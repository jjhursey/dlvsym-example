#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "exlib.h"

int main(int argc, char **argv) {
    int input = 2;
    int output;

    output = lookup(input);

    printf("Input %2d -> Output %3d\n", input, output);

    return 0;
}
