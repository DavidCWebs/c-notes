# Function Pointers in qsort()

In C, the `qsort()` function sorts an array in place using the [quickersort][1] algorithm - a variation of [quick sort][2].

Function Signature
------------------
```c
#include <stdlib.h>

void qsort(void *base, size_t nmemb, size_t size,
	int (*compar)(const void *, const void *));
```
Function arguments for `qsort()`:
1. `base`: pointer to the start of the array
2. `nmemb`: Number of members in the array
3. `size`: Size of an individual element in the array
4. `compar`: Pointer to a comparison function that accepts 2 x `const void *` arguments


To use `qsort()`, you need to include the stdlib.h header - i.e. `#include <stdlib.h>`. 

Comparison Function
-------------------
The comparison function must return an integer that is:
 
* Less than zero if the first argument is considered to be less than the second
* Zero if the arguments are equal
* Greater than zero if the first argument is considered to be greater than the second

Be careful with return values - especially if the values being compared are not integers.

**Use `>` or `<` rather than subtraction which may provide unexpected results if comparing non integer values.**

Generic Type Parameters
-----------------------
Note that the comparison function receives `const void *` as arguments - you need to cast these within the comparison function.

Example
-------
Sort an array of `Triangle` type defined objects according to their area.

Note that definition of the `area()` function has been omitted for brevity.

```c
typedef struct triangle
{
	int a;
	int b;
	int c;
} Triangle;


int compareTriangles(const void *x, const void *y)
{
	const Triangle *a = x, *b = y;
	int res = area(a) != area(b) ? area(a) > area(b) ? 1 : -1 : 0;
	return res;
}

/**
* Sort an array of Triangles
*/
void sort_by_area(Triangle* tr, int n) {
	qsort(tr, n, sizeof(Triangle), compareTriangles);	
}
```

Note the nested conditional in `compareTriangles()`:
* If area of a and b **are not** equal, return 1 if the area of a is greater than the area of b, -1 if not.
* If the area of a and b **are** equal, return 0.

Also note the line `const Triangle *a = x, *b = y;` which copies the input pointers into the object required for the comparison. 

[1]: https://en.wikipedia.org/wiki/Qsort
[2]: https://en.wikipedia.org/wiki/Quicksort
