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
    graphs["AdjacencyMatrixGraph"] = AdjacencyMatrixGraph::createGraph;
    graphs["AdjacencyListGraph"] = AdjacencyListGraph::createGraph;

    for (const int& vector: vectors) {
        for (const int& density: densitys) {
            std::istringstream data(Experiment::generateGraph(vector, density).str());
            for (const auto& graph: graphs) {
                std::unique_ptr<Graph> graphRepresentation = graph.second(data);

                for (const int& startIndex: Experiment::generateStartVertexes(vector)) {

                    std::stringstream s1;
                    s1 << graph.first << "-v-" << vector << "-d-" << density << "-s-" << startIndex;

                    Experiment::perform(
                            s1.str(),
                            [&graphRepresentation, startIndex]() {
                                ShortestPathResult result;
                                dijkstra(*graphRepresentation, startIndex, result);
                            });

                    Experiment::perform(
                            s1.str(),
                            [&graphRepresentation, startIndex]() {
                                ShortestPathResult result;
                                bellmanFord(*graphRepresentation, startIndex, result);
                            });
                }
            }
        }
    }

//    std::ifstream inputStream2{"sp_data/graph/graphV200D0.75.txt"};
//    std::istringstream is(Experiment::generateGraph(10, 50).str());

//    std::unique_ptr<Graph> m2 = AdjacencyListGraph::createGraph(inputStream2);
//    ShortestPathResult result;
//    m2->dump();
//    auto d = bellmanFord(*m2, 7, result);
//    m2->dump();

//    ShortestPathResult result;
//    bellmanFord(*m2, 7, result);
//    auto d =  m2->incidentEdges(Vertex(0, 0));
//    m2->dump();
//    std::cout << Experiment::generateGraph(10, 50).str() << std::endl;
}