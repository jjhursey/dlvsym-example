# Example of using dlvsym for function versioning

Resources that were helpful in creating this example.
 * [Preloading with multiple symbol versions](https://blog.fesnel.com/blog/2009/08/25/preloading-with-multiple-symbol-versions/)
 * [How the GNU C Library handles backward compatibility](https://developers.redhat.com/blog/2019/08/01/how-the-gnu-c-library-handles-backward-compatibility)
 * GCC Wiki [SymbolVersioning](https://gcc.gnu.org/wiki/SymbolVersioning)
 * LD [3.9 VERSION Command](https://sourceware.org/binutils/docs/ld/VERSION.html)
 * [Documenting the (dynamic) linking rules for symbol versioning"](https://lore.kernel.org/all/c6736794-60bb-517e-0bcf-2e80331f0f72@gmail.com/T/)

The `--version-script` is a linker option that defines the version file.

## To build

 * `exlib.c` : Library implementation
 * `exlib.h` : Library header (with function pointers for the `dlsym`/`dlvsym` tests)
 * `exlib.vers` : Linker version file

```
make clean
make
```

## Inspect symbols in the shared library

```
nm libexlib.so | grep lookup
```

## Testing

There are three tests:
 * `test-link.c` : Test direct linking resolution.
   - Expectation: Default function
 * `test-dlsym.c` : Test `dlsym` without version marker
   - Expectation: First match
   - This will match one of the the unversioned functions (see `nm` output above for ordering)
     - Seems to pick the last one defined in the `exlib.c`. The `.symver` must override previous settings.
 * `test-dlvsym.c` : Test `dlvsym`
   - Expectation: Access and execute all versioned functions

## Example output

```
shell$ make clean
rm -f libexlib.so libexlib-wo.so test-link test-link-wo test-dlsym test-dlvsym .*.o
shell$ make
gcc -shared -fPIC -Wl,--version-script,exlib.vers exlib.c -o libexlib.so
gcc -shared -fPIC -Wl,--version-script,exlib.vers exlib.c -DNO_UNVERSIONED=1 -o libexlib-wo.so
gcc test-link.c -g -O0 -Wall -Werror -lexlib -L. -o test-link
gcc test-link.c -g -O0 -Wall -Werror -lexlib-wo -L. -o test-link-wo
gcc test-dlsym.c -g -O0 -Wall -Werror -ldl -o test-dlsym
gcc test-dlvsym.c -g -O0 -Wall -Werror -ldl -o test-dlvsym
```

```
shell$ nm libexlib.so | grep lookup 
0000000000000b28 T lookup@
0000000000000b28 T lookup_v0_0
0000000000000ac8 T lookup_v0_1
0000000000000a64 t lookup_v1
0000000000000a64 T lookup@v1
00000000000009f8 t lookup_v2
00000000000009f8 T lookup@v2
0000000000000994 t lookup_v3
0000000000000994 T lookup@@v3
shell$ nm libexlib-wo.so | grep lookup 
00000000000009e4 t lookup_v1
00000000000009e4 T lookup@v1
0000000000000978 t lookup_v2
0000000000000978 T lookup@v2
0000000000000914 t lookup_v3
0000000000000914 T lookup@@v3
```

```
shell$ ./test-link
--> Version 3
Input  2 -> Output 400
```

```
shell$ ./test-dlsym 
Testing: With unversioned functions
--> Version 0_0
Input  2 -> Output   2

Testing: Without unversioned functions
--> Version 3
Input  2 -> Output 400
```

```
shell$ ./test-dlvsym 
--> Version 1
Input  2 -> Output   4
--> Version 2
Input  2 -> Output  40
--> Version 3
Input  2 -> Output 400
```
