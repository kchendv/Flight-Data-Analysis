# Flight Data Analysis
## Developed By: Kevin Chen, Davy Ji, Michael Ma, Jacob Pan

## Summary

This graph analysis report takes a set of flight / airport data and performs:

* A Breadth First Search (BFS)
* Dijkstra's algorithm analysis on the distance between airports
* Page Rank analysis for the relative significance of airports worldwide

## Instructions

The header files are stored as .h files in the /include/ folder: AirportTraversal.h, BFS.h, Graph.h, PageRank.h, Utils.h

The source files are stores as .cpp files in the /src/ folder: AirportTraversal.cpp, BFS.cpp, Graph.cpp, PageRank.cpp, Utils.cpp

The full dataset is stores as data.txt in the /src/ folder

The tests and sample test files are located in the /tests/ folder. The main test file is graph_tests.cpp

The written report and presentation video can be found in the /written_report/ folder

Dependencies included in the project:
Eigen 3.3.9 (Included in /include/)

To run the assignment, use the included makefil. You first need to run the command "make", then enter "./cs225proj"

The test suite is compiled using the command "make test" and then to run the test suite, then enter "./test"
