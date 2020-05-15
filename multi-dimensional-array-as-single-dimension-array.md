# Simulated Multidimensional Array in C
Represent a multidimensional array as a 1d array by using offsets to compute the array index.

For stack allocated multi-dimensional arrays, sub-arrays won't necessarily be stored in contiguous memory, which may not be optimal for performance.

A multi dimensional array can be mimicked by use of a single array with appropriate offsets.

## Example Array
For a conceptual "3D" array `array3d[xmax][ymax][zmax]`, the total number of elements required to represent this as a flat array is `xmax * ymax * zmax` - so theh array should be initialized with `array3d[xmax * ymax * zmax]`.

Array indexes are then calculated with an offset to provide the multi-dimensional behaviour.

`array[f(x, y, z)]` simulates `array[x][y][z]`, where `f(x, y, z)` returns an integer index.

To calculate index `i` for `array3d[x][y][z]`:

` i = (x * (ymax * zmax)) + (y * zmax) + z`

## Array Visualisation
```
i     x     y     z     val
---------------------------
0     0     0     0     A00
1     0     0     1     A01
2     0     0     2     A02
3     0     1     0     A10
4     0     1     1     A11
5     0     1     2     A12
6     0     2     0     A20
7     0     2     1     A21
8     0     2     2     A22
9     1     0     0     B00
10    1     0     1     B01
11    1     0     2     B02
12    1     1     0     B10
13    1     1     1     B11
14    1     1     2     B12
15    1     2     0     B20
16    1     2     1     B21
17    1     2     2     B22
18    2     0     0     C00
19    2     0     1     C01
20    2     0     2     C02
21    2     1     0     C10
22    2     1     1     C11
23    2     1     2     C12
24    2     2     0     C20
25    2     2     1     C21
26    2     2     2     C22
```
To access `array[2][1][1]`, `flatArray[f(2, 1, 1)]` is used. This is computed to retrieve `flatArray[22]` - in this case the value C11 is retrieved.

## Code
```c
#include <stdio.h>
#define DIMENSION_1 3
#define DIMENSION_2 3
#define DIMENSION_3 5

int getIndex(int i, int j, int k);
void output(const int *array, int size);

int main(void)
{
    printf("\nOne dimensional array mimicking 3d array:\n");
    const int num_elements = DIMENSION_1 * DIMENSION_2 * DIMENSION_3;
    int single3d[num_elements];
    int val = 0;
    int index = 0;

    for (int x = 0; x < DIMENSION_1; x++) {
        for (int y = 0; y < DIMENSION_2; y++) {
            for (int z = 0; z < DIMENSION_3; z++) {
                val = (x + 1) * (y + 1) * (z + 1);
                index = getIndex(x, y, z);
                single3d[index] = val;
                printf(z < DIMENSION_3 - 1 ? "%d: %d, " : "%d: %d", index, val);
            }
            printf(" | ");
        }
        printf("\n");
    }

    output(single3d, num_elements);
    printf("\nGet single3d[1][1][2]:");
    printf(" %d\n", single3d[getIndex(1, 1, 2)]);

    return 0;
}

int getIndex(int x, int y, int z)
{
    if (x >= DIMENSION_1 || y >= DIMENSION_2 || z >= DIMENSION_3) {
        return 1;
    }
    return (x * (DIMENSION_3 * DIMENSION_2)) + (y * DIMENSION_3) + z;
}

void output(const int *array, int size)
{
    int index = 0;
    printf("Size: %d\n", size);
    for (int x = 0; x < DIMENSION_1; x++) {
        for (int y = 0; y < DIMENSION_2; y++) {
            for (int z = 0; z < DIMENSION_3; z++) {
                index = getIndex(x, y, z);
                printf("array[%d][%d][%d] = %d\t", x, y, z, array[index]);
                printf("Index: %d, Value: %d\t%p\n", index, ((x + 1) * (y + 1) * (z + 1)), (void*)&array[index]);
            }
        }
    }

}
```

Output:

```
One dimensional array mimicking 3d array:
0: 1, 1: 2, 2: 3, 3: 4, 4: 5 | 5: 2, 6: 4, 7: 6, 8: 8, 9: 10 | 10: 3, 11: 6, 12: 9, 13: 12, 14: 15 | 
15: 2, 16: 4, 17: 6, 18: 8, 19: 10 | 20: 4, 21: 8, 22: 12, 23: 16, 24: 20 | 25: 6, 26: 12, 27: 18, 28: 24, 29: 30 | 
30: 3, 31: 6, 32: 9, 33: 12, 34: 15 | 35: 6, 36: 12, 37: 18, 38: 24, 39: 30 | 40: 9, 41: 18, 42: 27, 43: 36, 44: 45 | 
Size: 45
array[0][0][0] = 1	Index: 0, Value: 1	0x7ffd3c6681a0
array[0][0][1] = 2	Index: 1, Value: 2	0x7ffd3c6681a4
array[0][0][2] = 3	Index: 2, Value: 3	0x7ffd3c6681a8
array[0][0][3] = 4	Index: 3, Value: 4	0x7ffd3c6681ac
array[0][0][4] = 5	Index: 4, Value: 5	0x7ffd3c6681b0
array[0][1][0] = 2	Index: 5, Value: 2	0x7ffd3c6681b4
array[0][1][1] = 4	Index: 6, Value: 4	0x7ffd3c6681b8
array[0][1][2] = 6	Index: 7, Value: 6	0x7ffd3c6681bc
array[0][1][3] = 8	Index: 8, Value: 8	0x7ffd3c6681c0
array[0][1][4] = 10	Index: 9, Value: 10	0x7ffd3c6681c4
array[0][2][0] = 3	Index: 10, Value: 3	0x7ffd3c6681c8
array[0][2][1] = 6	Index: 11, Value: 6	0x7ffd3c6681cc
array[0][2][2] = 9	Index: 12, Value: 9	0x7ffd3c6681d0
array[0][2][3] = 12	Index: 13, Value: 12	0x7ffd3c6681d4
array[0][2][4] = 15	Index: 14, Value: 15	0x7ffd3c6681d8
array[1][0][0] = 2	Index: 15, Value: 2	0x7ffd3c6681dc
array[1][0][1] = 4	Index: 16, Value: 4	0x7ffd3c6681e0
array[1][0][2] = 6	Index: 17, Value: 6	0x7ffd3c6681e4
array[1][0][3] = 8	Index: 18, Value: 8	0x7ffd3c6681e8
array[1][0][4] = 10	Index: 19, Value: 10	0x7ffd3c6681ec
array[1][1][0] = 4	Index: 20, Value: 4	0x7ffd3c6681f0
array[1][1][1] = 8	Index: 21, Value: 8	0x7ffd3c6681f4
array[1][1][2] = 12	Index: 22, Value: 12	0x7ffd3c6681f8
array[1][1][3] = 16	Index: 23, Value: 16	0x7ffd3c6681fc
array[1][1][4] = 20	Index: 24, Value: 20	0x7ffd3c668200
array[1][2][0] = 6	Index: 25, Value: 6	0x7ffd3c668204
array[1][2][1] = 12	Index: 26, Value: 12	0x7ffd3c668208
array[1][2][2] = 18	Index: 27, Value: 18	0x7ffd3c66820c
array[1][2][3] = 24	Index: 28, Value: 24	0x7ffd3c668210
array[1][2][4] = 30	Index: 29, Value: 30	0x7ffd3c668214
array[2][0][0] = 3	Index: 30, Value: 3	0x7ffd3c668218
array[2][0][1] = 6	Index: 31, Value: 6	0x7ffd3c66821c
array[2][0][2] = 9	Index: 32, Value: 9	0x7ffd3c668220
array[2][0][3] = 12	Index: 33, Value: 12	0x7ffd3c668224
array[2][0][4] = 15	Index: 34, Value: 15	0x7ffd3c668228
array[2][1][0] = 6	Index: 35, Value: 6	0x7ffd3c66822c
array[2][1][1] = 12	Index: 36, Value: 12	0x7ffd3c668230
array[2][1][2] = 18	Index: 37, Value: 18	0x7ffd3c668234
array[2][1][3] = 24	Index: 38, Value: 24	0x7ffd3c668238
array[2][1][4] = 30	Index: 39, Value: 30	0x7ffd3c66823c
array[2][2][0] = 9	Index: 40, Value: 9	0x7ffd3c668240
array[2][2][1] = 18	Index: 41, Value: 18	0x7ffd3c668244
array[2][2][2] = 27	Index: 42, Value: 27	0x7ffd3c668248
array[2][2][3] = 36	Index: 43, Value: 36	0x7ffd3c66824c
array[2][2][4] = 45	Index: 44, Value: 45	0x7ffd3c668250

Get single3d[1][1][2]: 12
```

## Resources
* [SO Question][1] (quite a few wrong/confusing answers here)

[1]: https://stackoverflow.com/questions/7367770/how-to-flatten-or-index-3d-array-in-1d-array
