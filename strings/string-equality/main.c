#include <stdio.h>

/**
 * This string comparison function accepts parameters defined
 * either as array of char (mutable) or const char * (immutable).
 * */
int stringEqual(const char *str1, const char *str2)
{
	const char *p1 = str1;
	const char *p2 = str2;
	while (*p1 == *p2) {
		if (*p1 == 0)
			return 1;
		p1++;
		p2++;
	}
	return 0;
}

int main()
{
	const char *s1 = "Dave";
	const char *s2 = "David";
	printf(stringEqual(s1, s2) ? "%s is equal to %s\n" : "%s is not equal to %s\n", s1, s2);
	
	char a1[] = "David";
	char a2[] = "David";
	printf(stringEqual(a1, a2) ? "%s is equal to %s\n" : "%s is not equal to %s\n", a1, a2);

	// Code
	return 0;
}
