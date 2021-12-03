#include "../include/AirportTraversal.h"
#include <iostream>

AirportTraversal::~AirportTraversal(){}

AirportTraversal::Iterator::~Iterator(){}

AirportTraversal::Iterator::Iterator(){
    traversal_ = NULL;
    is_end_ = false;
}

AirportTraversal::Iterator::Iterator(AirportTraversal *traversal, Graph graph, Graph::Airport start)
 : visited_(graph.GetAdjMatrix().size(), 0){
    traversal_ = traversal;
    graph_ = graph;
    start_ = start;
    current_  = start;
    is_end_ = false;
}

AirportTraversal::Iterator & AirportTraversal::Iterator::operator++(){
    if(traversal_->empty()){
        return *this;
    }
    Graph::Airport curr = traversal_->pop();
    //How do we set visited to true? Id doesn't start at 0
    visited_[curr.id_] = true;
    
    //push neighbors
    vector<Graph::Airport> currDest = graph_.GetDestinations(curr);
    for(size_t i = 0; i < currDest.size(); i++){
        if(!visited_[currDest[i].id_]){
            traversal_->add(currDest[i]);
        }
    }
    //while traversal isn't empty and the top of traversal is visited, pop
    while((!traversal_->empty())&&(visited_[traversal_->peek().id_])){
        traversal_->pop();
    }
    //if traversal is empty, we are done
    if(traversal_->empty()){
        is_end_ = true;
        return *this;
    }

    current_ = traversal_->peek();
    return *this;
}

Graph::Airport AirportTraversal::Iterator::operator*() {
  return current_;
}

bool AirportTraversal::Iterator::operator!=(const AirportTraversal::Iterator &other) {
    return !(is_end_ && other.is_end_);
}

bool AirportTraversal::Iterator::operator==(const AirportTraversal::Iterator &other) {
    return (is_end_ && other.is_end_);
}

void AirportTraversal::Iterator::setEnd() {
    is_end_ = true;
};