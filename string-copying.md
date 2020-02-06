# String Copying
The C library `strncpy()` function copies a string from one location to another, taking a parameter that specifies maximum number of characters that may be copied. If the length of the source string exceeds the limit, then the destination is not null terminated - a situation which the programmer must typically rectify before using the string for any significant purpose.

The similarly named function `strcpy()` is more dangerous, as there is no way to tell it how much space is available in the destination. If insufficient space is available, then `strcpy()` will overwrite whatever follows it in memory, creating potential problems.

Some of these problems may result in security vulnerabilities. There is another function, `strdup()` which allocates space for a copy of the string, and copies it into that space.

strcpy vs strncpy
-----------------
`strncpy()` attempts to prevent buffer overflow by requiring a length. `strcpy()` depends on a trailing `\0`, which may not always be present.

On the other hand, `strncpy()` does not null-terminate the string - which can be very problematic.

`strncpy()` oddities:

* It doesn't put a nul-terminator on the destination if it is completely filled; and
* It always completely fills the destination, with nuls if necessary.

Safer strncpy()?
----------------
For a "safer strcpy()", you are better off using strncat() like so:

```c
#include <stdio.h>
#include <string.h>

void copyString(char *dest, size_t destSize, const char *source)
{
	if (destSize >= strlen(source) + 1)
	{
		dest[0] = '\0';
		strncat(dest, source, destSize - 1);
	}
}

int main()
{
	const char *s1 = "David";
	char dest[6];
	copyString(dest, 6, s1);
	printf("dest is %s\n", dest);
	return 0;
}
```
[Reference][1]


[1]: https://stackoverflow.com/a/1258577/3590673

