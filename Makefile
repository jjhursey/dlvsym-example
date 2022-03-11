
CC = gcc
CFLAGS = -g -O0 -Wall -Werror

LIBS = libexlib.so libexlib-wo.so
BIN = test-link test-link-wo test-dlsym test-dlvsym

all: $(LIBS) $(BIN)

test-link: test-link.c $(LIBS)
	$(CC) test-link.c $(CFLAGS) -lexlib -L. -o test-link

test-link-wo: test-link.c $(LIBS)
	$(CC) test-link.c $(CFLAGS) -lexlib-wo -L. -o test-link-wo

test-dlsym: test-dlsym.c $(LIBS)
	$(CC) test-dlsym.c $(CFLAGS) -ldl -o test-dlsym

test-dlvsym: test-dlvsym.c $(LIBS)
	$(CC) test-dlvsym.c $(CFLAGS) -ldl -o test-dlvsym

libexlib.so: exlib.c exlib.vers
	$(CC) -shared -fPIC -Wl,--version-script,exlib.vers exlib.c -o libexlib.so

libexlib-wo.so: exlib.c exlib.vers
	$(CC) -shared -fPIC -Wl,--version-script,exlib.vers exlib.c -DNO_UNVERSIONED=1 -o libexlib-wo.so

clean:
	$(RM) $(LIBS) $(BIN) .*.o
