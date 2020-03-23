#include <stdio.h>
#include <string.h>
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

int main(int argc, char **argv)
{
	char *endptr = NULL;
	int n = argc == 2 ? strtol(argv[1], &endptr, 10) : N;

	int r[n];
	iterativeFibonacci(r, n);
	printArray(r, n);
	
	int r2[n];
	memset(r2, -1, sizeof(*r2) * n);
	r2[0] = 0;
	r2[1] = 1;
	recursiveFibonacci(r2, n - 1);
	printArray(r2, n);
	printf("recursiveFibonacci() called %lu times.\n", count);
	return 0;
}
