#include <stdio.h>
#include <stdlib.h>

#define SIZE 10

int *initArray(size_t size)
{
	int *p = malloc(size * sizeof(*p));
	for (size_t i = 0; i < size; i++) {
		*(p + i) = (int)i;
	}
	return p;
}


int main()
{
	int *myArray = initArray(SIZE);
	for (size_t i = 0; i < SIZE; i++) {
		printf("%d\n", myArray[i]);
	}
	free(myArray);
	return 0;
}
