CXX=g++
CXX_FLAGS=-g -std=c++11 -Wfatal-errors -I../Msg -I../Tasks -I../simpleQueue

BINS=tstDatabase

all:	$(BINS)

tstDatabase:	tstDatabase.cpp database.o myDatabase.o
	$(CXX) $(CXX_FLAGS) tstDatabase.cpp database.o myDatabase.o -o tstDatabase

database.o:	database.cpp database.h 
	$(CXX) -c $(CXX_FLAGS) database.cpp -o database.o

myDatabase.o:	myDatabase.cpp myDatabase.h 
	$(CXX) -c $(CXX_FLAGS) myDatabase.cpp -o myDatabase.o

clean:
	rm -f *.o cscope.out $(BINS)
