# Pointer Arithmetic

Incrementing an `int *` integer pointer makes it point to the "next" integer in memory.

The compiler emits instructions which actually add the number of bytes that an integer occupies in memory

For each type of pointer, adding 1 has a different meaning.

For an integer pointer, adding 1 means "one integer later in memory". Incrementing the pointer should have it point to the “next” integer in memory.i

The compiler emits instructions which actually add the number of bytes that an integer occupies in memory (e.g., +1 means to change the numerical value of the pointer by +4).

When adding N to a pointer to any type T, the compiler generates instructions which add (N * the number of bytes for values of type T) to the numeric value of the pointer - causing it to point N Ts further in memory.

Pointer arithmetic does not work with pointers to void - the compiler has no idea how big the pointed-at object is, therefore cannot N objects.

Undefined Behaviour
-------------------
If you move a pointer by means of pointer arithmetic and it points to a memory location outside the scope of the programme, _undefined behaviour_ may result. This should be considered erroneous.

C gives you a lot of rope when it comes to pointer assignment/arithmetic - C gives the compiler a lot of freedom with regard to control of memory.
