
CC=gcc
CFLAGS=-g
BINS=testSched2 # sched 

all:	$(BINS)

sched:	sched.c sched.h
	$(CC) $(CFLAGS) sched.c -o sched

sched2.o:	sched2.c sched2.h
	@echo "Build sched2."
	$(CC) $(CFLAGS) -c sched2.c -o sched2.o

testSched2:	sched2.o testSched2.c
	$(CC) $(CFLAGS)  sched2.o testSched2.c -o testSched2

clean:
	rm -f *.o $(BINS)
