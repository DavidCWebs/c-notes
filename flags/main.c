#include <stdio.h>
enum flag {
    DEBUG           = 1,
    WARNINGS        = 1 << 1,
    VERBOSE         = 1 << 2,
    SIMPLE          = 1 << 3,
    TESTS           = 1 << 4,
    BUILD           = 1 << 5,
    MULTI           = 1 << 6,
    DIST            = 1 << 7
};

const char *flagnames[]= {
    "DEBUG",
    "WARNINGS",
    "VERBOSE",
    "SIMPLE",
    "TESTS",
    "BUILD",
    "MULTI",
    "DIST"
};

int main()
{
    char flags = 0;
    printf("size of char: %lu\n", sizeof(char));
    printf("size of unsigned char: %lu\n", sizeof(unsigned char));
    printf("flags:\t\t%d\n", flags);
    printf("DEBUG:\t\t%d\n", DEBUG);
    printf("WARN:\t\t%d\n", WARNINGS);
    printf("VERBOSE:\t%d\n", VERBOSE);
    printf("SIMPLE:\t\t%d\n", SIMPLE);
    printf("TESTS:\t\t%d\n", TESTS);
    printf("BUILD:\t\t%d\n", BUILD);
    printf("MULTI:\t\t%d\n", MULTI);
    printf("DIST:\t\t%d\n", DIST);

    int x = 7;
    printf("x << 2 = %d\n", x << 1);

    // SET using INCLUSIVE OR
    flags |= VERBOSE;
    flags |= SIMPLE;
    flags |= MULTI;
    flags |= TESTS;

    for (size_t i = 0; i < 8; i++) {
        if (flags & (1 << i)) printf("%s is SET\n", flagnames[i]);
    }

    printf("unsetting...\n");

    // Unset using XOR
    flags ^= TESTS;
    for (size_t i = 0; i < 8; i++) {
        if (flags & (1 << i)) printf("%s is SET\n", flagnames[i]);
    }

    return 0;
}
