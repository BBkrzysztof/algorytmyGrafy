#ifndef ADJACENCY_LIST_GRAPH_HPP_
#define ADJACENCY_LIST_GRAPH_HPP_

#include <map>
#include <memory>

#include "graph.hpp"

class AdjacencyListGraph : public Graph
{

  public:
    // TODO: implement all required methods
    explicit AdjacencyListGraph(int vertexCount);

    static std::unique_ptr<Graph> createGraph(std::istream& is);

    void insertEdge(int v, int w, int o) final;

    void replaceEdge(int v, int x) final;
    std::vector<std::vector<int>> vertices() final;
    void dump() final;

  private:
    std::vector<std::vector<std::pair<int, int>>>* array;
};

#endif /* ADJACENCY_LIST_GRAPH_HPP_ */
