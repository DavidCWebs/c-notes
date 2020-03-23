# Compute the Fibonacci Sequence in C
The objective of this exercise is to compute a Fibonacci sequence up to a target number of elements, saving the sequence as an array.

The Fibonacci sequence is the sequence of numbers such that each number is the sum of the two preceding numbers, starting from 0 and 1. For example, the first 6 Fibonacci numbers are:

`0, 1, 1, 2, 3, 5`

The exercise contrasts two methods:

* Iterative, using a for loop and computing values in order
* Recursive, using dynamic programming technique (memoization) to improve efficiency

Iterative
---------
The iterative method is straightforward - loop from zero up to the target, setting the current element to:

* 0 if the current element is at index 0.
* 1 if the current element is at index 1.
* The sum of the elements at the previous two adjacent indices otherwise.

```c
void iterativeFibonacci(int *resArray, int n)
{
	for (int i = 0; i < n; i++) {
		resArray[i] = i == 0 || i == 1 ? i : resArray[i-1] + resArray[i-2];
	}
}
```

Recursive, with Dynamic Programming Caching
-------------------------------------------
Simple recursive calls (in a tree structure) would involve multiple repeat calls performing the same calculation.

Computing the 4th number in the Fibonacci sequence would involve calling:

* `fib(4)` once
* `fib(3)` once
* `fib(2)` twice
* `fib(1)` three times
* `fib(0)` twice

fib(4)
|     \
|      \
|       \
|        \
fib(3)	  fib(2)--
|    \     \      \
|     \	    \      \
|      \     \      \	
fib(2) fib(1) fib(1) fib(0)
|    \
|     \
|      \
fib(1)	fib(0)


For example, a naive recursive implementation in C looks like this:
```c
int fib(int n)
{
	if (n < 2) {
		return n;
	}
	return fib(n - 2) + fib(n - 1);
}
```
The number of function calls grows out of proportion as you calculate higher numbers in the sequence: computing the 10th number in the Fibonacci sequence calls `fib()` 177 times - computing the 20th number calls `fib()` 21891 times. Each call to the function requires a stack frame, so this approach is quite inefficient both in terms of time and space complexity.

We can do better by storing results as we go - a dynamic programming technique called _memoization_.

### Memoization
This can be implemented by using an array to hold successive numbers in the sequence. For each recursive call, we check to see if the value has already been computed by looking in the cache. If has been previously computed, we return this value. Otherwise, we perform the computation and add this to the cache.

```c
#include <stdio.h>
#include <stdlib.h>

#define N 10
static size_t count = 0;

void iterativeFibonacci(int *resArray, int n)
{
	for (int i = 0; i < n; i++) {
		resArray[i] = i == 0 || i == 1 ? i : resArray[i-1] + resArray[i-2];
	}
}

int recursiveFibonacci(int *resArray, int n)
{
	count++;
	if (resArray[n] == -1) {
		resArray[n] = recursiveFibonacci(resArray, n - 1) + recursiveFibonacci(resArray, n - 2);
	}
	return resArray[n];
}

void printArray(int *arr, int n) {
	for (int i = 0; i < n; i++) {
		printf(i == 0 ? "[ %d" : ", %d", arr[i]);
	}
	puts(" ]\n");
}

int main(void)
{
	int r[N];
	iterativeFibonacci(r, N);
	printArray(r, N);
	
	int r2[N] = { [0 ... N-1] = -1 };
	r2[0] = 0;
	r2[1] = 1;
	recursiveFibonacci(r2, N - 1);
	printArray(r2, N);
	printf("recursiveFibonacci() called %lu times.\n", count);
	return 0;
}
```

Using this method, computing the 20th number in the Fibonacci sequence requires 37 calls to `recursiveFibonacci()`. We also have the additional benefit of having the entire sequence up to and including our target in our cache array, for very little extra cost.

References
----------
* [SO answer][1]
* [Dynamic Programming from Novice to Advanced][2]

[1]: https://cs.stackexchange.com/a/99517/104932
[2]: https://www.topcoder.com/community/competitive-programming/tutorials/dynamic-programming-from-novice-to-advanced/

