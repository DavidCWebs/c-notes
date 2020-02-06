# Shallow vs Deep Copy

When making a copy (e.g. of a struct pointer) be careful that you are not making a shallow copy when you require a deep copy:

```c
#include <stdio.h>
#include <stdlib.h>

typedef struct point {
	int x;
	int y;
} Point;

int main()
{
	Point *p1 = malloc(sizeof(*p1));
	p1->x = 1;
	p1->y = 1;

	// Shallow copy - same memory block as p1
	Point *p2 = p1;
	p2->x = -1;
	p2->y = 99;

	// p1 members have been amended
	printf("p1 = (%d, %d)\n", p1->x, p1->y);
	printf("p2 = (%d, %d)\n", p2->x, p2->y);

	// Deep copy - unique memory allocation
	Point *p3 = malloc(sizeof(*p3));
	p3->x = p1->x;
	p3->y = p1->y;

	p3->x = 42;
	// p1 members have NOT been amended
	printf("p1 = (%d, %d)\n", p1->x, p1->y);
	printf("p3 = (%d, %d)\n", p3->x, p3->y);


	free(p1);
	free(p3);
	return 0;
}

```
Be careful that you're not copying pointers (shallow copy), when you require a copy of values (a deep copy).

Be careful with more complex data structures - you may be copying a pointer to a struct which has fields taht are in turn dynamically allocated pointers.

In a shallow copy, each pointer in the shallow copy points at the same location in memory as the original. 
