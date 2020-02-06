# Array of Strings

An array of strings is a multidimensional array of characters. Strings themselves are arrays of characters with a null terminator. Because of this all the same rules apply to arrays of strings, and we can represent an array of strings as either `char **` or `char (*)[]`

Consider the following two statements, each of which declares a multidimensional array of chars, and initializes it with a braced array of string literals:

```c
char strs[3][4] = {"Abc", "def", "ghi"};
char chrs[3][3] = {"Abc", "def", "ghi"};
```

The difference between the two declarations is the size of the second dimension of the array - 4 in the first statement, and 3 in the second.

The first statement (which declares `strs`) includes space for the null terminator, which is required to make the sequence of characters a valid string. The second statement, which declares `chrs`, does not include such space and only stores the characters that were written (with no null terminator).

The first case is an array of strings. The second is an array of character arrays (none of which are null terminated - as such they are not strings).

This second statement is fine if you intend to use `chrs` as a multidimensional array of characters, and not use its elements for anything which expects a null terminated string. It is a valid multidimensional array of chars and isn't illegal.

When declaring arrays of strings (multi-dimensional arrays of chars) you cannot omit the size from the second dimension (which is the number of characters in each string). You can only omit only the first dimensions of a multidimensional array.

If you declare a multidimensional array of chars to hold strings of different lengths, then you must size the second dimension according to the length of the longest string. For example:

```c
char words[4][7] = {"Out", "of", "cheese", "error."};
```

In this example, `words` requires 28 bytes (characters) of storage despite the fact that the strings used to initialize it occupy 15 bytes. This representation wastes some space. While that waste may not be significant in this example, if we were instead looking at millions of strings with lengths that vary greatly, we might be wasting megabytes.

We might instead use the [array-of-pointers][1] representation for an array of strings. Representing multidimensional data with an array of pointers allows us to have items of different lengths, which naturally solves the problem of wasted space. To represent our array of strings like this:

```c
const char * words[] = {"Out", "of", "cheese", "error."};
```

Words are declared words as an array of `const char *`s - the elements of the array are pointers to `const chars`, and thus the chars they point to are immutable.

We should include the `const` (and must include it to be const-correct) as we have indicated that words should be initialized to pointers to string literals, which are in read-only memory.

__It is common to end an array of strings with a NULL pointer__:

```c
const char * words2[] = {"Out", "of", "cheese", "error.", NULL};

// Allows looping over the array as string (i.e. until NULL)
const char ** ptr = words2;
while (*ptr != NULL) {
  printf("%s ", *ptr);
  ptr++;
}
printf("\n");
```

[1]: /array-of-pointers.html
