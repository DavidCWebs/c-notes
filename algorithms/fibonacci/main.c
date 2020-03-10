#include <stdio.h>

#define N 410

void iterativeFibonacci(int *resArray, int n)
{
	for (int i = 0; i < n; i++) {
		resArray[i] = i == 0 || i == 1 ? i : resArray[i-1] + resArray[i-2];
	}
}

int recursiveFibonacci(int *resArray, int n)
{
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


int main()
{
	int r[N];
	iterativeFibonacci(r, N);
	printArray(r, N);
	
	int r2[N] = { [0 ... N-1] = -1 };
	
	r2[0] = 0;
	r2[1] = 1;
	printArray(r2, N);
	recursiveFibonacci(r2, N - 1);
	printArray(r2, N);
	return 0;
}
