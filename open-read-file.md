# Open and Read a File

Opening a file results in a _stream_ associated with that file.

In C, this is represented by the `FILE *` type.

Open File
---------
To open a file, the `fopen` function is typically used:

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
	// Open file - fp is a file stream
	FILE *fp = fopen("input.txt", "r");
	
	// Check that we have a valid stream
	if (!fp) {
		perror("Problem opening file");
		return EXIT_FAILURE;
	}

	// So stuff with the file contents
	char *lineBuf = NULL;
	size_t len = 0;
	while(getline(&lineBuf, &len, fp) != EOF)
		printf("%s", lineBuf);
	free(lineBuf);

	// Close the file
	fclose(fp);
	return EXIT_SUCCESS;
}
```

`fopen` takes two parameters: name of file to open, and the mode with which to open it:

```c
FILE *fopen(const char *path-to-file, const char *mode);
```

The argument `mode` points to a string beginning with one of the following sequences (possibly followed by additional characters, as described below):

* "r": Open text file for reading. The stream is positioned at the beginning of the file.
* "r+": Open for reading and writing. The stream is positioned at the beginning of the file.
* "w": Truncate file to zero length or create text file for writing. The stream is positioned at the beginning of the file.
* "w+": Open for reading and writing. The file is created if it does not exist, otherwise it is truncated. Stream positioned at the beginning of the file.
* "a": Open for appending (writing at end of file). The file is created if it does not exist. Stream positioned at the end of the file.
* "a+": Open for reading and appending (writing at end of file). The file is created if it does not exist. Theinitial file position for reading is at the beginning of the file, but output is always appended to the end of the file.

The mode string can also include the letter 'b' either as a last character or as a character between the characters in any of the two-character strings described above. This is strictly for compatibility with C89 and has no effect; the 'b' is ignored on all POSIX conforming systems, including Linux. Other systems may treat text files and binary files differently, and adding the 'b' may be a good idea if you do I/O to a binary file and expect that your program may be ported to non-UNIX environments.

See `man fopen` for more.

Close an Open File
------------------
Pass the file pointer of an open file to the `fclose()` function:

```c
int fclose(FILE *stream);
```
Returns 0 on success.

On failure `EOF` is returned and `errno` is set accordingly.

__Check for failure__ and advise user accordingly before closing the programme. You might provide another opportunity to write data and save, allowing the user to free up disk space.

Closing the stream sends any buffered write data to the OS, and then asks the OS to close the associated file descriptor.

After calling `fclose()` on a stream, you may no longer access it - a subsequent call to `fgetc`, `fprintf`, etc. is erroneous - what will happen is undefined.


FILE structs
------------
The actual struct that represents the file is complex, but the complexity is abstracted away. The actual struct does not directly contain data from the file. It is not necessary to know what the `FILE` struct contains, only how to interact with it.

The details of `FILE` are implementation specific.

Relevant data held by `FILE`:

* Information about the state of the file - e.g. which file is open, it's mode.
* Data in the file.

The `FILE` struct does not contain the name of the file, rather a file descriptor, which is a numeric identifier provided by the operating system when the system call to open the file is made.

C library functions which work on the stream use this descriptor as they interact with system calls.

Failure
-------
If `fopen()` fails, `NULL` is returned.

__Always check the return value of fopen before proceeeding__: make sure you have a valid stream to work with.
* Current position - where exactly reads and writes will occur.

Read File: fgetc
-----------------
Read the file character-by-character using `fgetc()`.

Example:

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		perror("Problem opening file");
		return EXIT_FAILURE;
	}
	int c; // must be an int, to handle EOF
	while ((c = fgetc(fp)) != EOF) {
		printf("%c", c);
	}

	return EXIT_SUCCESS;
}
```
Note that an assignment is also an expression - so `fgetc()` can be used to read characters (assignment) in the loop's conditional expression. In other words, make the assignment and the conditional check in the while loop's expression.

Read File: fgets
----------------
Read a file one line at a time, with a maximum length - in contrast to `getline()` where the line buffer is dynamically allocated.

Example:

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	FILE *fp = fopen("input.txt", "r");
	if (!fp) {
		perror("Problem opening file");
		return EXIT_FAILURE;
	}
	char lineBuffer [100];
	while (fgets(lineBuffer, 100, fp) != NULL) {
		// If the string has no newline, lineBuffer wasn't big enough
		if (strchr(lineBuffer, '\n') == NULL) {
			printf("Line too long...");
			return EXIT_FAILURE;
		}
		printf("%s", lineBuffer);
	}
	fclose(fp);
	return EXIT_SUCCESS;
}
```
Read Non-Textual Data From File
-------------------------------
When data is in binary format - i.e. it is not a text file, instead consisting of image, video or sound data - `fread()` may be the most appropriate function:

```c
size_t fread(void *ptr, size_t size, size_t nitems, FILE *stream);
```

The size of the integer used for each piece of data is part of the file format specification.

The first argument is a pointer to the data to write - it is a `void *` since it could be any type of data.

The next argument specifies the size of each item. If writing an `int` or an array of `int`s, we would pass in `sizeof(int)`. However, if we are reading and writing files, we probably want to work with the `int` types defined in `stdint.h`, which have their sizes fixed across systems (such as `int32_t` or `uint64_t`).

The third argument specifies how many such items should be read from the stream, and the final argument specifies from which stream to read.

The `fread` function returns how many items were successfully read. As with `fgets`, you should employ `feof` and/or `ferror` to obtain more information if `fread` returns fewer items than you requested. 

Resources
---------
* [Make an array of strings from a file in C][1] - using dynamic allocation

[1]: https://dev-notes.eu/2019/07/Build-an-Array-of-Strings-From-a-File-in-C/
