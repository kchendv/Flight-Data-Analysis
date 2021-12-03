#include "../include/Graph.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using std::stringstream;
using std::string;
using std::vector;
using std::map;

Graph::Graph(string input_file) {
    // Initialization
    no_of_airports_ = 0;

    // TODO : Find correct file path?
    std::ifstream input_stream(input_file);

    // Data not found
    if (input_stream.fail()) {
      throw std::invalid_argument("Data not found");
    }

    string input_line;
    while (std::getline(input_stream, input_line)) {
        string start_name = GetStartAirportName(input_line);
        string end_name = GetEndAirportName(input_line);

        // Attempt to add Airport, if not already exists
        AddAirport(start_name);
        AddAirport(end_name);

        // Find start_id and end_id
        size_t start_id = airport_id_[start_name];
        size_t end_id = airport_id_[end_name];
        
        // Add flight (updates weight of adj_matrix_)
        AddFlight(start_id, end_id);
    }
}

vector<Graph::Airport> Graph::GetDestinations(Airport start) const {
    if (start.id_ > adj_matrix_.size()) {
        // Invalid id, return empty vector
        return vector<Airport> ();
    }

    vector<Airport> result;
    for (size_t end_id = 0; end_id < adj_matrix_[start.id_].size(); end_id++) {
        if (adj_matrix_[start.id_][end_id] > 0) {
            result.push_back(airports_[end_id]);
        }
    }
    return result;
} 

vector<int> Graph::Dijkstra(int start_id, int destination_id) {
    if (start_id >= (int)no_of_airports_
        || destination_id >= (int)no_of_airports_) {
        throw std::invalid_argument("Airport id out of range");
    }

    // Initialization
    unsigned dimension = adj_matrix_.size();
    vector<double> dist(dimension, std::numeric_limits<double>::max());
    vector<bool> mst(dimension, false);
    vector<double> path(dimension, -2); 
    path[start_id] = -1;
    dist[start_id] = 0;

    // Remove min node
    for (unsigned i = 0; i < dimension - 1; i++) {
	int min = std::numeric_limits<int>::max();
	int min_index = 0;
	for (unsigned j = 0; j < dimension; j++) {
	    if (!mst[j] && dist[j] <= min) {
	   	min = dist[j];
		min_index = j;
	    }
	}
 	//add node to MST
	mst[min_index] = true;
	for (unsigned j = 0; j < dimension; j++) {
	   double add_weight = adj_matrix_[min_index][j];
           //if current node is part of mst 
	   if (!mst[j]
            && add_weight != 0
            && (dist[min_index] + add_weight < dist[j])) {
	      path[j] = min_index;
	      dist[j] = dist[min_index] + add_weight;
	   }
	 
   	 }
    }
    
    if(path[destination_id] == -2){
        return vector<int>();
    }

    // Build path from destination to start
    vector<int> toReturn;
    int curr_id = destination_id;
    while (curr_id != -1) {
        toReturn.insert(toReturn.begin(), curr_id);
        curr_id = path[curr_id];
    }

    return toReturn;
}

vector<string> Graph::Dijkstra(string start_name, string destination_name) {
    if (airport_id_.find(start_name) == airport_id_.end()
        || airport_id_.find(destination_name) == airport_id_.end()) {
        throw std::invalid_argument("Airport name not found");
    }
    vector<int> id_path = Dijkstra(airport_id_[start_name], airport_id_[destination_name]);
    vector<string> name_path;
    for (int id : id_path) {
        name_path.push_back(airports_[id].name_);
    }

    return name_path;
}

vector<vector<double>> Graph::GetAdjMatrix() const {
    return adj_matrix_;
}

map<string, int> Graph::GetIdMap() const {
    return airport_id_;
}

vector<Graph::Airport> Graph::GetAirports() const {
    return airports_;
}

string Graph::GetStartAirportName(string input_line) const {
    stringstream s_stream(input_line);
    string result;
    for (size_t i = 0; i < kStartPos; i++) {
        getline(s_stream, result, ',');
    }
    return result;
}

string Graph::GetEndAirportName(string input_line) const {
    stringstream s_stream(input_line);
    string result;
    for (size_t i = 0; i < kEndPos; i++) {
        getline(s_stream, result, ',');
    }
    return result;
}

void Graph::AddAirport(string name) {
    // Check if airport is not already added
    if (airport_id_.find(name) == airport_id_.end()) {
        AddToAirports(name);
        AddToAirportId(name);
        AddToAdjMatrix();
        // Increment number of airports (id)
        no_of_airports_++;
    }
}

void Graph::AddFlight(int start_id, int end_id) {
    if (adj_matrix_[start_id][end_id] == 0.0) {
        adj_matrix_[start_id][end_id] = 1.0;
    } else {
        adj_matrix_[start_id][end_id] = 1 / 
        ((1 / adj_matrix_[start_id][end_id]) + 1);
    }
}

void Graph::AddToAirports(string name) {
    Airport new_airport(name, no_of_airports_);
    airports_.push_back(new_airport);
}

void Graph::AddToAirportId (string name) {
    airport_id_[name] = no_of_airports_;
}

void Graph::AddToAdjMatrix () {
    // Resize row
    adj_matrix_.push_back(vector<double>(no_of_airports_, 0));
    // Resize column
    for (size_t i = 0; i < adj_matrix_.size(); i++) {
        adj_matrix_[i].push_back(0);
    }
}
