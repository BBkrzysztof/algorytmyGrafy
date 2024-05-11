#include "../include/graphs/adjacency_list_graph.hpp"

AdjacencyListGraph::AdjacencyListGraph(int vertexCount)
{
    this->array = new std::vector<std::vector<std::pair<int, int>>>(vertexCount);
}

void AdjacencyListGraph::insertEdge(int v, int w, int o)
{
    this->array->at(v).emplace_back(w, o);
}

void AdjacencyListGraph::dump()
{
    int iter = 0;
    for(const auto& element : *this->array)
    {
        std::cout << iter << " ";

        for(auto i : element)
        {
            std::cout << "   { " << i.first << "   " << i.second << " }   ";
        }
        std::cout << std::endl;
        iter++;
    }
}

std::unique_ptr<Graph> AdjacencyListGraph::createGraph(std::istream& is)
{
    int vertexCount = 0;
    int edgesCount = 0;
    is >> vertexCount;
    is >> edgesCount;

    std::unique_ptr<Graph> graph = std::make_unique<AdjacencyListGraph>(vertexCount);

    for(int i = 0; i < edgesCount; i++)
    {
        int vertexA, vertexB, weight;
        is >> vertexA;
        is >> vertexB;
        is >> weight;

        graph->insertEdge(vertexA, vertexB, weight);
    }

    return graph;
}
void AdjacencyListGraph::replaceEdge(int v, int x)
{
    // this->array->at(v).emplace_back(w, o);
}
std::vector<std::vector<int>> AdjacencyListGraph::vertices()
{
    // return *this->array;
}
