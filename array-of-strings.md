# Array of Strings

An array of strings is a multidimensional array of characters. Strings themselves are arrays of characters with a null terminator. Because of this all the same rules apply to arrays of strings, and we can represent an array of strings as either `char **` or `char (*)[]`

Consider the following two statements, each of which declares a multidimensional array of chars, and initializes it with a braced array of string literals:

```c
char strs[3][4] = {"Abc", "def", "ghi"};
char chrs[3][3] = {"Abc", "def", "ghi"};
```

The difference between the two declarations is the size of the second dimension of the array - 4 in the first statement, and 3 in the second.

The first statement (which declares `strs`) includes space for the null terminator, which is required to make the sequence of characters a valid string. The second statement, which declares `chrs`, does not include such space and only stores the characters that were written (with no null terminator).

In the first case, we have an array of strings. The second is an array of character arrays (none of which are null terminated - as such they are not strings).

This second statement is correct if we intend to use `chrs` only as a multidimensional array of characters, and not use its elements for anything which expects a null terminated string.

The second statement makes a valid multidimensional array of chars and is not illegal - it will not produce an error or a warning.

This behavior is much the same as we discussed previously, for just declaring arrays of characters and initializing them from string literals. However, a significant difference is that in the multidimensional case, we cannot omit the size from the second dimension (which is the number of characters in each string), as C allows us to omit only the first dimensions of a multidimensional array.

If you declare a multidimensional array of chars to hold strings of different lengths, then you must size the second dimension according to the length of the longest string. For example, we might declare the following array:

```c
char words[4][10] = {"A", "cat", "likes", "sleeping."};
```

In this example, `words` requires 40 characters of storage despite the fact that the strings used to initialize it only occupy 22 characters. This representation wastes some space. While that waste may not be significant in this example, if we were instead looking at millions of strings with lengths that vary greatly, we might be wasting megabytes.

We might instead use the [array-of-pointers][1] representation for an array of strings. As we previously discussed, representing multidimensional data with an array of pointers allows us to have items of different lengths, which naturally solves the problem of wasted space. To represent our array of strings in this fashion, we might declare and initialize words as follows:

```c
const char * words[] = {"A", "cat", "likes", "sleeping."};
```

Observe that here, we declare words as an array of `const char *`s - the elements of the array are pointers to `const chars`, and thus the chars they point to may not be modified.

We should include the `const` (and must include it to be const-correct) as we have indicated that words should be initialized to pointers to string literals, which are in read-only memory.

We will note that it is common to end an array of strings with a NULL pointer, such as this:

```c
const char * words2[] = {"A", "cat", "likes", "sleeping.", NULL};

// Allows looping over the array as string (i.e. until NULL)
const char ** ptr = words2;
while (*ptr != NULL) {
  printf("%s ", *ptr);
  ptr++;
}
printf("\n");
```

[1]: /array-of-pointers.html
