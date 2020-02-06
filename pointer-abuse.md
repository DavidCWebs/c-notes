# Pointer Abuse

If you have a float `a`, you can assign an integer pointer to the address of `a` by casting:

```c

float a = 3.14;

int *p = (int *) &a;
printf("%d\n", p);

// prints 1078523331
```
The int pointer `*p` looks at the bit pattern at `&a` and interprets this as an int, without any further interpretation.

This probably constitutes pointer abuse.
