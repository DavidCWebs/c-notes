# Dynamic Memory Allocation With Malloc
To allocate memory dynamically (i.e. on the heap) `malloc()` and the related functions `calloc()` and `realloc()` are used.

The `malloc()` function allocates `size` bytes and returns a pointer to the allocated memory.The memory is notinitialized. If size is 0, then `malloc()` returns either `NULL`, or a unique pointer value that can later be successfully passed to `free()`

Function signature:

```c
void *malloc(size_t size);
```
Returns a pointer to the allocated memory, which is suitably aligned for any built-in type.

On error, returns `NULL`. `NULL` may also be returned by a successful call to `malloc()` with a size of zero.

```c
// Allocate memory for an array of 10 int pointers:
int *array = malloc(sizeof(*array) * 10);
```

The `size` parameter should be `sizeof(*type) * number_of_elements_required`.

The canonical way of doing this is to refer to the variable being declared. So if an array of `int` is declared as `int *myArray`, with space for `size_t n` elements, dynamic memory allocation looks like this:

```c
size_t n = 10;
int *myArray = malloc(sizeof(*myArray) * n);
```

Use in Functions
----------------
Allows memory to be dynamically allocated within a function, returning a pointer so that the memory block can be accessed within other functions.

Even though a function's stack frame is destroyed when the function goes out of scope, heap-allocated memory that has been allocated using `1malloc()` persists until it is freed.

Freeing Memory
--------------
Dynamically allocated memory must be explicitly freed using the `free()` function:

```c
void free(void *ptr);
```
`ptr` is the starting address for memory to be freed.

This de-allocates the memory associated with `*ptr` and it can no longer be used.

__You can't free anything other than a block in the heap.__

If the block being freed contains pointers to other dynamically allocated blocks of memory, free these __first__ - otherwise you will lose access to them, and it will not be possible to free them.

Double Free
-----------
You can't free the same block of memory twice - be careful when freeing copied blocks. Either free the original or the copy, not both.

Free Beginning og Block Only
----------------------------
If `*p` is a malloc'd block of memory and you increment it, it no longer points to the start of the block on the heap. It is therefore illegal to free it. Make a copy and iterate the copy, or keep a copy of the starting pointer.
