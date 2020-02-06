# Debugging With GDB
Gathers information about what is going on in code.

Compiling
---------
For gdb to work, the code must be compiled with _debugging symbols_: these are extra pieces of data that help the debugging tool determine the layout of code and data in memory.

The `-g` option instructs `gcc` to compile with debugging symbols. If you're using `gdb`, use `-ggdb3` to request the maximum amount of debugging information. If compiling in multiple steps, include `-ggdb3` at each step.

Run GDB
-------
Once the programme has been compiled with debugging symbols, run `gdb`. You can do this directly from the command line.

Commands
--------
### Start
`start`: Begin (or restart) the program’s execution. Stop the program (to accept more commands) as soon as execution enters main.

### Run
`run`: This command runs the program (possibly restarting it). It will not stop unless it encounters some other condition that causes it to stop. Abbrieviation: `r`.

### Step
`step`: Advance the program one "step" - `step` will go into a function called by the current line. This command can be abbreviated `s`.

### Next
`next`: Advance the program one line. Unlike step, if the current line of code is a function call, gdb will execute the entire called function without stopping. This command can be abbreviated `n`.

### Print
`print`: Takes an expression as an argument, evaluates that expression, and prints the results. Note that if the expression has side-effects, they will happen, and will affect the state of the program (e.g., if you do print x = 3, it will set x to 3, then print 3). You can put /x after print to get the result printed in hexadecimal format. This command can be abbreviated `p` (or `p/x` to print in hex).

Every time you print the value of an expression, gdb will remember the value in its own internal variables which are named `$1`, `$2`, etc. Gdb shows the internal variable when it prints the value—e.g., `$1 = 42`).

You can use these $ variables in other expressions if you want to make use of these values later.

### Print from Array
gdb also has a feature to let you print multiple elements from an array. If you put `@number` after an lvalue, gdb will print number values starting at the location you named. This feature is most useful with arrays - for example, if `a` is an array, you can do `p a[0]@5` to print the first 5 elements of `a`.

### Display
`display`: The display command takes an expression as an argument, and displays its value every time gdb stops and displays a prompt. For example `display i` will evaluate and print `i` before each (gdb) prompt. You can abbreviate this command `disp`.

### Repeat Commands
If you hit enter without entering any command, gdb will repeat the last command you entered. This feature is most useful when you want to use step or next multiple times in a row.

### Command Line Arguments
To pass command line arguments, you can either write them after the `start` or `run` command (e.g. `run someArg anotherArg`), or you can use `set args` to set the command line arguments.

Investigating the State of Your Program
---------------------------------------
A debugger allows you to investigate the state of your programme. The `print` and `display` commands allow you to see what value an expression evaluates to.

### Inspect Stack Frames
Gdb allows you to inspect the current set of stack frames and move up and down within them. The `backtrace` command lists all of the stack frames with the current one on top, and main on the bottom, so that you can see what function calls got you to the current place. The `backtrace` also lists the line where each call was made (or where the execution arrow is, for the current frame).

Gdb uses the variables in the current scope when executing the `print` command. If you need to inspect variables in other frames further up the stack, instruct gdb to select different frames with `up` and `down`, which move scope up and down the stack.

If the programme stops in a failed assert gdb will stop deep inside the C library - in the code that handles assert. The code under examination is a few stack frames up. Use `up` a few times until gdb returns to a frame corresponding to the relevant code.

The `info` command provides information about various aspects of the programme. This command has various subcommands:

* `info frame` describes the memory layout of the current frame
* `info types` describes the types that are in the current program

There are a variety of info commands, but most of them are for more advanced uses - use `help info` within gdb for more information.

Controlling Execution
---------------------
The `next` and `step` commands advance the state of the program line-by-line. This may not be optimal, especially when debugging a large programme.

A breakpoint instructs gdb to stop execution whenever the program reaches a particular line.

Breakpoints are set with the `break` command, followed by either a line number or a function name (meaning to set the breakpoint at the start of that function).

In emacs, you can also press C-x space to set a breakpoint at the point. It is also possible to set a breakpoint at a particular memory address, although that is a more advanced feature. When we set a breakpoint, gdb will assign it a number, which we can use to identify it to other breakpoint-related commands.

Once we have a breakpoint set, we can run the program (or continue, if it is already started), and it will execute until the breakpoint is encountered (or some other condition which causes execution to stop). When the breakpoint is encountered, gdb will return control to us at a (gdb) prompt, allowing us to give it other commands. You might inspect the state of the program, set more breakpoints, and continue.

By default, breakpoints are unconditional. Gdb will stop the program and give you control anytime it reaches the appropriate line.

### Conditional Breakpoint
Useful for looking inside loops and recursion.

Break on line 7 if `i` is as specified:
```
(gdb) break 7 if i==250000
```
Watchpoints
-----------
A watchpoint stops execution when the value of a particular expression changes. For example: `watch i`, which will cause gdb to stop whenever the value of `i` changes. When gdb stops in response to a watchpoint, it will print the old value of the expression and the new value.

Watchpoints can be a particularly powerful tool when you have pointer-related problems, and values of variables are changing through aliases.

However, sometimes, the alias we have when we setup the watchpoint may go out of scope before the change we are interested in happens. For example, we may want to watch `*p`, but `p` is a local variable, whose scope ends before the value changes.

Whenever we face such a problem, we can print `p`, which will give us the pointer in a gdb variable (e.g., `$6`) and then we can use that `$`-variable - which never goes out of scope - to set a watchpoint: watch `*$6`.

Signals
-------
When a programme receives a signal, gdb will stop the programme and give you control. There are three particularly common signals that come up during debugging:

### SIGSEGV
Indicates a segmentation fault. If the programme is segfaulting, then just running it in gdb can help you gather a lot of information about what is happening.

When the segfault happens, gdb will stop, and your program will be on the line where the segfault happened. You can then begin inspecting the state of the program (printing out variables) to see what went wrong.

### SIGABRT
Programme calls `abort()` or fails an assert. As with segfaults, if your code is failing asserts, then running it in gdb can be incredibly useful. You will get control of the program at the point where assert causes the program to abort, and (after going up a few frames back into your own code), see exactly what was going on when the problem happened.

### SIGINT
Programme is interrupted - e.g., by the user pressing Control-c. If the programme is getting stuck in an infinite loop, you can run it in gdb, and then after a while, press Control-c. You can then see where the program is, and what it is doing. You are not guaranteed to be in the right place (you may interrupt the program before it gets into the infinite loop), but if you wait sufficiently long, you will typically end up where you want. You can then see what is happening, and why you are not getting the behaviour you want.
