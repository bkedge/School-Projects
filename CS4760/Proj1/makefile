all: logutil

logutil: main.o loglib.o
	gcc -o logutil main.o loglib.o

main.o: main.c
	gcc -c main.c

loglib.o: loglib.c
	gcc -c loglib.c

clean:
	rm *.o logutil
