CXX=g++
CXX_FLAGS=-g
BINS=msgTst

all:	$(BINS)

msgTst:	msgTst.cpp msgClass.o
	$(CXX) $(CXX_FLAGS) msgTst.cpp msgClass.o -o msgTst

msgClass.o:	msgClass.cpp msgClass.h
	$(CXX) $(CXX_FLAGS) -c msgClass.cpp -o msgClass.o


clean:
	rm -f *.o cscope.out $(BINS)

