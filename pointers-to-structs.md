# Pointers to Structs
Pointers to structs are very common.

When dereferencing struct fields, remember that order of operations means that the `.` operation happens before the `*` operation. This means that `*a.b` means "dereference the b field from the struct a".

If `a` is a pointer to a struct, this won't work. You need to use parentheses: `(*a).b` which means "dereference a and get the member field b".

You can use `a->b` as a shorthand to say "dereference a and get the member field b". When `a` is a pointer to a struct, `a->b` and `(*a).b` are equivalent expressions.

Example
------- 

```c

#include <stdio.h>

typedef struct node {
	int *p;
	int x;
} Node ;

int main()
{
	int num = 42;
	Node a = {&num, 13};

	// Basic struct
	printf("p = %d, x = %d\n", *a.p, a.x);
	
	// Pointer to struct
	Node *pa = &a;
	printf("p = %d, x = %d\n", *(pa->p), (*pa).x);

	return 0;
}
```
