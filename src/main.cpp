#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>

//#include "adjacency_list_graph.cpp"
#include "adjacency_matrix_graph.cpp"
#include "adjacency_list_graph.cpp"
#include "shortest_path_algorithms.cpp"

#include "../include/graphs/vertex.hpp"

int main() {


    std::ifstream inputStream2{"sp_data/graph/graphV10D0.5Negative.txt"};
    std::unique_ptr<Graph> m2 = AdjacencyMatrixGraph::createGraph(inputStream2);
//    m2->dump();
    ShortestPathResult result;
    bellmanFord(*m2, 7, result);
//    auto d =  m2->incidentEdges(Vertex(0, 0));
//    m2->dump();

}