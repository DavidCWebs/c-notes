Pointer Arithmetic with Multiple Indirection
============================================
It's useful to really understand pointer arithmetic in C - though in most situations you'd probably be better off using the array subscript operator (`[]`).

The `*` dereferencing operator has precedence over the addition `+` operator.

For the following examples, we'll use multiple indirection to create an abstract data structure `doc` to represent this string:

```c
char str[] = "hello world. abc def.\nxyz";
```
...as a multidimensional array. The string could be represented as a document `doc` whereby:

- `doc`: contains multiple `paragraphs` - sequences of characters delimited by newline ('\n') characters
- `paragraph`: contains multiple sentences - sequences of characters delimited by fullstop ('.') characters
- `sentence`: contains multple words -sequences of characters delimited by space (' ') characters
- `word`: contains multiple characters, with no spaces and terminated by a `NUL` character

The underlying data type in this example is a `char`. This means:

- Words are pointers to `char`s (an array of `char`s): `char *`
- Sentences are pointers to words (an array of arrays): `char **`
- Paragraphs are pointers to sentences (an array of arrays of arrays): `char ***`
- The Document is a pointer to paragraph(s) - an array of arrays of arrays of arrays: `char****`.

Data Structure:
```
char ****doc = NULL;

// Assume space has been allocated:
doc[0][0][0] = "hello";
doc[0][0][1] = "world";
doc[0][1][0] = "abc";
doc[0][1][1] = "def";
doc[1][0][0] = "xyz";
```

Resulting Data structure:
```
// Document
{
	// Paragraph 0
	{
		// Sentence 0
		{"hello", "world"},
		// Sentence 1
		{"abc", "def"}
	},
	// Paragraph 1
	{
		// Sentence 0
		{"xyz"}
	}
}
```

Example: `*(**doc + 1))`
------------------------

- `doc`: This variable holds the address of the first highest level array - a pointer to first paragraph
- `*doc`: Dereference `doc` to get a pointer to the first sentence in the first paragraph.
- `**doc`: Dereference this to get a pointer to the first word in the first sentence of the first paragraph.
- `**doc + 1`: Add 1 to this to move the pointer to the second word of the sentence.
- `*(**doc + 1)`: Dereference this to get a printable string - a pointer to a null terminated array of chars.
 
```c
printf("%s\n", *(**doc + 1));
// Output: "world"
```

Example: `*(*(*doc + 1) + 1)`
-----------------------------

- `*doc + 1`: Dereference `doc` to get a pointer to first sentence in paragraph 0, then add 1 to get a pointer to sentence 2.
- `*(*doc + 1) + 1`: Dereference the pointer to sentence to get a pointer to first word, add 1 to get a pointer to second word.
- `*(*(*doc + 1) + 1)`: Dereference this to print the string.

```c
printf("%s\n", *(*(*doc + 1) + 1));
// Output: "def"
```


```c
//                          para index 0
//                          |
//                          |    sentence index 1
//                          |    |
//                          |    |    word index 0
//                          |    |    |
//              	    |    |    |    character index 1
//                          ↓    ↓    ↓    ↓ 
char letter = *(*(*(*(doc + 0) + 1) + 0) + 1);
// equivalent:
char letter = doc[0][1][0][1];
```

```c
>>> p **(*(*doc+1)+1)
$112 = 100 'd'

>>> p *(*(*(*doc+1)+1)+1)
$113 = 101 'e'

>>> p *(*(*(*doc+1)+1)+2)
$114 = 102 'f'
>>> 

char ****doc;

doc[0][0][0] == "hello"
doc[0][0][1] == "world"
doc[0][1][0] == "abc"
doc[0][1][1] == "def"

>>> p *(*(*doc+0)+0)
$117 = 0x602680 "hello"

>>> p *(*(*doc+0)+1)
$118 = 0x6026a0 "world"
```

- `*doc`: Dereference `doc` once, giving a pointer to the first sentence in the first paragraph.
- `*doc + 1`: Add 1 to this value - providing a pointer to the second sentence.
- `*(*doc + 1)`: Dereference this, giving a sentence (an array of words).
- `*(*doc + 1) + 0`: Add zero to pointer - which still points to the first array of words (sentence).
- `*(*(*doc + 1) + 0)`: Dereference this to print, generating tdoche first word in the second sentence of the first paragraph

```c
>>> p *(*(*doc+1)+0)
$119 = 0x6026c0 "abc"


>>> p *(*(*doc+1)+1)
$120 = 0x6026e0 "def"

```
