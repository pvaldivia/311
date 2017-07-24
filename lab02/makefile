CXX = g++
CXXFLAGS = -c -g -std=c++11 -Wall -W -Werror -pedantic
LDFLAGS =

PROG = cmap

$(PROG) : CensusData.o
	$(CXX) $(LDFLAGS) CensusData.o -o $(PROG)

CensusData.o : CensusData.cpp CensusData.h
	$(CXX) $(CXXFLAGS) CensusData.cpp

clean :
	rm -f core $(PROG) *.o
