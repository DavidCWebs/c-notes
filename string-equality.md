# String Equality
You can't use the `==` operator to check for string equality in C, as you might in Python, Javascript or other languages.

The equality operator will just check _pointer equality_ - `str1 == str2` checks if `str1` and `str2` point to the same location.

You may want this, but usually when comparing strings you are checking that the sequence of characters in each string is the same.

strcmp
------
The C library `strcmp()` function returns:

* 0 if the strings are equal
* A positive number if the first string is "greater than" the second string
* A negative number if the first string is "less than" the second string

In this context "greater than" and "less than" refer to lexicographic order —what you would think of as “alphabetical ordering,” but extended to encompass the fact that strings may have non-letters. The comparison is case sensitive.

Note that the C library has another function, `strcasecmp` which performs case-insensitive comparison.
