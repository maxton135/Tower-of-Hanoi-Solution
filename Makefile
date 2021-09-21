CFLAGS=-Wall -Wextra -Werror -pedantic
CC=clang $(CFLAGS)

all	:	tower

tower	:	tower.o stack.o
	$(CC)	-o tower stack.o tower.o
stack.o	:	stack.c stack.h
	$(CC)	-c stack.c
tower.o	:	tower.c
	$(CC)	-c tower.c
clean	:
	rm -rf tower stack.o tower.o
infer	:
	make clean; infer-capture -- make; infer-analyze
