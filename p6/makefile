CXX = g++
CXXFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS =

PROG = spath

$(PROG) : graph.o minpriority.o spapp.o
	$(CXX) $(LDFLAGS) graph.o minpriority.o spapp.o -o $(PROG)

spapp.o : spapp.h spapp.cpp
	$(CXX) $(CXXFLAGS) spapp.cpp

minpriorityQ.o : minpriority.cpp minpriority.h
	$(CXX) $(CXXFLAGS) minpriority.cpp

graph.o : graph.cpp graph.h
	$(CXX) $(CXXFLAGS) graph.cpp

clean :
	rm -f core $(PROG) *.o
