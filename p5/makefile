CXX = g++
CXXFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS =

PROG = minheap

$(PROG) : minpriority.o main.o
	$(CXX) $(LDFLAGS) minpriority.o main.o -o $(PROG)

main.o : main.cpp minpriority.h
	$(CXX) $(CXXFLAGS) main.cpp

minpriorityQ.o : minpriority.cpp minpriority.h
	$(CXX) $(CXXFLAGS) minpriority.cpp

clean :
	rm -f core $(PROG) *.o
