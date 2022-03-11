#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "exlib.h"

// Unversioned function
int display(int value)
{
    printf("--> Display\n");
    return -1 * value;
}

/*
 * Symbol Versioning
 * GCC: https://gcc.gnu.org/wiki/SymbolVersioning
 * LD : https://sourceware.org/binutils/docs/ld/VERSION.html
 */

// @@ : Default symbol for newly linked programs. Only one can be marked as such.
__asm__(".symver lookup_v3, lookup@@v3");
int lookup_v3(int value) {
    printf("--> Version 3\n");
    return value * 200;
}

// @ : Versioned. Not the default
__asm__(".symver lookup_v2, lookup@v2");
int lookup_v2(int value) {
    printf("--> Version 2\n");
    return value * 20;
}

// @ : Versioned. Not the default
__asm__(".symver lookup_v1, lookup@v1");
int lookup_v1(int value) {
    printf("--> Version 1\n");
    return value * 2;
}

#ifndef NO_UNVERSIONED
// @  : No version. Not the default
__asm__(".symver lookup_v0_1, lookup@");
int lookup_v0_1(int value) {
    printf("--> Version 0_1\n");
    return value;
}

// @  : No version. Not the default
__asm__(".symver lookup_v0_0, lookup@");
int lookup_v0_0(int value) {
    printf("--> Version 0_0\n");
    return value;
}
#endif
