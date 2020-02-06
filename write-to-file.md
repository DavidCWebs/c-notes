# Write to File

Printing Formatted Text: fprintf
--------------------------------
The `fprintf()` function is similar to `printf()`, but it's first argument is a file stream specifying where to write output.

Example, `fprintf()`:

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *f = fopen("out.txt", "w");
	if (!f) {
		perror("could not open file for writing.");
		return EXIT_FAILURE;
	}
	const char *str = 
		"test.\n"
		"multi\n"
		"line\n";
	fprintf(f, "%s", str);
	fclose(f);
	return EXIT_SUCCESS;
}
```

Write a Single Character at a Time With fputc
---------------------------------------------
Example:

```c
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int copy(const char *inFile, const char *outFile)
{
	FILE *fpIn = fopen(inFile, "r");
	FILE *fpOut = fopen(outFile, "w");
	if (!fpIn) {
		perror("Can't open file for reading.");
		return EXIT_FAILURE;
	}

	if (!fpOut) {
		perror("Can't open file for writing.");
		return EXIT_FAILURE;
	}

	int c;
	while ((c = fgetc(fpIn)) != EOF) {
		// Transform the char
		c = toupper(c);

		// Write to output, one char at a time.
		fputc(c, fpOut);
	}

	// We should properly check for success of fclose()
	fclose(fpIn);
	fclose(fpOut);
	return EXIT_SUCCESS;
}

int main(int argc, char **argv)
{
	if (argc != 3) {
		fprintf(stderr, "Usage: %s <input file> <output file>\n", argv[0]);
		return EXIT_FAILURE;
	}
	copy(argv[1], argv[2]);
	return 0;
}
```

Write String Without Format Conversions
---------------------------------------
The `fputs()` function writes the string s to stream, without its terminating null byte.

See `man fputs` for more information.

Print Non Textual Data
----------------------
Use `fwrite()`:

```c
size_t fwrite(const void *ptr, size_t size, size_t nmemb, FILE *stream);
```
The function `fwrite()` writes `nmemb` items of data, each `size` bytes long, to the stream pointed to by `stream`, obtaining them from the location given by `ptr`.

Point of Failure
----------------
These methods write at the current position in the file and advance it accordingly.

Any of these methods may fail - some failures are detected immediately whereas others of are detected later.

See the relevant man pages for more info re failure.

The C library functions may buffer the data and not immediately request that the OS write it. Even once the application makes the requisite system calls to write the data, the OS may buffer it internally before actually writing it to the hardware device.

Making a system call is a slow process, and writing to a hard disk is quite slow. Furthermore, writing a disk becomes less efficient as you write smaller quantities of data to it - there are fixed overheads to find the correct location on disk - so the OS tries to buffer up writes.
