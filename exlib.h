#ifndef MYLIB_H
#define MYLIB_H

int display(int value);
typedef int (*display_fn)(int value);

int lookup(int value);
typedef int (*lookup_fn)(int value);

/* MYLIB_H */
#endif
