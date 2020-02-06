# String Literals
In C, strings are arrays of characters terminated by an ASCII NUL character `'\0'`.

>A string is a contiguous sequence of characters terminated by and including the first null character. The term multibyte string is sometimes used instead to emphasize special processing given to multibyte characters contained in the string or to avoid confusion with a wide string. A pointer to a string is a pointer to its initial (lowest addressed) character. The length of a string is the number of bytes preceding the null character and the value of a string is the sequence of the values of the contained characters, in order.
>
>–[C11 ISO/IEC 9899:2011 Definition of string][1] (p 180)

You can define a string as a pointer to a char, initialised by a string literal. In this case, string literals are stored in a read only section of memory and are effectively constant.

A string literal e.g. "Hello World!" has the type `const char*` - a pointer to an array of chars which cannot be modified.

```c
const char *str = "Hello World!";
```

After this statement `str` is a pointer which points to an array of characters. These characters appear in the order of the string, and are followed by the null terminator character, '\0' (note that we do not need to write this character down in the string literal—the compiler adds it for us for literals only).

Each byte (`char` is a type which is one byte wide) holds a numeric representation of the particular letter (as an ASCII code). The string is just a sequence of bytes in memory, the last of which has a numeric value of 0.

Immutability
------------
It is not possible to modify the characters pointed to by a string as defined by `const char *str = "Hello World!"`. 

In this case, assignment to `str[i]` will result in a compiler error.

If the `const` modifier is not used in the variable declaration the code will still compile. Regardless of whether or not the variable is declared `const`, any attempt to modify the string will result in a segmentation fault crash.

To enable compiler warnings for this type of mistake, compile with `-Wwrite-strings` - this is not enabled by default with `-Wall`.

### Declare String Literals Const
Though many programmers are sloppy about `const`, as a matter of good practice __string literals should be declared const__.

The reason for the immutability of string literals is that the value is stored in a read-only section in the binary file and cannot be modified.

If you compile to an assembly file (use the `-S` compiler option in gcc), you can see the string literals in the `.rodata` section. In this context, rodata means “read-only data” - such data is available for the entire lifetime of the programme.

### String Literals in Memory
String literal data is placed into memory by the loader - the portion of the operating system which reads the executable file from the disk and initializes memory.

The loader knows what to write for the string literals (and where they should go in memory) because the compiler writes information into the executable file describing the contents of the data section.

After the loader finishes initializing memory, it marks the read-only portions of the static data section as non-writeable in the page table - the structure that the operating system maintains to describe the program’s memory to the hardware.

### Write Attempt - Consequences
Attempting to write to a read-only portion of memory is similar to writing to an invalid region of memory. It causes the hardware to trap into the operating system, transferring execution control from the programme to the OS kernel.

Conceptually, the hardware takes the execution arrow out of the program, and puts it into a particular function in the OS, noting where the execution arrow was in case the OS wants to return control to the program. The OS then sees that the program was attempting to access memory in invalid ways, and kills it with a segmentation fault. 

References
----------
[ISO/IEC definition of string][1]

[1]:http://www.open-std.org/jtc1/sc22/wg14/www/docs/n1570.pdf#%5B%7B%22num%22%3A425%2C%22gen%22%3A0%7D%2C%7B%22name%22%3A%22XYZ%22%7D%2C-27%2C816%2Cnull%5D
