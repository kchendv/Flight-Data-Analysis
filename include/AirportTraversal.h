#pragma once

#include "Graph.h"

#include <iterator>
#include <vector>

using std::vector;

class AirportTraversal
{
public:
    class Iterator : std::iterator<std::forward_iterator_tag, Graph::Airport>
    {
    public:
    
        /**
         * Default iterator constructor.
         */
        Iterator();

        /**
         * Airport Iterator Constructor
         * Creates a visited vector of size of traversal's adj matrix
         * (since it should have the number of vertices as size)
         */
        Iterator(AirportTraversal *traversal, Graph graph, Graph::Airport start);

        /**
         * Iterator Deconstructor
         */
        ~Iterator();
        
        /**
         * Iterator increment operator.
         *
         * Advances the traversal of the image.
         */
        Iterator &operator++();

        /**
         * Iterator accessor operator.
         *
         * Accesses the current Point in the ImageTraversal.
         */
        Graph::Airport operator*();

        /**
         * Iterator inequality operator.
         *
         * Determines if two iterators are not equal.
         */
        bool operator!=(const Iterator &other);

        /**
         * Iterator equality operator.
         * Determines if two iterators are equal.
         */
        bool operator==(const Iterator &other);

        /**
         * Sets is_end_ to true
         */
        void setEnd();

    private:
        AirportTraversal *traversal_;
        Graph graph_;
        Graph::Airport current_;
        Graph::Airport start_;
        vector<bool> visited_;
        bool is_end_;
    };

    virtual ~AirportTraversal();

    /**
     * The begining of an iterator
     * Virtual function. Derived class need to implement this
     */
    virtual Iterator begin() = 0;

    /**
     * The end of an iterator
     * Virtual function. Derived class need to implement this
     */
    virtual Iterator end() = 0;

    /**
     * Add new point to the traversal
     * Virtual function. Derived class need to implement this
     */
    virtual void add(const Graph::Airport &t) = 0;

    /**
     * Remove and return the next point of the traversal
     * Virtual function. Derived class need to implement this
     */
    virtual Graph::Airport pop() = 0;

    /**
     * Return but not remove the next point of the traversal
     * Virtual function. Derived class need to implement this
     */
    virtual Graph::Airport peek() const = 0;

    /**
     * To see if the traversal has no points left
     * Virtual function. Derived class need to implement this
     */
    virtual bool empty() const = 0;
};