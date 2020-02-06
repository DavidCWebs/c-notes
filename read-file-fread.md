# Reading & Writing to File in C

File Pointer
------------
### Open a File
Open a file and associate a stream with it using `fopen()`.

```c
FILE *fopen(const char *path, const char *mode);
```
Opens the file specified by `path` and returns a FILE pointer. The `mode` argument is a string that specifies the mode under which the file is opened:


* `r`: Reading, stream positioned at the beginning of the file.
* `r+`: Reading and writing, stream positioned at the beginning of the file.
* `w`: Truncate file to zero length or create text file for writing - stream positioned at the beginning of the file.
* `w+`: Reading and writing - file is created if it does not exist, otherwise it is truncated.  The stream positioned at the beginning of the file.
* `a`: Appending (writing at end of file) - file is created if it does not exist.  Stream positioned at the end of the file.
* `a+`: Reading and appending (writing at end of file) - file is created if it does not exist.  The initial file position for reading is at the beginning of the file, but output is always appended to the end of the file.

Returns a file descriptor - low level communication mechanism that is used to access a file (or pipe, or network socket).

On Linux, file descriptors are held in the kernel's global file table. This holds data relating to the inode of the file, access restrictions and byte-offset.

### Closing a File
`fclose(FILE *stream)` is used to close the specified stream. The act of closing sends buffered data to the OS and writes any buffered output data using `fflush()`. The underlying file descriptor is then closed.

On success, 0 is returned. Otherwise, EOF is returned, and `errno` is set to indicate the error.

`fclose()` can fail for a variety of reasons - for example:
 
* Data cannot be written to the disk drive
* Network connectivity is lost (in the case of a remote file system)

**Always check the return status of fclose()** - and at least report the error on failure.

On close, if the C library has unwritten data, a system call is made to the kernel to write data. The system call takes a file descriptor

Read a File With fread
----------------------
`fread()` is used for reading non-textual data from a file i.e. binary format file.

`fread()` prototype:

```c
size_t fread (void * ptr, size_t size, size_t nitems, FILE * stream);
```

Writing to a File
-----------------

References
----------
[*nix file descriptors][1]

[1]: https://en.wikipedia.org/wiki/File_descriptor
