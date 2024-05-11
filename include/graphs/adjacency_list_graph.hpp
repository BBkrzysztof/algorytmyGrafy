#ifndef ADJACENCY_LIST_GRAPH_HPP_
#define ADJACENCY_LIST_GRAPH_HPP_

#include <map>
#include <memory>

#include "graph.hpp"

class AdjacencyListGraph : public Graph {

public:
    // TODO: implement all required methods
    explicit AdjacencyListGraph();

    ~AdjacencyListGraph() override;

    static std::unique_ptr<Graph> createGraph(std::istream& is);

    void insertEdge(Vertex v, Vertex w, int o) final;

    void insertVertex(Vertex* v) final;

    void removeEdge(const Edge& e) final;

    std::vector<Vertex*>* vertices() final;

    std::vector<Edge>* edges() final;

    std::vector<Vertex*> endVertices(Edge e) final;

    Vertex* opposite(Vertex v, Edge e) final;

    void removeVertex(Vertex v) final;

    std::vector<Edge> incidentEdges(Vertex v) final;

    bool areAdjacent(Vertex v, Vertex w) final;

    void replaceEdge(const Edge& e, int x) final;

    void replaceElement(Vertex v, Vertex x) final;

    void dump() final;

private:
    std::map<Vertex, std::map<Vertex, Edge>>* adjacencyList;
};

#endif /* ADJACENCY_LIST_GRAPH_HPP_ */
