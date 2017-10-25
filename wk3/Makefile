all: file.o
	clang -o file file.o

file.o: file.c
	clang -c -o file.o file.c

clean:
	rm *.o file

