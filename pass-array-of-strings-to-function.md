# Pass Array of Strings as a Function Parameter

Note that `char *[]` decays into a `char **`.

Example
-------

```c
#include <stdio.h>

char *func(const char **input, size_t n)
{
	for (size_t i = 0; i < n; i++) {
		printf("%s\n", input[i]);	
	}
	return "world";
}

int main()
{
	const char *input[] = {
		"david",
		"egan"
	};
	func(input, sizeof(input) / sizeof(input[0]));
	return 0;
}
```
