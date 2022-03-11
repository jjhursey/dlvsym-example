
CC = gcc
CC_FLAGS = -g -O0 -Wall -Werror

LIB = libexlib.so
BIN = test1

all: $(LIB) $(BIN)

test1: test1.c libexlib.so
	$(CC) test1.c $(CFLAGS) -lexlib -L. -o test1

libexlib.so: exlib.c
	$(CC) -shared -fPIC -Wl,--version-script,exlib.vers exlib.c -o libexlib.so

clean:
	$(RM) $(LIB) $(BIN) .*.o
