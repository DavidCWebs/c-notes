# Recursion
Many algorithms involve repeating the same computation.

This can be achieved with iteration (e.g. while, for loops etc) or _recursion_.

Recursion involves an algorithm calling itself. Any recursive function can be written as an iterative function, but sometimes recursive functions can be easier to understand.

Example: Factorial
------------------

```c
#include <stdio.h>

int factorial(int a)
{
	// Base case - we know (trivially) that 0! = 1
	// This means that if a == 1, a! = 1 x 0! = 1 x 1 = 1
	if (a == 1)
		return a;
	return a * factorial(a - 1);
}

int main()
{
	printf("%d\n", factorial(5));
	return 0;
}
```

Tail Recursion
--------------
The example above uses _head recursion_ - computation is performed after the function makes a recursive call.

In a _tail recursive_ function, the only recursive call is in the return statement - as soon as the recursive call is made, the function returns it's result without further computation.

Generally, a _tail call_ is when the caller returns immediately after the called function returns - in other words:

A recursive function is tail recursive if it's recursive call is a tail call.

Tail recursion allows the compiler to optimise the code such that instead of allocating a stack frame for each recursive call, the current stack frame is reused.

Most of the stack frame for the current procedure is no longer needed, and can be reused by the frame of the tail call. In this way, a tail recursive function only uses a single stack frame as opposed to many. If the required computations are large enough, this can make a significant difference and may prevent stack overflow.

Tail Recursive Example
----------------------
```c
#include <stdio.h>

int factorialTail(int n, int ans)
{
	if (n <= 1)
		return ans;
	// The recursive call is the last computation for this
	// function - tail recursion.
	return factorialTail(n - 1, ans * n); 
}

int main()
{
	printf("%d\n", factorialTail(5, 1));
	return 0;
}
```
Because the function needs to be initialised with a starting `ans` of 1, this may be confusing. To avoid the potential confusion that may arise when calling the function - i.e. to compute the factorial of a number `n` you should only expect the calling code to supply `n` - the computation can be wrapped in a helper function:

```c
#include <stdio.h>

int factorialTail(int n, int ans)
{
	if (n <= 1)
		return ans;
	return factorialTail(n - 1, ans * n); 
}

/*
* Abstracts away the second parameter for the caller
*/
int factorial(int n)
{
	// Second parameter will always be 1
	return factorialTail(n, 1);
}

int main()
{
	printf("%d\n", factorial(5));
	return 0;
}
```

Note that as soon as the tail recursive call is made, the stack frame is no longer needed - there is no value in the frame that will be used again.

The compiler recognises this, and performs what is known as tail recursion elimination - recursive calls do not result in unique stack frames. Instead, the compiler updates the relevant values inside the current frame as a means of recursion.

The answer is carried with each call, accumulating it's value.

Equivalence of Tail Recursion and Iteration
-------------------------------------------
In terms of computing resources, tail recursion and iteration are equivalent.

Any algorithm written with iteration can be re-written using tail recursion, and vice versa.

A smart compiler will compile tail recursion and iteration to an identical set of instructions.

The equivalence of tail recursion and iteration is important for functional programming languages. In a purely functional language, you cannot modify a value once you create it. As such, there are no loops (which typically require modifying variables to change the conditions) - only recursive functions. What would typically be written as a loop is instead written as a tail recursive function.

Resources
---------
* [Tail call][1], Wikipedia

[1]: https://en.wikipedia.org/wiki/Tail_call
