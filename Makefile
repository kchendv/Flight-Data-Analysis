# Executable Name
EXENAME = cs225proj
TEST = test

# Add all object files needed for compiling:
OBJS = main.o Graph.o PageRank.o Utils.o BFS.o AirportTraversal.o

# Compilation Flags
CXX = clang++
CXXFLAGS = $(CS225) -std=c++14 -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++14 -stdlib=libc++ -lc++abi -lm


# Custom Clang Enforcement
include make/customMake


# Define Makefile Rules
.PHONY: all test clean output_msg

all : $(EXENAME)

output_msg: ; $(CLANG_VERSION_MSG)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

Graph.o: main.cpp src/Graph.cpp
	$(CXX) $(CXXFLAGS) main.cpp src/Graph.cpp 

BFS.o: main.cpp src/BFS.cpp
	$(CXX) $(CXXFLAGS) main.cpp src/BFS.cpp

AirportTraversal.o: main.cpp src/AirportTraversal.cpp
	$(CXX) $(CXXFLAGS) main.cpp src/AirportTraversal.cpp 

PageRank.o: main.cpp src/PageRank.cpp
	$(CXX) $(CXXFLAGS) src/PageRank.cpp 

Utils.o: main.cpp src/Utils.cpp
	$(CXX) $(CXXFLAGS) src/Utils.cpp

test: output_msg catch/catchmain.cpp tests/graph_tests.cpp src/Graph.cpp src/AirportTraversal.cpp src/BFS.cpp src/PageRank.cpp src/Utils.cpp
	$(LD) tests/graph_tests.cpp src/Graph.cpp src/AirportTraversal.cpp src/BFS.cpp src/PageRank.cpp src/Utils.cpp $(LDFLAGS) -o test
	
clean:
	-rm -f *.o $(EXENAME) test
