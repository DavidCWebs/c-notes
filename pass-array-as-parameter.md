# Passing Arrays as Parameters
Note that in C there is no way to get the size of an array that has been passed as a parameter.

Don't confuse this with strings - although strings are arrays of chars in C, they are (should be) NULL terminated, so their length can be determined by counting up to a `NUL` character. As such, strings are a special case.

The size of the array should therefore be passed in as a separate parameter.

Method 1: Pointer to First Element and Size
-------------------------------------------

```c
#include <stdio.h>
void arrayFunction(int *arr, size_t n)
{
	for (size_t i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}
}

int main()
{
	int myArr[] = {1, 2, 3, 4};
	arrayFunction(myArr);
	return 0;
}
```

Method 2: Pass Array as Parameter with Size
-------------------------------------------

```c
#include <stdio.h>
void arrayFunction(int arr[], size_t n) {
	for (size_t i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}
}
int main()
{
	int myArr[] = {1, 2, 3, 4};
	arrayFunction(myArr);
	return 0;
}
```
This method is preferred by some, as an array is explicitly passed. It is functionally equivalent to method 1. Though it is possible to pass in a size in the square brackets, the compiler will not check this is correct. Legal, but doesn't do anything and is also potentially confusing.


Array Pointers as Function Parameters
-------------------------------------
When a function parameter is a pointer that points at an array, it can be indexed as an array because it is an array under the hood. The name of an array variable is just a pointer.

Similarly, pointer arithmetic can also be applied to the array pointer. Such pointer arithmetic will be well defined as long as the resulting pointer remains within the bounds of the array - it is guaranteed that array elements are sequential in memory.

Arrays are Not (Exactly) Pointers
---------------------------------
Note the following:

```c
#include <stdio.h>

void printArr(int *arr, int n) {
	printf("n = %d\n", n); // n is correct
	for (int i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}
}

void faultyPrintArr(int *arr) {
	int n = sizeof(arr) / sizeof(arr[0]);
	printf("in function, sizeof(arr) / sizeof(arr[0]) = %lu\n", n); // Incorrect
	printf("n = %d\n", n);
	for (int i = 0; i < n; i++) {
		printf("%d\n", arr[i]);
	}
}

int main()
{
	int myArr[] = {1, 2, 3, 4};
	printf("in main, sizeof(myArr) = %lu\n", sizeof(myArr));
	printArr(myArr, sizeof(myArr)/sizeof(myArr[0]));
	faultyPrintArr(myArr);
	return 0;
}
```
Checking the size of an array - as in `main()` - is different to checking the size of a pointer - as in `faultyPrintArr()`.
