CXX = g++
CXXFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS =

PROG = mst

$(PROG) : graph.o minpriority.o mstapp.o
	$(CXX) $(LDFLAGS) graph.o minpriority.o mstapp.o -o $(PROG)

mstapp.o : mstapp.h mstapp.cpp
	$(CXX) $(CXXFLAGS) mstapp.cpp

minpriorityQ.o : minpriority.cpp minpriority.h
	$(CXX) $(CXXFLAGS) minpriority.cpp

graph.o : graph.cpp graph.h
	$(CXX) $(CXXFLAGS) graph.cpp

clean :
	rm -f core $(PROG) *.o
