#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>

//#include "adjacency_list_graph.cpp"
#include "adjacency_matrix_graph.cpp"
//#include "shortest_path_algorithms.cpp"

#include "../include/graphs/vertex.hpp"

int main() {


    std::ifstream inputStream2{"graphV4d0.5.txt"};
    std::unique_ptr<Graph> m2 = AdjacencyMatrixGraph::createGraph(inputStream2);

    m2->dump();
    m2->removeVertex(Vertex(0, 2));

    m2->dump();

}