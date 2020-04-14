General Notes

Always count from zero and add since you index from zero.

Always use sizeof(arrayvar[0]) instead of the underlying element type and use the temporary, the optimizer will get rid of it

Always sentinel an array of pointers with a null, you never know if the size and the result will get separated

NEVER strcpy(), and check out why we made line_length
