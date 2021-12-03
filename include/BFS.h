#pragma once

#include <iterator>
#include <queue>
#include "AirportTraversal.h"
#include "Graph.h"
/**
 * A Breadth-first Airport Traversal.
 * Derived from the baseclass Airport Traversal
 */

class BFS : public AirportTraversal {
    private:
      //queue to hold the airport for BFS
      std::queue<Graph::Airport> queue;

      //The graph used
      Graph graph_;

      //The airport we start at
      Graph::Airport start_;


    public:
      /**
        * Initializes a breadth-first Airport traversal on a graph
        * starting at 'start' for given Graph 'graph'
        * @param graph The graph that the BFS is going to traverse
        * @param start The start point for this BFS
        */
      BFS(const Graph & graph, const Graph::Airport & start);

      //The beginning of the traversal iterator
      AirportTraversal::Iterator begin();
      
      //The end of the traversal iterator
      AirportTraversal::Iterator end();

      /**
        * Adds an Aiport for the traversal to visit at some point in the future using the queue
        * @param airport the airport to be added into the queue
        */
      void add(const Graph::Airport & airport);

      /**
        * Removes and returns the current Airport in the traversal
        * @return Graph::Airport the current Airport in the traversal
        */
      Graph::Airport pop();

      /**
        * Returns the current point in the traversal
        * @return Graph::Airport the current Airport in the traversal
        */
      Graph::Airport peek() const;

      /**
        * Method to determine if the traversal is empty
        * @return true if the traversal is empty, false otherwise
        */
      bool empty() const;
 };