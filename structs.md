# C Structs
A C structure (struct) is a composite data type that defines a group of (usually related) data under a single name. A struct is held in a single block of memory, allowing different variables to be accesssed by a single pointer or struct declared name.

The data contained within a struct are known as __members__ in C parlance - in other languages structures may be called _records_ and members may be known as _fields_.

The members of a struct may have different data types from one another, so structs are a logical choice for grouping related mixed-type data (e.g. a `Person` struct may have `name`, `id`, `location` members). 

A C struct references a contiguous block of phsyical memory. When storing a struct in dynamic memory, the `sizeof` operator is used to determine the number of bytes needed for storage. The struct may contain members which are themselves pointers to dynamically allocated memory.

Declaration
-----------
The syntax for declaration is:

```c
struct tag_name {
	type name_of_member_1;
	type name_of_member_2;
	// Declare members as necessary - size must be known at compile time.
};
```
You don't necessarily need a tag name: see the section on Typedef & Structs.

Initialising
------------
There are three ways to initialise a struct.

* When member lists are in order, initialise in place: `struct coord a = { 1, 2 };`
* When member lists are not in order, use designated initialisers: `struct coord a = { .y  = 2, .x = 1 }`
* By copying an existing struct of the same type: `struct a = b;`

If a struct is declared `static`, omitted members are initialised to 0.

Typedef Structs
---------------
Type definitions can help to make a programme more understandable. They often save typing and allow you to define a particular type in a single place in the codebase, making it easier to make changes.

On the other hand, using typedefs can obscure your code - it may not be obvious that you're dealing with a `typedef` defined struct when reading the codebase.


### Define tag only
Define a struct, without making a type definition:

```c
struct node_tag {
	int id;
	struct node_tag *next;
};

// Usage:
int main()
{
	struct node_tag first;
	first.id = 1;
	...
}
```

### Define tag, then Define Type Alias

```c
struct node_tag {
	int id;
	struct node_tag *next;
};
typedef struct node_tag Node;

// Usage:
int main()
{
	// In this case, we can use our defined type without the struct keyword
	Node first;
	first.id = 1;
	...
}
```

### Declare & Define Struct in a Single Statement

```c
typedef struct node_tag {
	int id;
	struct node_tag *next;
} Node;

// Usage:
int main()
{
	// Usage as above
	Node first;
	first.id = 1;
	...
}
```

### Typedef with no Tag Declaration
When defined in this way, a struct can't refer to it's own type.

```c
typedef struct {
	int id;
	// Can't refer to this type as in the `next` field above.
} Node;

// Usage:
int main()
{
	// In this case, the struct keyword is unnecessary
	Node first;
	first.id = 1;
	...
}
```

