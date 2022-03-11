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

    printf("Testing: With unversioned functions\n");
    handle = dlopen("./libexlib.so", RTLD_LAZY);
    if( NULL == handle ) {
        fprintf(stderr, "Error: Failed to dlopen(./libexlib.so). %s\n", dlerror());
        exit(1);
    }

    fp = dlsym(handle, "lookup");
    if( NULL == fp ) {
        fprintf(stderr, "Error: Failed to dlsym(). %s\n", dlerror());
        exit(1);
    }

    output = fp(input);
    printf("Input %2d -> Output %3d\n", input, output);

    dlclose(handle);



    printf("\nTesting: Without unversioned functions\n");
    handle = dlopen("./libexlib-wo.so", RTLD_LAZY);
    if( NULL == handle ) {
        fprintf(stderr, "Error: Failed to dlopen(./libexlib.so). %s\n", dlerror());
        exit(1);
    }

    fp = dlsym(handle, "lookup");
    if( NULL == fp ) {
        fprintf(stderr, "Error: Failed to dlsym(). %s\n", dlerror());
        exit(1);
    }

    output = fp(input);
    printf("Input %2d -> Output %3d\n", input, output);


    dlclose(handle);

    return 0;
}
