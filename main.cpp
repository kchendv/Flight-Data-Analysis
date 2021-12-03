#include "include/Graph.h"
#include "include/PageRank.h"
#include "include/Utils.h"
#include "include/BFS.h"

#include <iostream>
#include <map>
#include <vector>
#include <random>

int main() {
	// Part 1: Sample Adjacency Matrix
	std::cout << "-- Part 1: Sample Adjacency Matrix --" << std::endl;
	Graph graph_sample("tests/routes1.txt");
	vector<vector<double>> adj = graph_sample.GetAdjMatrix();
	for(unsigned i = 0; i < adj.size(); i++) {
	   for(unsigned j = 0; j < adj[i].size(); j++) {
		std::cout << adj[i][j] << " ";
	   }
	   std::cout<<std::endl;
	}

	// The following demonstrations uses the full Flights dataset
	Graph graph_full_dataset("src/data.txt");
	vector<Graph::Airport> airports = graph_full_dataset.GetAirports();
	map<string, int> airport_id = graph_full_dataset.GetIdMap();

	// Part 2: BFS Full run
	std::cout << std::endl << "-- Part 2 : BFS Full Run --"<< std::endl;
	Graph::Airport lax("AER", 0);
	BFS bfs(graph_full_dataset, lax);
	for (auto it = bfs.begin(); it != bfs.end(); ++it) {
		std::cout<< (*it).name_ << " ";
	}
	std::cout<< std::endl;

	// Part 3: Dijkstra Demonstration
	std::cout << std::endl << "-- Part 3 : Dijkstra Demonstration --" << std::endl;
	std::cout << "Shortest path from AER to LAX: ";
	vector<string> path_names = graph_full_dataset.Dijkstra("AER", "LAX");
	for (size_t i = 0; i < path_names.size(); i++) {
		std::cout << path_names[i] << " ";
	}
	std::cout << std::endl;

	// Part 4: Page Rank ranking
	std::cout << std::endl << "-- Part 4 : Page Rank --" << std::endl;
	PageRank page_rank;
	page_rank.LoadAdjacencyMatrix(graph_full_dataset.GetAdjMatrix());
	vector<size_t> page_ranking = page_rank.GenerateRanking();
	std::cout<< "Top 10 most important airports (Page Rank):" <<std::endl;
	for (size_t i = 0; i < 10; i++) {
		std::cout<< airports[page_ranking[i]].name_ << std::endl;
	}

	vector<double> dCount(airports.size(), 0);

	// Part 5: Dijkstra ranking
	std::cout << std::endl << "-- Part 5 : Dijkstra Ranking --" << std::endl;
	std::random_device device;
    std::mt19937 rng(device());
    std::uniform_int_distribution<int> distribution(0, airports.size() - 1);
	size_t iterations = 100; // Increase this to get a more accurate result
	for(size_t i = 0; i < iterations; i++){
		int start = distribution(rng);
		int end = distribution(rng);
    	vector<int> results = graph_full_dataset.Dijkstra(start, end);
      	for (int airport_id : results) {
        	dCount[airport_id] += 1;
      	}
	}

	std::cout<< "Top 10 most important airports (Dijkstra):" <<std::endl;
	vector<size_t> dijkstra_rank = Utils::GenerateRanking(dCount);
	for (size_t i = 0; i < 10; i++) {
		std::cout<< airports[dijkstra_rank[i]].name_ << std::endl;
	}

	// Part 6: Spearman Correlation
	std::cout << std::endl << "-- Part 6 : Spearman Correlation --" << std::endl;
	std::cout<< "Spearman Correlation: " << Utils::SpearmanCorrelation(page_ranking, dijkstra_rank) << std::endl;
}
