# Preprocessing

Preprocessor directives begin with a `#` symbol and have their own syntax.

Include
-------
The `#include <file>` directive instructs the preprocessor to include the specified file. Angle brackets denote that the file is one of the C standard header files. Custom headers are generally defined by `"` double quotation marks, e.g.: `#include "my-header.h"`.

Header files generally contain:

* Function prototypes
* Macro definitions
* Type declarations

Function Prototype
------------------
Like a function definition, but without a body and terminated by a semi-colon.

The prototype allows the compiler to check that the correct number and type of arguments have been passed when the function is used in the source code, and that the return value is the correct type - without having the entire function available.

Macros
------
May be as simple as defining a constant e.g.

```c
#define EXIT_SUCCESS 0
```
This macro in `stdlib.h` allows a function to return the string `EXIT_SUCCESS` - the preprocessor will replace all occurrences of the string with the numeral `0`. Allows source code to be more meaningful, and helps improve portability between platforms.


