# Manpages
Use the command:

```bash
man man
```
...for information on how to use `man`.


Access info on C function that is also the name of a shell built-in:

```bash
man -s3 printf
# Outputs information about the C function 
```

Section 3 is for C library function reference.
Section 1 is for executable programmes and shell commands.

Search Manpages by Keyword
--------------------------
Use the -k option, denoting "keyword". For example:

```bash
man -k compare
# List man pages with the string "compare" in their descriptions
```
