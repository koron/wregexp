CC = gcc

all: test1

wregexp.o: wregexp.c

test1.o: test1.c wregexp.h

test1: test1.o wregexp.o

test: test1
	./test1

tags:
	ctags -R .

clean:
	rm -f *.o
	rm -f test1 test1.exe
