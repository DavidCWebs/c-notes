# Compute the Fibonacci Sequence in C
The objective of this exercise is to compute a Fibonacci sequence from 0 up to a target integer.

Contrast two methods:

* Iterative, using a for loop and computing values in order
* Recursive, using dynamic programming techniques to improve efficiency

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

Computing the third number in the Fibonacci sequence would involve calling the computation for the second number twice.

References
----------
* [SO answer][1]
* [Dynamic Programming from Novice to Advanced][2]

[1]: https://cs.stackexchange.com/a/99517/104932
[2]: https://www.topcoder.com/community/competitive-programming/tutorials/dynamic-programming-from-novice-to-advanced/

