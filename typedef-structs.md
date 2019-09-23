Typedef Structs
===============
Typedefs are a useful abstraction. They can save typing and define a particular type in a single place in the  codebase. This makes it easier to change the type.

On the other hand, using typedefs obscures your code somewhat - it's not obvious that you're dealing with a typedef'd struct when reading the codebase.


Define tag only
---------------

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

Define tag, then Define Type Alias
----------------------------------

```c
struct node_tag {
	int id;
	struct node_tag *next;
};
typedef struct node_tag Node;

// Usage:
int main()
{
	// In this case, the struct keyword is unnecessary
	Node first;
	first.id = 1;
	...
}
```

Declare & Define Struct in a Single Statement
---------------------------------------------

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

Typedef with no Tag Declaration
-------------------------------
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



