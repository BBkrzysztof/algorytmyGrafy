
#define CATCH_CONFIG_MAIN

#include "../include/catch2/catch.hpp"

#include "adjacency_matrix_graph.cpp"
#include <filesystem>

using namespace std::string_literals;

const std::filesystem::path dataDirectoryPath{"sp_data"};

std::unique_ptr<Graph> createAdjacencyMatrixGraph() {
    std::ifstream inputStream{"graphV4d0.5.txt"};
    std::unique_ptr<Graph> m = AdjacencyMatrixGraph::createGraph(inputStream);

    return m;
}

TEST_CASE("createGraph")
{

    std::vector<int> target = {0, 1, 3, 0, 1, 0, 1, 7, 3, 1, 0, 4, 0, 7, 4, 0};
    auto m = createAdjacencyMatrixGraph();

    auto edges = m->edges();
    int iter = 0;
    for (const Edge& edge: *edges) {
        REQUIRE(edge.weight == target[iter]);
        iter++;
    }
}

TEST_CASE("insertEdge and removeEdge")
{

    std::vector<int> target = {123, 1, 3, 0, 1, 0, 1, 7, 3, 1, 0, 4, 0, 7, 4, 0};

    auto m = createAdjacencyMatrixGraph();

    m->insertEdge(Vertex(0, 0), Vertex(0, 0), 123);
    auto edges = m->edges();

    int iter = 0;
    for (const Edge& edge: *edges) {
        REQUIRE(edge.weight == target[iter]);
        iter++;
    }
    //remove edge 0:0
    m->removeEdge(Edge(
            new Vertex(0, 0),
            new Vertex(0, 0),
            0
    ));

    target[0] = 0;
    int iter2 = 0;
    auto updatedEdges = m->edges();
    for (const Edge& edge2: *updatedEdges) {
        REQUIRE(edge2.weight == target[iter2]);
        iter2++;
    }
}

TEST_CASE("insertVertex and removeVertex")
{
    std::vector<int> target = {0, 1, 3, 0, 0, 1, 0, 1, 7, 0, 3, 1, 0, 4, 0, 0, 7, 4, 0, 0, 0, 0, 0, 0, 0};

    auto m = createAdjacencyMatrixGraph();

    m->insertVertex(Vertex::build(0));
    auto edges = m->edges();

    int iter = 0;
    for (const Edge& edge: *edges) {
        REQUIRE(edge.weight == target[iter]);
        iter++;
    }

    std::vector<int> target2 = {0, 1, 0, 1, 0, 7, 0, 7, 4, 0};
    m->removeVertex(Vertex(0, 2));

    auto edges2 = m->edges();

    int iter2 = 0;
    for (const Edge& edge: *edges2) {
        REQUIRE(edge.weight == target2[iter2]);
        iter++;
    }
}