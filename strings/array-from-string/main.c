#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * Populate an array of strings, taking a string as input and splitting based
 * on the provided delimiter.
 * 
 * Returns the number of elements on success, -1 on failure.
 *
 * */
#define N_LINES 10
#define N_CHARS 20

ssize_t makeStringArray(const char *inStr, char ***arr, char *delim)
{
	// strtok changes the string it operates on, so we make a copy.
	char *str = calloc(strlen(inStr) + 1, sizeof(*str));
	strcpy(str, inStr);

	// Set up initial space: 10 lines, each line 20 chars - prevent too-frequent reallocs.
	*arr = calloc(N_LINES, sizeof(*arr));
	size_t nLines = 0; // Track space allocated for lines
	for (size_t i = 0; i < N_LINES; i++) {
		*(*arr + i) = calloc(N_CHARS, sizeof(***arr));
	}
	
	// First token	
	char *p = strtok(str, delim);
	size_t len = p ? strlen(p) : 0;
	nLines++;

	// Allocate space and store string
	if (len > N_CHARS - 1) {
		char *tmp = realloc(**arr, len + 1);
		if (!tmp) {
			fprintf(stderr, "realloc failed");
			return -1;
		}
		**arr = tmp;
	}
	strcpy(**arr, p);

	// NB This loops such that p == NULL is processed, because p is only set to NULL when strtok() has
	// consumed the entire string. This has the effect of adding a final element in the array which
	// consists of a single NULL character. An alternative would be to move the `p = strtok(NULL, delim)`
	// assignment into the while loops controlling expression, so the final iteration (when `p == NULL`)
	// does not proceed.
	while(p) {
		if (nLines > N_LINES -1) {
			*arr = realloc(*arr, nLines + 1);
		}
		p = strtok(NULL, delim);
		len = p ? strlen(p) : 0;
		if (len > N_CHARS - 1) {
			char *tmp = realloc(**(arr + nLines), len + 1);
			if (!tmp) {
				fprintf(stderr, "realloc failed.");
				return -1;
			}
			*(*arr + nLines) = tmp;
		}
		if (p) {
			strcpy(*(*arr + nLines), p);
		} else {
			memset(*(*arr + nLines), 0, 1);
		}
		nLines++;
	}
	free(str);
	return nLines - 1; // Allow for the last "sentinel" element, which is a NULL.
}


int main()
{
	char **arr = NULL;
	char str[] = "abc\ndef\nghi\njkl";
	size_t n = makeStringArray(str, &arr, "\n");
	printf("arr has %lu elements.\n", n);

	char **tracer = arr;
	while (**tracer) {
		printf("while: %s\n", *(tracer++));
	}

	for (size_t i = 0; i < n; i++) {
		printf("%s\n", arr[i]);
		free(arr[i]);
	}

	free(arr);
	return 0;
}
