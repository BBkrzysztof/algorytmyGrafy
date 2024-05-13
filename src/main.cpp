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
#include "Experiment.cpp"
#include <functional>

#include "../include/graphs/vertex.hpp"

std::vector<int> vectors = {10, 50, 100, 250, 500};
std::vector<int> densitys = {25, 50, 75, 100};


void AdjacencyList(int i = 0) {
    for (const int& vector: vectors) {
        for (const int& density: densitys) {
            std::istringstream data(Experiment::generateGraph(vector, density).str());
            std::unique_ptr<Graph> graph = AdjacencyListGraph::createGraph(data);
            std::stringstream s1, s2;
            s1 << "AdjacencyMatrix-dijkstra-nr-" << i << "-v-" << vector << "-d-" << density << "-s-" << 1;
            s2 << "AdjacencyMatrix-bellmanFord-nr-" << i << "-v-" << vector << "-d-" << density << "-s-" << 1;
            Experiment::perform(
                    s1.str(),
                    [&graph]() {
                        ShortestPathResult result;
                        dijkstra(*graph, 1, result);
                    });

            Experiment::perform(
                    s2.str(),
                    [&graph]() {
                        ShortestPathResult result;
                        bellmanFord(*graph, 1, result);
                    });
            graph.reset();
        }
    }
}

void AdjacencyMatrix(int i = 0) {
    for (const int& vector: vectors) {
        for (const int& density: densitys) {
            std::istringstream data(Experiment::generateGraph(vector, density).str());
            std::unique_ptr<Graph> graph = AdjacencyMatrixGraph::createGraph(data);
            std::stringstream s1, s2;
            s1 << "AdjacencyMatrix-dijkstra-nr-" << i << "-v-" << vector << "-d-" << density << "-s-" << 1;
            s2 << "AdjacencyMatrix-bellmanFord-nr-" << i << "-v-" << vector << "-d-" << density << "-s-" << 1;
            Experiment::perform(
                    s1.str(),
                    [&graph]() {
                        ShortestPathResult result;
                        dijkstra(*graph, 1, result);
                    });

            Experiment::perform(
                    s2.str(),
                    [&graph]() {
                        ShortestPathResult result;
                        bellmanFord(*graph, 1, result);
                    });
            graph.reset();
        }
    }
}

int main() {
    AdjacencyList();
    AdjacencyMatrix();
}

