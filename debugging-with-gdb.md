# Debugging With GDB
Using a debugger allows you to investigate the state of your programme. If you're working in C or C++, familiarity with a debugger is more or less essential.

GDB is the GNU debugger - it is a tool that allows you to see what is going on "inside" your target programme while it is executing - or what a programme was doing at the moment it crashed.

Compiling
---------
To use GDB, compile with _debugging symbols_: these are extra pieces of data that help the tool determine the layout of code and data in memory.

The `-g` option instructs `gcc` to compile with debugging symbols. Use `-ggdb3` for the maximum amount of debugging information. If compiling in multiple steps, include `-ggdb3` at each step.

Run GDB
-------
Once the programme has been compiled with debugging symbols, run `gdb` from the command line, providing the name of your executable as an argument: `gdb ./my-prog`.

Commands: Moving Through the Programme
--------------------------------------
### Run
`run` or `r`: Run the programme, or possibly restart it. The programme will run until it encounters a condition that causes it to stop - a crash, breakpoint etc.

### Start
`start`: Begin (or restart) the programme. Similar to `run`, but `start` is the equivalent of setting a temporary breakpoint at the beginning of the main procedure. The `start` command stops the programme (e.g. to accept more commands) as soon as execution enters the main function - `main()` in C and C++.

### Step
`step` or `s`: Advance the programme one step - `step` will go into called functions.

### Next
`next` or `n`: Advance the program one line. Unlike step, if the current line of code is a function call, GDB will execute the entire called function without jumping into the function.

### Repeat Commands
Hit enter without entering a command to repeat the last command.

### Command Line Arguments
To pass command line arguments, you can either add them after the `start` or `run` (`r`) command (e.g. `r someArg anotherArg`), or you can use `set args` to set command line arguments.

Examine Variables
-----------------
### Print
`print` or `p`: Evaluates an expression and prints the result. Print a variable x: `p x` to show the value of `x` at the current position in the programme.

If the expression has side-effects they will affect the state of the program - if you do `p x = 3`, x is set to 3 and printed.

Format print:

* `/x`: Integer in hexadecimal format
* `/d`: Integer in signed decimal
* `/u`: Integer in unsigned decimal
* `/o`: Integer in octal
* `/t`: Integer in binary ("t" == "two")
* `/a`: Print as an address

E.g. print variable `i` in hex format: `p/x i`.

[See here][3] for more options.


When you print the value of an expression, GDB remembers the value in internal variables which are named `$1`, `$2` etc. Gdb shows the internal variable when it prints the value e.g., `$1 = 42`.

The `$` variables can be used in subsequent expressions.

### Print from Array
You can print multiple elements from an array - put `@number` after an lvalue name and GDB prints `number` values starting at that index.

If `A` is an array, `p A[0]@5` will print the first 5 elements.

Print all elements in array `A` of length `len`: `p *A@len`

### Display
`display` or `disp`: Automatically display certain expressions each time GDB stops at a breakpoint or after a step. To display the value of `i` at each breakpoint: `display i`.

Investigating the State of Your Program
---------------------------------------
. The `print` and `display` commands allow you to see what value an expression evaluates to.

### Inspect Stack Frames
Gdb allows you to inspect the current set of stack frames and move up and down within them. The `backtrace` (`bt`) command lists all of the stack frames with the current one on top, and main on the bottom - showing the function calls that lead up to the current position. The `backtrace` also shows the line where each call was made.

Gdb uses the variables in the current scope when executing the `print` command. To inspect variables in other frames further up the stack, select different frames with the `up` and `down` command, which move scope up and down the stack.

If the programme stops in a failed assert GDB will stop deep inside the C library - in the code that handles assert. The code under examination is likely to be a number of stack frames up. Use the `up` command a few times until GDB enters the appropriate frame.

The `info` command provides information about various aspects of the programme. This command has various subcommands:

* `info frame` describes the memory layout of the current frame
* `info types` describes the types that are in the current program
* `info b` information about breakpoints

There are a variety of info commands, but most of them are for more advanced uses - use `help info` within GDB for more information.

Controlling Execution
---------------------
The `next` (`n`) and `step` (`s`) commands advance the state of the program line-by-line. This may not be optimal, especially when debugging a large programme.

A breakpoint instructs GDB to stop execution whenever the program reaches a particular line.

### Example Breakpoints

```gdb
# Breakpoint inside function main() - break inserted just after opening curly brace:
b main
Breakpoint 1 at 0x4007de: file main.c, line 6.

# Breakpoint in file main.c on line 42:

b main.c:42
Breakpoint 2 at 0x4009b5: file main.c, line 43.
```
Breakpoints are set with the `break` (`b`) command, followed by either a line number or a function name (meaning to set the breakpoint at the start of that function).

When you set a breakpoint, GDB assigns it an ID number.

The programme runs (or continues if already started) until the breakpoint. When the breakpoint is encountered, GDB pauses execution and allows you to inspect the state of the programme at this point.

You can enter `c` to continue from the breakpoint, which jumps to the next breakpoint. You can also use `n` or `s` to step through the programme from this point.

By default, breakpoints are unconditional. Gdb will stop the program and give you control anytime it reaches the appropriate line.

### Conditional Breakpoint
Conditional breakpoints are very useful for looking inside loops and recursive reoutines.

Break on line 7 if `i` is as specified:
```
(gdb) break 7 if i==250000
```
### Breakpoint Info

Show info on currently set breakpoints:
```gdb
info b
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000004007de in main at main.c:6
2       breakpoint     keep y   0x00000000004009b5 in main at main.c:43
```
### Delete all Breakpoints
`delete`, `del` or `d` and enter 'y' to confirm.

### Delete Specific Breakpoint
Get the ID using `info b` then `d x` to delete breakpoint with id x.

### Disable all Breakpoints
`disable` with no arguments to disable all breakpoints. To enable, enter `enable x` where `x` is the ID of the breakpoint in question.

### Disable Specific Breakpoints

```gdb
disable x

# disable multiple, space separated:
disable x y
```

### Save and Reload Breakpoints
Save current breakpoints into a file `bp-store.txt`:

```gdb
save breakpoints bp-store.txt
```

To reload:
```gdb
source bp-store.txt
```

Backtrace
---------
Run `bt` after programme interruption to see a backtrace - a list of function calls, representing the call stack. The top line is the frame that was current when the programme was interrupted.

Use the `frame` command to inspect a specified frame.

Watchpoints
-----------
A watchpoint stops execution when the value of a particular expression changes. For example: `watch i`, which will cause GDB to stop whenever the value of `i` changes. When GDB stops in response to a watchpoint, it will print the old value of the expression and the new value.

Watchpoints can be a particularly powerful tool when you have pointer-related problems, and values of variables are changing through aliases.

However, sometimes, the alias we have when we setup the watchpoint may go out of scope before the change we are interested in happens. For example, we may want to watch `*p`, but `p` is a local variable, whose scope ends before the value changes.

Whenever we face such a problem, we can print `p`, which will give us the pointer in a GDB variable (e.g., `$6`) and then we can use that `$`-variable - which never goes out of scope - to set a watchpoint: watch `*$6`.

Signals
-------
When a programme receives a signal, GDB will stop the programme and give you control.

### SIGSEGV
Indicates a segmentation fault. The programme has attempted to access a restricted area of memory.

Execution stops, and the programme will be on the line where the segfault happened. You can inspect the state of the program (printing out variables) to see what went wrong.

### SIGABRT
Programme calls `abort()` or fails an assert. GDB leaves you in control of the programme at the point where assert caused the abort, and (after going up a few frames back into your own code), see exactly what was going on when the problem happened.

### SIGINT
Programme is interrupted - e.g., by the user pressing Control-c. If the programme is getting stuck in an infinite loop, you can run it in gdb, and then after a while, press Control-c. 

Once execution has halted, you can use `bt` to see a backtrace. To examine a particular frame, use the `frame` command, e.g. `(gdb) f 6` to inspect frame 6.

References
----------
* [Debugging with GDB][1] - online book
* [GDB Tutorial][2] by Faye Williams - loads of useful GDB stuff on the same site

[1]: https://sourceware.org/gdb/onlinedocs/gdb/
[2]: https://www.fayewilliams.com/2011/02/01/command-line-gdb-tutorial-and-walkthrough-part-1/
[3]: https://sourceware.org/gdb/onlinedocs/gdb/Output-Formats.html
