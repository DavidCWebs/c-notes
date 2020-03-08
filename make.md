# Make & Makefiles

The GNU `make` utility is a tool that maintains groups of programmes `make` can determine which pieces of a large programme need to be compiled and/or recompiled, and generally take care of compilation and recompilation in an efficient way.

You can use `make` with any programming language whose compiler can be run from the command line. Beyond compiling programmes, `make` can describe any task that involves updating files automatically when other files change.

The Makefile
------------
The `Makefile` is used to describe relationships between files in the programme, and the commands necessary for updating files.

In C programmes, the executable file is updated ("linked") from "object" files, which are in turn made by compiling source files.

Once you've written a suitable `Makefile`, you just need to run `make` in the programme root directory to perform all necessary recompilations.

If you don't specify a `Makefile` with `make -f <makefile>`, `make` will look for the makefiles:

1. GNUmakefile
2. makefile
3. Makefile

in that order. It is recommended to call the makefile `Makefile`.

The makefile contains one or more rules that specify how a target is produced from prerequisite files. `make` updates a target if the prerequisite files that it depends upon have been modified since the target was last changed, or if the target does not exist.

Rules
-----
A `make` rule is comprised of a target specification and it's prerequisite files, all on one line and with the target separated from the prerequisites by a colon.

After the space-separated list of prerequisites, the rule has a newline and a list of commands that should be executed required to rebuild the target from the prerequisites.

Commands may be added over multiple lines, but each line that contains a command must start with a TAB character.

### Example Makefile

The following makefile has 3 targets: `myProgramme`, `moduleOne` & `moduleTwo`:

```make
myProgramme: moduleOne.o moduleTwo.o
	gcc -o myProgramme moduleOne.o moduleTwo.o

moduleOne.o: moduleOne.c moduleOne.h standaloneHeader.h
	gcc -std=gnu=gnu99 -pedantic -Wall -c moduleOne.c

moduleTwo.o: moduleTwo.c moduleTwo.h standaloneHeader.h
	gcc -std=gnu=gnu99 -pedantic -Wall -c moduleTwo.c
```
Special Make Variables
----------------------
Inside an action, special variables are available for matching filenames:

* `$@`: The full target name of the current target
* `$?`: Dependencies that are _newer_ than the current target
* `$*`: Returns text corresponding to `%` in current target
* `$<`: Returns the name of the first dependency
* `$^`: Name of all dependencies, space separated

This allows your makefile to be more concise:

### Example Makefile 2

Example C++ makefile for the following project structure:

- `main.cpp`: includes grade.h & util.h
- `util.cpp`: includes util.h
- `util.h`: contains declarations
- `grade.cpp`: includes grade.h
- `grade.h`: contains declarations

```make
# Set a variable for flags to avoid repetition
CXXFLAGS = -W -Wall -pedantic -std=c++17 -g
CXX = g++ ${CXXFLAGS}
NAME = grades

# The target has the dependencies util.o and main.o
$(NAME): util.o main.o
	$(CXX) -o $@ $^

# For any .c file, build an object file by applying the actions on the following line.
%.o: %.c
	$(CXX) -c $<

util.o: util.h

grade.o: grade.h

# Remove the executable and all object files
.PHONY: clean
clean:
	-rm $(NAME) *.o
```
Variables for Implicit Rules
----------------------------
- `CFLAGS`: Extra flags to give to the C compiler.
- `CPPFLAGS`: Extra flags to give to the C preprocessor and programs that use it (the C and Fortran compilers). 
- `CXX`: Program for compiling C++ programs, default `g++`. 
- `CXXFLAGS`: Extra flags to give to the C++ compiler.

