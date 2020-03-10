# Initialize a C Array with Values
For the GCC compiler, you can initialize an element to a particular value by specifying the array index and associated value.

For example:

```c
...
int a[5] = { [1] = 42, [4] = 42 };

// Equivalent to:
int a[5] = { 0, 42, 0, 0, 42 };

```
You can also intialise a range of elements by using the format `[first ... last] = value`

This is a GNU extension.

Initialise All Elements to the Same Value
-----------------------------------------
The following complete example shows how this technique can be used to initialize all elements in an array to the same value:

```c
#include <stdio.h>
#define N 5

void printArray(int *arr, int n) {
	for (int i = 0; i < n; i++) {
		printf(i == 0 ? "[ %d" : ", %d", arr[i]);
	}
	puts(" ]\n");
}

int main()
{
	// Incorrect method
	int arr[N] = { 42 };
	printArray(arr, N);
	// Output: [ 42, 0, 0, 0, 0 ]
	
	int arr2[N] = { [0 ... N - 1] = 42 };
	printArray(arr2, N);
	// Output: [ 42, 42, 42, 42, 42 ]

	return 0;
}
```

References
----------
* [GCC Documentation][1]

[1]: https://gcc.gnu.org/onlinedocs/gcc-4.1.2/gcc/Designated-Inits.html
