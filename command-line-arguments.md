# Command Line Arguments
To accept command line arguments, the signature of `main()` should be:

```c
int main(int argc, char **argv);
```

The first argument, `int argc` is the count of how many command line arguments were passed in (it stands for argument count).

The second argument `char **argv` is an array of strings which contains the arguments that were passed in (`argv` stands for argument vector).

The first element of `argv` -`argv[0]` - is a string containing the name of the program as it was invoked on the command line.

Access the elements of `argv` as for any other array of strings.

For programmes that expect a particular number of arguments, `argc` should be checked first to make sure that the correct number of arguments has been supplied before accessing the elements of `argv`.

Failure to do so can result in the programme segfaulting is insufficient arguments are provided.

Example
-------
Accept two command line arguments, use them as strings:

```c
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr, "Usage:\n%s <input file path> <output file path>\n", argv[0]);
		return EXIT_FAILURE;
	}
	// argv[0] is the programme name
	for (int i = 1; i < argc; i++) {
		printf("argv[%d]:\t%s\n", i, argv[i]); 
	}
	return EXIT_SUCCESS;
}
```

Set Options
-----------
```c
#include <stdio.h>
#include <stdlib.h>

enum {
    OPT_A = 0x01,
    OPT_B = 0x02,
    OPT_C = 0x04,
    OPT_H = 0x08,
    NUM_OPTIONS = 4
};
static char *options[] = {"OPT_A", "OPT_B", "OPT_C", "OPT_H"};
static char flags = 0;

// Set option: apply bitwise OR against flags with relevant OPTIONS value.
void setOption(char c)
{
	switch(c) {
		case 'a':
			flags |= OPT_A;
			break;
		case 'b':
			flags |= OPT_B;
			break;
		case 'c':
			flags |= OPT_C;
			break;
		case 'h':
			flags |= OPT_H;
			break;
		default:
			fprintf(stderr, "Option %c not recognised.\n", c);
	}
}

/**
 * Set an options flag from command line arguments prepended with '-'
 * */
int main(int argc, char **argv)
{
	(void)argc;

	while (*(++argv) && **argv == '-') {
		while (*(++(*argv))) {
			setOption(**argv);
		}
	}

	// Print the set options
	for (int i = 0; i < NUM_OPTIONS; i++) {
		printf("%s is %s\n", options[i], flags & (1 << i) ? "set" : "not set");
	}
	
	// Loop through additional arguments if necessary 
	while (*argv) {
		printf("%s\n", *(argv++));
	}

	return EXIT_SUCCESS;
}
```
### Outer While Loop
1. Pre-increment argv to ignore first string (programme name).
2. Dereference argv once to get a pointer to the first char of the relevant string.
3. Fully dereferencing argv (i.e. `**argv`) at this point returns the first character of the string.
4. Continue until either `*argv` is NULL or the first char of the string != '-'.

### Inner While Loop
Step through each character, passing the char to setOption.

The `*(++(*argv))` statement means:
* Preincrement the pointer to the string by `++(*argv)`, thereby advancing the char pointed to and ignoring the leading '-'.
* Dereference this char (with the first `*`) to return the actual char. 

Getopt
------
For more complex command line arguments, the `getopt()` function is available. Include the `unistd.h` header file to access `getopt()`.

>The getopt() function parses the command-line arguments. Its arguments argc and argv are the argument count and array as passed to the main() function on program invocation. An element of argv that starts with '-' (and is not  exactly "-" or "--") is an option element. The characters of this element (aside from the initial '-') are option characters. If getopt() is called repeatedly, it returns successively each of the option characters from each of the option elements.
>
>— getopt man page: `man -S3 getopt`

The Environment Pointer
-----------------------
The `main()` function can take a third argument: `char ** envp`.

This is a pointer to an array of strings containing the values of environment variables.

The elements of the array are strings of the form `variable=value` (e.g., `PATH=/bin:/usr/bin`).

You can also access the environment variables with the functions `getenv`, `setenv`, `putenv`, and `unsetenv`.

Process Creation
----------------
When the command shell runs a programme, it makes system calls that:

* Create a new process - a fork
* Replace running programme with that requested (`execve()` system call)

The `execve` system call takes:
* An argument specifying the file with the programme to run
* A second argument specifying the values to pass the new program as `argv` (which must end with a NULL element)
* A third argument specifying the values to pass for `envp`

When the OS executes the execve system call, it destroys the currently running program (the system call only returns on an error), and loads the specified executable binary into memory.

The values of `argv` and `envp` are written into memory conforming to an ABI - application binary interface. The ABI is a contract between the OS and programmes about how things work.

The kernel then sets the execution arrow to a starting location specified in the executable binary (On Linux with gcc, the entry point is a symbol called `_start` - but the details are platform specific.

The startup code resides in an object file that is linked with any compiled C programme unless you request explicitly for it not to be. This calls various functions which initialize the C library. This startup code also counts the elements of `argv` to compute the value of `argc` and eventually calls main.

Regardless of how main is declared, it always passes in `argc`, `argv`, and `envp`. If main is declared with fewer arguments, it still receives them but simply ignores them.

When main returns, it returns to the function that called it. In the case of main, the caller is the startup code. At this point, the startup code performs any cleanup required by the C library, and calls `exit` to quit the programme. The return value of `main()` is passed in as the argument of `exit`. This determines the exit status of the programme.

The shell (or other program that ran the program in question) can make a system call, which waits for its "child" process(es) to exit, and then collects their return values.



Resources
---------
* [Getopt][1]

[1]: https://www.gnu.org/software/libc/manual/html_node/Getopt.html

