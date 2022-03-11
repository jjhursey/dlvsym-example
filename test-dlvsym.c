// _GNU_SOURCE needed for dlvsym
#define _GNU_SOURCE

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dlfcn.h>

#include "exlib.h"


int main(int argc, char **argv) {
    int input = 2;
    int output;
    void *handle;
    lookup_fn fp;
    int iter;
    const char *versions[] = {"v1", "v2", "v3", NULL};

    handle = dlopen("./libexlib.so", RTLD_LAZY);
    if( NULL == handle ) {
        fprintf(stderr, "Error: Failed to dlopen(./libexlib.so). %s\n", dlerror());
        exit(1);
    }

    for(iter = 0; NULL != versions[iter]; ++iter) {
        fp = dlvsym(handle, "lookup", versions[iter]);
        if( NULL == fp ) {
            fprintf(stderr, "Error: Failed to dlsym(). %s\n", dlerror());
            exit(1);
        }

        output = fp(input);
        printf("Input %2d -> Output %3d\n", input, output);
    }

    dlclose(handle);

    return 0;
}
