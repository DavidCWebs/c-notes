#include <stdio.h>

typedef struct node {
	int *p;
	int x;
} Node ;

int main()
{
	int num = 42;
	Node a = {&num, 13};
	printf("p = %d, x = %d\n", *a.p, a.x);

	Node *pa = &a;
	printf("p = %d, x = %d\n", *(pa->p), (*pa).x);

	// Code
	return 0;
}
