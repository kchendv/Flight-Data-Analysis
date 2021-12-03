#define CATCH_CONFIG_MAIN
#include "../catch/catch.hpp"
#include "../include/Graph.h"
#include "../include/BFS.h"
#include "../include/PageRank.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;

TEST_CASE("Constructor Test 1")
{
  Graph graph("tests/routes1.txt");
  vector<vector<double>> mat 
  {{ 0, 1, 0, 0, 0, 0 },
  { 0, 0, 1, 0, 0, 0 },
  { 1, 1, 0, 0, 0, 0 },
  { 0, 1, 1, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 1 },
  { 0, 0, 0, 0, 0, 0 }};
  REQUIRE(mat == graph.GetAdjMatrix());
  map<string, int> id = graph.GetIdMap();
  REQUIRE(id["AER"] == 0);
  REQUIRE(id["KZN"] == 1);
  REQUIRE(id["ASF"] == 2);
  REQUIRE(id["CEK"] == 3);
  REQUIRE(id["DME"] == 4);
  REQUIRE(id["NBC"] == 5);
}

TEST_CASE("Constructor Test 2")
{
  Graph graph("tests/routes2.txt");
  vector<vector<double>> mat
   {{0,1,0,0,0,0},
   {1,0,0,0,0,0},
   {0,0,0,1,0,0},
   {0,0,1,0,0,0},
   {0,0,0,0,0,1},
   {0,0,0,0,0,0}};
  REQUIRE(mat == graph.GetAdjMatrix());
  map<string, int> id = graph.GetIdMap();
  REQUIRE(id["FLA"] == 0);
  REQUIRE(id["BOG"] == 1);
  REQUIRE(id["FLL"] == 2);
  REQUIRE(id["FRA"] == 3);
  REQUIRE(id["GIG"] == 4);
  REQUIRE(id["LIM"] == 5);
}

TEST_CASE("GetDestinations Test 1") {
  Graph graph("tests/routes1.txt");
  vector<Graph::Airport> dest = graph.GetDestinations(Graph::Airport("AER", 0));
  REQUIRE(dest[0].name_ == "KZN");
  vector<Graph::Airport> dest1 = graph.GetDestinations(Graph::Airport("KZN", 1));
  REQUIRE(dest1[0].name_ == "ASF");
  vector<Graph::Airport> dest2 = graph.GetDestinations(Graph::Airport("ASF", 2));
  REQUIRE(dest2[0].name_ == "AER");
  REQUIRE(dest2[1].name_ == "KZN");
  vector<Graph::Airport> dest3 = graph.GetDestinations(Graph::Airport("CEK", 3));
  REQUIRE(dest3[0].name_ == "KZN");
  REQUIRE(dest3[1].name_ == "ASF");
  vector<Graph::Airport> dest4 = graph.GetDestinations(Graph::Airport("DME", 4));
  REQUIRE(dest4[0].name_ == "CEK");
  REQUIRE(dest4[1].name_ == "NBC");
  vector<Graph::Airport> dest5 = graph.GetDestinations(Graph::Airport("NBC", 5));
  REQUIRE(dest5.empty());
}

TEST_CASE("GetDestinations Test 2") {
  Graph graph("tests/routes2.txt");
  vector<Graph::Airport> dest = graph.GetDestinations(Graph::Airport("FLA", 0));
  REQUIRE(dest[0].name_ == "BOG");
  vector<Graph::Airport> dest1 = graph.GetDestinations(Graph::Airport("BOG", 1));
  REQUIRE(dest1[0].name_ == "FLA");
  vector<Graph::Airport> dest2 = graph.GetDestinations(Graph::Airport("FLL", 2));
  REQUIRE(dest2[0].name_ == "FRA");
  vector<Graph::Airport> dest3 = graph.GetDestinations(Graph::Airport("FRA", 3));
  REQUIRE(dest3[0].name_ == "FLL");
  vector<Graph::Airport> dest4 = graph.GetDestinations(Graph::Airport("GIG", 4));
  REQUIRE(dest4[0].name_ == "LIM");
  vector<Graph::Airport> dest5 = graph.GetDestinations(Graph::Airport("LIM", 5));
  REQUIRE(dest5.empty());
}

TEST_CASE("BFS/Iterator Test 1") {
  Graph graph("tests/routes2.txt");
  Graph::Airport airport("FLA", 0);
  BFS bfs(graph, airport);
  AirportTraversal::Iterator it = bfs.begin();
  REQUIRE((*it).name_ == "FLA"); ++it;
  REQUIRE((*it).name_ == "BOG"); ++it;
  REQUIRE(!(it != bfs.end()));

  Graph::Airport airport2("FRA", 0);
  BFS bfs2(graph, airport2);
  AirportTraversal::Iterator it2 = bfs2.begin();
  REQUIRE((*it2).name_ == "FRA"); ++it2;
  REQUIRE((*it2).name_ == "BOG"); ++it2;
  REQUIRE(!(it != bfs.end()));
}

TEST_CASE("BFS/Iterator Test 2") {
   Graph graph("tests/routes1.txt");
   Graph::Airport airport("AER", 0);
   BFS bfs(graph, airport);
   AirportTraversal::Iterator it = bfs.begin();
   REQUIRE((*it).name_ == "AER"); ++it;
   REQUIRE((*it).name_ == "KZN"); ++it;
   REQUIRE((*it).name_ == "ASF"); 

   Graph::Airport airport2("DME", 4);
   BFS bfs2(graph, airport2);
   AirportTraversal::Iterator it2 = bfs2.begin();
   REQUIRE((*it2).name_ == "DME"); ++it2;
   REQUIRE((*it2).name_ == "CEK"); ++it2;
   REQUIRE((*it2).name_ == "NBC"); ++it2;
   REQUIRE((*it2).name_ == "KZN"); ++it2;
   REQUIRE((*it2).name_ == "ASF"); 
}

TEST_CASE("BFS/Iterator Test 3") {
  Graph graph("tests/routes3.txt");
  Graph::Airport airport("AER", 0);
  BFS bfs(graph, airport);
  vector<string> expected {"AER", "KZN", "OSF", "XLE", "DME", "DOV", "NBC", "RBL"};
  vector<string> results;
  for (Graph::Airport airport : bfs) {
    results.push_back(airport.name_);
  }
  for (int i = 0; i < expected.size(); i++) {
    REQUIRE(expected[i] == results[i]); 
  }
}

TEST_CASE("Dijkstra Test 1") {
  Graph graph("tests/routes3.txt");
  vector<int> expected {0, 1, 3};
  vector<int> results = graph.Dijkstra(0, 3);
  for (int i = 0; i < expected.size(); i++) {
    REQUIRE(expected[i] == results[i]); 
  }
  
  vector<string> expected_names {"AER", "KZN", "XLE"};
  vector<string> results_names = graph.Dijkstra("AER", "XLE");
  for (int i = 0; i < expected.size(); i++) {
    REQUIRE(expected_names[i] == results_names[i]); 
  }
}

TEST_CASE("Dijkstra Test Unequal Weights") {
  Graph graph("tests/routes4.txt");
  vector<int> expected {0, 3, 4, 5};
  vector<int> results = graph.Dijkstra(0, 5);
  for (int i = 0; i < expected.size(); i++) {
    REQUIRE(expected[i] == results[i]); 
  }
}

TEST_CASE("Dijkstra Test Invalid Argument") {
  Graph graph("tests/routes3.txt");
  REQUIRE_THROWS_AS(graph.Dijkstra(0, 36), std::invalid_argument);
  REQUIRE_THROWS_AS(graph.Dijkstra("ZZZ", "XLE"), std::invalid_argument);
}

TEST_CASE("Pagerank Test 1") {
  Graph graph("tests/routes5.txt");
  PageRank page(true);
  page.LoadAdjacencyMatrix(graph.GetAdjMatrix());
  vector<size_t> rank = page.GenerateRanking();
  vector<Graph::Airport> airports = graph.GetAirports();
  REQUIRE(airports[rank[0]].name_.compare("CCC")==0);
  REQUIRE(airports[rank[1]].name_.compare("DDD")==0);
  REQUIRE(airports[rank[2]].name_.compare("BBB")==0);
  REQUIRE(airports[rank[3]].name_.compare("AAA")==0);
}


TEST_CASE("Dijkstra Test Rank Comparison") {
  Graph graph("tests/routes5.txt");
  map<int, int> dCount;
  dCount[0]=0; // AAA is 0
  dCount[1]=0; // BBB
  dCount[2]=0; // CCC
  dCount[3]=0; // DDD
  srand((unsigned int)time(NULL));
  vector<Graph::Airport> airports = graph.GetAirports();

  for(size_t i = 0; i < 4; i++){
    for(size_t k = 0; k < 4; k++){
      vector<int> results = graph.Dijkstra(i,k);
      for (int j = 0; j < results.size(); j++) {
        dCount[results[j]]+=1;
      }
    }
    
  }
  //we should make a rank vector
  REQUIRE(dCount[2]>=dCount[3]);//C>D
  REQUIRE(dCount[3]>=dCount[1]);//D>B
  REQUIRE(dCount[1]>=dCount[0]);//B>A
}

TEST_CASE("Pagerank Test Invalid Argument") {
  Graph graph("tests/routes6.txt");
  PageRank page(true);
  vector<vector<double>> matrix1 
  {{}};
  vector<vector<double>> matrix2
  {{0, 0, 0}};
  REQUIRE_THROWS_AS(page.LoadAdjacencyMatrix(graph.GetAdjMatrix()), std::invalid_argument);
  REQUIRE_THROWS_AS(page.LoadAdjacencyMatrix(matrix1), std::invalid_argument);
  REQUIRE_THROWS_AS(page.LoadAdjacencyMatrix(matrix2), std::invalid_argument);
}
