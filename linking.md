# Linking
Linking is the final step in producing a programme. Linking the programme takes one or more object files and combines them with various libraries and startup code to produce an executable binary.

The object files refer to functions by name, and the linker resolves these references by finding the matching function definitions. If the linker can't find the definition for a name ("symbol") or if the same symbol is defined more than once, the Linker will report an error.

Errors
------
Reported by `ld`, which is the linkers name.

Unresolved symbol error may result from one of the following:

* The symbol was not defined
* The object where the symbol was defined was not included
* It has been specified that the symbol is only visible in the file (compilation unit) where it was defined (i.e. by use of the `static` keyword).

Trying to include a `.c` file will cause a linker error - only header files may be linked.

External Libraries
------------------
For libraries other than the C standard library, you must specifically request that the linker links the library with the `-l` option, specifying the name of library immediately after the `l` (no spaces).

You may also need to specify a path using the `-L` option. From the `man ld` page:

>-L searchdir
>--library-path=searchdir
>
>Add path searchdir to the list of paths that ld will search for archive libraries and ld control scripts.  You may use this option any number of times.  The directories are searched in the order in which they are specified on the command line.  Directories specified on the command line are searched before the default directories.  All -L options apply to all -l options, regardless of the order in which the options appear.
>
>-L options do not affect how ld searches for a linker script unless -T option is specified.
>
>If searchdir begins with "=", then the "=" will be replaced by the sysroot prefix, controlled by the --sysroot option, or specified when the linker is configured.
>
>The default set of paths searched (without being specified with -L) depends on which emulation mode ld is using, and in some cases also on how it was configured.
>
>The paths can also be specified in a link script with the "SEARCH_DIR" command.  Directories specified this way are searched at the point in which the linker script appears in the command line.
