Team Proposal
1. Leading Question

We hope to determine which airports are the most significant in the world. In addition, we hope to identify the effectiveness of Dijkstra's algorithm as a measure for ranking importance by comparing the results with the Pagerank algorithm. The effectiveness of Dijkstra’s algorithm for ranking can be determined by the frequency of inclusion of an airport in the lowest-weighted path between any two airports. We hope to produce a qualitative comparison of the difference between the importance of pages as determined by this analysis using the Dijkstra algorithm and the PageRank algorithm. 

2. Dataset Acquisition and Processing

We will be using OpenFlights Airport Database which has a dataset for the airports that is a directed graph in a .dat file that we can add a weight for each node. We generate the weight by calculating 1 divided by the number of flights between any two airports as a measure of throughput. It consists of a set of approximately 67000 edges (flights) between 3300 origin and destination nodes (airports). The data set contains additional information, such as the airline code, which we will not use. If any edge contains incomplete data, we will skip the particular edge.

3. Graph Algorithms

We will use BFS, Pagerank as well as Dijkstra’s algorithm. For Dijkstra’s algorithm, we expect to take in a starting node as well as an ending node, and it would ideally return a set of nodes as well as edges that represent the lowest-weighted (easiest to travel between, given throughput) path. For BFS, we would take in a starting node and traverse through every node in a breadth-first order. For Pagerank, we will return the ordering of the rank of each node. For BFS we would aim for O(n) where n is the number of nodes, while Dijkstra’s is O(mlogn) where m represents the number of nodes while n is the number of edges. It is difficult to find a specific time complexity for Pagerank, but we will aim to implement an algorithm as close to original implementation as possible in terms of efficiency.

4. Timeline

In week 1 (4/11 to 4/17) We will have been able to write in the data and represent all the data as a directed graph. In addition, we will set up the weights for the graph.

In week 2 (4/18 to 4/24) We will have set up the iterator for the graph as well as test cases to make sure we have set up our graph correctly.

In week 3 (4/25 to 5/1) We will have set up BFS and Dijkstra’s algorithm as well as thorough test cases to make sure that our algorithm is performing as expected.

In week 4 (5/2 to 5/8) We will have implemented Pagerank as well as the test cases for it.

In week 5 (5/9 to 5/12) We will be making final changes and final touches to our project.


chiuyin2

jacobfp2

kevinc17

davyji2