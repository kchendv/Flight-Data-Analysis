#include "../include/AirportTraversal.h"
#include "../include/BFS.h"


BFS::BFS(const Graph & graph, const Graph::Airport & start) {
    graph_ = graph;
    start_ = start;

    queue.push(start);
}

AirportTraversal::Iterator BFS::begin() {
    return AirportTraversal::Iterator(this, graph_, start_);
}

AirportTraversal::Iterator BFS::end() {
    AirportTraversal::Iterator it;
    it.setEnd();
    return it;
}

void BFS::add(const Graph::Airport & airport) {
    queue.push(airport);
}

Graph::Airport BFS::pop() {
    if (!empty()) {
        Graph::Airport temp = queue.front();
        queue.pop();
        return temp;
    }
    return Graph::Airport();
}

Graph::Airport BFS::peek() const {
    if (!empty()) {
        return queue.front();
    }
    return Graph::Airport();
}

bool BFS::empty() const {
    if (queue.empty()) {
        return true;
    } else {
        return false;
    }
}