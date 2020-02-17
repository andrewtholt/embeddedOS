CC=g++
CFLAGS=-g

BINS=testQ

testQ:	testQ.c simpleQ.o
	$(CC) $(CFLAGS) testQ.c simpleQ.o -o testQ

simpleQ.o:	simpleQ.h simpleQ.c
	$(CC) -c $(CFLAGS) simpleQ.c -o simpleQ.o

clean:
	rm -f *.o $(BINS)

