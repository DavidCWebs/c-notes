# The Operating System & System Calls
To interact with the outside world, a programme must access hardware - a disk drive, a screen, a keyboard, etc.

Normal programmes are not trusted to access hardware directly - such access is mediated by the operating system.

A programme makes a request to the OS via a _system call_ - a special type of function that transfers control from the programme to the operating system. The OS checks that the request is allowed before executing it.

This is how an OS enforces security and access rules. If a request is not permissable, the OS can return an error code to the originating programme. Otherwise, the OS can perform the requested actions before returning the result to the programme.

The C Library
-------------
Though C code can make system calls directly, it is more common to use functions in the C library (which in turn make the necessary system calls).

### Example: printf()
The `printf()` function is part of the C library that is used to write to standard output. The `printf()` function scans the format string and performs the required format conversions before writing the resulting string to standard output. The output is achieved by means of the `write()` system call.

System Call
-----------
Transfers control to the OS, requests that a task be performed (e.g. write to standard output).

Library Call
------------
Calls a function found in a library, such as the C standard library.

Man Pages: System Calls, Library Functions
------------------------------------------
* System call: man section 2 e.g. `man 2 write`
* Library function: man section 3 e.g. `man 3 printf`

Errors From System Calls
------------------------
System calls can fail in multiple ways.

When a system call fails in C, a global variable `errno` is set. `errno` stands for __error number__.

If a system call fails, `errno` can provide information about what went wrong.

Error Constants
---------------
Check for specific errors by comparing `errno` against various constants defined in `errno.h`.

Error Message
-------------
The C library function `perror()` prints a descriptive message based on the current value of `errno`. It takes one argument, a string which is printed before the error message.

To use `perror()`, `#include <stdio.h>`.

The `perror(const char *s)` function produces a message on standard error describing the last error encountered during a call to a system or library function.

If `s` is not NULL and `*s` is not a null byte, the argument string `s` is printed, followed by a colon and a blank space. Then an error message corresponding to the current value of `errno` is printed followed by a new-line.

The argument string should include the name of the function that caused the error.

 The global error list `sys_errlist[]`, which can be indexed by `errno`, can be used to obtain the error message without the newline. See `man 3 perror` for more on this.

When a system call fails, it usually returns -1 and sets the variable `errno` to a value describing what went wrong.

Many library functions also set `errno`.

Note that `errno` is __undefined__ after a successful system call or library function call: the call may well change this variable, even though it succeeds - for example, it may have internally used a different library function that failed.

Thus, if a failing call is not immediately followed by a call to `perror()`, the value of errno should be saved to avoid the `errno` being "polluted" by seemingly successful calls.

