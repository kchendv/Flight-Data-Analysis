**Dataset**

For the final project, we use the OpenFlight flight routes data (last updated June 2014) which contains 67663 unique
flight routes between 3425 airports globally. The data is stored in the form of a .txt file where each line represents
a unique route. The route is a string with comma-separated values representing the airline, airline ID, source airport,
source airport ID, destination airport, destination airport ID, codeshare (“Y” if the flight is a codeshare, empty otherwise),
number of intermediate stops and the most common plane type. Some values are omitted, in which case two commas are 
directly adjacent to each other. For this project, we only use the source and destination airport names of each route.
Alternatively, we can also use assigned id’s to the airports instead of airport names. The full dataset is stored in “src/data.txt”.
We will process the algorithms by taking in each line and then parsing through the names. 

**Algorithms**

We planned to create a graph using the airports as nodes and flight connections as edges. This graph will be 
stored in a Graph class, storing nodes of struct Airport. The Airport struct nodes have member variables that 
contain the names of the airport and the uniquely generated airport ids. We chose to implement BFS, Dijsktras,
and Pagerank. For BFS, we would take in a starting node and traverse through every node in a breadth-first order.
For BFS, it will be the same as in the mp_traversal implementation, where the user manually increments the iterator operator,
or by using a for loop to traverse. The BFS constructor itself will take in a Graph and a starting airport node.
For Dijkstra’s algorithm, we expect to take in a starting node as well as an ending node, and it would ideally
return a set of nodes as well as edges that represent the lowest-weighted (easiest to travel between, given throughput) path.
For Pagerank, we will return the ordering of the rank of each node. For Dijkstra’s, the input would be a start airport,
and then destination airport, and the output would be a vector of airports that were traversed. With Dijkstra’s, we had two implementations,
one where the input and output would be airport id’s, and the other where the input and output would be airport names. Note, however,
that these could not be interchanged, there could not be an input id and an output of names, and vice versa. With Pagerank, our input is
the adjacency matrix that is in the Graph class, and then our output would be a vector of airport id’s, sorted from most important to least. 

**Final Deliverables**

We want to determine which airports are the most significant in the world. In addition, we hope to identify the effectiveness
of Dijkstra's algorithm as a measure for ranking importance by comparing the results with the Pagerank algorithm. The effectiveness
of Dijkstra’s algorithm for ranking can be determined by the frequency of inclusion of an airport in the lowest-weighted path 
between any two airports. We hope to produce a qualitative comparison of the difference between the importance of pages as determined
by this analysis using the Dijkstra algorithm and the PageRank algorithm. 

**Timeline**

In week 1 (4/11 to 4/17) we will have been able to write in the data and represent all the data as a directed graph. In addition, we will set up the weights for the graph.
In week 2 (4/18 to 4/24) we will have set up the iterator for the graph as well as test cases to make sure we have set up our graph correctly.
In week 3 (4/25 to 5/1) We will have set up BFS and Dijkstra’s algorithm as well as thorough test cases to make sure that our algorithm is performing as expected.
In week 4 (5/2 to 5/8) we will have implemented pagerank as well as the test cases for it. 
In week 5 (5/9 to 5/12) we will be making final changes and final touches to our project.
