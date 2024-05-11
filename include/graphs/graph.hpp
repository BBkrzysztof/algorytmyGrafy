#ifndef GRAPH_HPP_
#define GRAPH_HPP_

#include <iostream>
#include <vector>
#include <algorithm>

#include "edge.hpp"
#include "vertex.hpp"

class Graph {
public:
    virtual ~Graph() = default;

    virtual std::vector<Vertex*> endVertices(Edge e) = 0;

    virtual Vertex* opposite(Vertex v, Edge e) = 0;

    virtual bool areAdjacent(Vertex v, Vertex w) = 0;

//    virtual void replaceElement(Vertex v, Vertex x) = 0;
//
    virtual void replaceEdge(const Edge& e, int x) = 0;

    virtual void insertVertex(Vertex* v) = 0;

    virtual void insertEdge(Vertex v, Vertex w, int o) = 0;

    virtual void removeVertex(Vertex v) = 0;

    virtual void removeEdge(const Edge& e) = 0;

    virtual std::vector<Edge> incidentEdges(Vertex v) = 0;

    virtual std::vector<Vertex*>* vertices() = 0;

    virtual std::vector<Edge>* edges() = 0;

    virtual void dump() = 0;
};

#endif /* GRAPH_HPP_ */
