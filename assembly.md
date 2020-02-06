# Assembly
The compiler generates assembly which is assembled into object files.

gcc invokes the assembler to translate the assembly instructions from the textual/human readable format into numerical encodings that can be used by the processor.

The object file contains machine executable instructions for the compiled source code. It is not yet a complete programme.

The object file may reference functions that it does not contain - e.g. those in the C library, or in other files.

## Partial Compilation
You can halt compilation at this stage if required:

The `-c` option for gcc causes the compiler to assemble the source files, but to stop at this point - the linking stage is not done. By default, the object file name for a source file is made by replacing the suffix .c, .i, .s, etc., with .o. Unrecognized input files, not requiring compilation or assembly, are ignored. You can specify an output file name with the `-o myName.o` option. By convention, object files should have the `.o` suffix.

This may be useful for large programmes, where the code needs to be partitioned into manageable sections. Each source file can be individually compiled to an object file, and object files can be linked together as a separate process. This can aid efficiency - change code in one file, recompile that file to generate a new object file, and link this to the main programme.

Optimisation
------------
Have the compiler optimise code using the `-O` option, followed by the level of optimisation required.

Release quality code, `gcc` compiled with `-O3`.

