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

std::vector<int> vectors = {10, 50, 100, 500, 1000};
std::vector<int> densitys = {25, 50, 75, 100};

std::map<
        std::string,
        std::function<std::unique_ptr<Graph>(std::istream& is)>
> graphs;

int main() {
//    graphs["AdjacencyMatrixGraph"] = AdjacencyMatrixGraph::createGraph;
    graphs["AdjacencyListGraph"] = AdjacencyListGraph::createGraph;

    for (const int& vector: vectors) {
        for (const int& density: densitys) {
            std::istringstream data(Experiment::generateGraph(vector, density).str());
            for (const auto& graph: graphs) {
                std::unique_ptr<Graph> graphRepresentation = graph.second(data);

                std::stringstream s1;
                s1 << graph.first << "-v-" << vector << "-d-" << density << "-s-" << 1;

                Experiment::perform(
                        s1.str(),
                        [&graphRepresentation]() {
                            ShortestPathResult result;
                            dijkstra(*graphRepresentation, 1, result);
                        });

                graphRepresentation.reset();
            }
        }
    }
}