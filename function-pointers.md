# Function Pointers
The instructions that a programme executes are numbers stored in memory. Because these instructions have memory addresses, it is possible to have pointers to them.

When a pointer is assigned to the first instruction in a function, the pointer is said to be a pointer to the function.

In this way, functions can be assigned to variables, and passed into other functions as parameters.

Function Name
-------------
The name of a function (without parentheses) is a pointer to that function.

Functions as Parameters
-----------------------
When declaring a function that accepts a function pointer, the syntax needs to declare what the passed function returns and what parameters it accepts.


```c

#include <stdio.h>

int xor(int el, int x)
{
	return el ^ x;
}

int multiply(int el, int x)
{
	return el * x;
}

/**
* Change elements of data in place by applying the
* func function pointer.
* 
*/ 
void changeIntArray(int *data, size_t n, int x, int (*func)(int, int))
{
	for (size_t i = 0; i < n; i++) {
		data[i] = func(data[i], x);
	}
}

void printArray(int *data, size_t n)
{
	printf("{");
	for (size_t i = 0; i < n; i++) {
		printf((i > 0) ? ", %d" : "%d", data[i]);
	}
	printf("}\n");
}

int main()
{
	int data[] = {1, 2, 3, 4};
	printArray(data, 4);
	
	// Multiply all elements by 2
	changeIntArray(data, 4, 2, multiply);
	printArray(data, 4);

	// Xor all elements by 3
	changeIntArray(data, 4, 3, xor);
	printArray(data, 4);

	return 0;
}
```

Once the function that accepts a function pointer is defined (in this case, `changeIntArray()`), any function pointer of the appropriate type can be passed in.

In the example above, `changeIntArray(data, 4, 2, multiply);` results in every element in the `data` array being multiplied by 2.

In the same example, `changeIntArray(data, 4, 3, xor);` results in every element in the `data` array being xored by 3.

Address of Operator in Declaration
----------------------------------
Function that accept function pointers as parameters may be called with the address-of operator e.g. `changeIntArray(data, 4, 2, &multiply)`.

This syntax is legal, but the `&` operator is superfluous (as it is with the name of an array). The name of the function is already a pointer.

Note that if we have a function pointer other than the name of a function (i.e., a variable or a parameter), then we could take the address of that variable, giving us a pointer to a pointer to a function. It is best to use only the address-of operator in this latter case, which comes up rather infrequently.
