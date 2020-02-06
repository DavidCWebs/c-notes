# Realloc
Resize an allocated block of heap memory.

```c
void *realloc(void *ptr, size_t size);
```

The `realloc()` function changes the size of the memory block pointed to by `ptr` to `size` bytes. The contents are not changed in the range from the start of the region up to the minimum of the old and new sizes.

* If the new size is larger than the old size, the added memory will not be initialized.
* If `ptr` is `NULL`, then the call is equivalent to `malloc(size)`, for all values of size.
* If `size` is equal to zero, and `ptr` is not `NULL`, then the call is equivalent to `free(ptr)`

Unless `ptr` is NULL, it must have been returned by an earlier call to `malloc()`, `calloc()` or `realloc()`. If the area pointed to was moved, a `free(ptr)` takes place.

Dangers of Overwriting
----------------------
Don't just overwrite with `realloc` - the original pointer may be lost if `realloc` fails.

Instead, use a temporary pointer:

```c
#include <stdio.h>
#include <stdlib.h>

int main()
{

	size_t sizeIncrement = 10;
	int *intArray = malloc(sizeIncrement * sizeof(*intArray));
	for (size_t i = 0; i < 10; i++)
		intArray[i] = i;

	// Need more space for an additional 10 elements
	// ---------------------------------------------
	// Don't just overwrite with realloc - the original
	// pointer may be lost if realloc fails:

	sizeIncrement+= 10; 
	int *tmp = realloc(intArray, sizeIncrement * sizeof(*tmp));
	if (!tmp) {
		perror("realloc");
		return EXIT_FAILURE;
	}
	intArray = tmp;

	for (size_t i = 10; i < 20; i++)
		intArray[i] = i;

	for (size_t i = 0; i < 20; i++)
		printf("el %lu = %d\n", i, intArray[i]);

	free(intArray);
	return 0;
}
```
 
