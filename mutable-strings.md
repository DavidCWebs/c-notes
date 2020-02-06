# Mutable Strings
Strings can be declared as an array of characters or as a pointer to a character. In either case, a character string literal can be used to initialise the value.

String literals are a collection of characters surrounded by double quotes. The terminating ‘\0’ character is implicit.

For a string to be mutable, it must reside in writeable memory, such as the frame of a function or memory that is dynamically allocated by malloc. To make space for a string in a function's stack frame, an array of chars must be declared with sufficient space to hold all of the string's characters plus the null terminator.

Initialise Char Array String
----------------------------

```c
char str[] = "Hello";
```
This is equivalent:

```c
char str[] = {'H', 'e', 'l', 'l', 'o', '\0'};
```

In both cases, a variable `str` is declared, with `str` being an array of 6 `char`s - one char for each letter in the string with one `char` for the terminating null character.

Caveats
-------
Though a char array can be declared with an explicit size, there must be enough space allocated for the null terminator. If not enough space is allocated, the string will still be stored in memory - but the null terminator will not be present:

```c
char str[5] = "Hello"; // Logical enough right? Since "Hello" has 5 letters...
``` 
The above example will store the relevant chars as a char array, but it will not be null terminated. It is a valid __array of characters__, but it is NOT a valid __string__. If you try to use such a variable as a string, trouble will ensue - the array will be accessed past it's bounds, since functions that handle strings generally use the null terminator to indicate the end of the string.

Failing to null-terminate a string may not always appear in testing - you might be lucky if the next byte of memory just happens to be a 0 - terminating the string accidentally. While this may seem fortuitous since the programme "works" - it is actually a dangerous sort of problem. The programme may be tested many times without exhibiting any errors - which may be stored up for deployment where differing conditions may cause the programme to crash or produce incorrect results.

Use tools such as valgrind which are capable of detecting this sort of error.

Space Requirements
------------------
It is valid to request more space than is required for a string - which may be necessary if you plan to concatenate more characters onto the string.

```c
char str[42] = "Hello"; // OK and will be null terminated.
```
