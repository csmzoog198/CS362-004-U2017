CFLAGS = -Wall -fpic -coverage -lm	

all: testme.c
	gcc -o testme testme.c $(CFLAGS)
	testme

clean:
	rm -f testme
	rm -f testme.o
