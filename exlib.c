#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "exlib.h"

/*
 * Symbol Versioning
 * GCC: https://gcc.gnu.org/wiki/SymbolVersioning
 * LD : https://sourceware.org/binutils/docs/ld/VERSION.html
 */

// @@ : Default symbol for newly linked programs
__asm__(".symver lookup_v2, lookup@@v2");
int lookup_v2(int value) {
    return value * 2;
}

// @  : No version. Not the default
__asm__(".symver lookup_v1, lookup@");
int lookup_v1(int value) {
    return value * 2;
}
