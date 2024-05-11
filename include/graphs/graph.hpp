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

    /**
     * return array of two ends Vertex from edge
     * @param Edge e
     * @return std::vector<Vertex*>
     */
    virtual std::vector<Vertex*> endVertices(Edge e) = 0;

    /**
     * return opposite end vertex of edge
     * @param Vertex v
     * @param Edge e
     * @return *Vertex
     */
    virtual Vertex* opposite(Vertex v, Edge e) = 0;

    /**
     * return true if vertexes are adjacent
     * @param Vertex v
     * @param Vertex w
     * @return bool
     */
    virtual bool areAdjacent(Vertex v, Vertex w) = 0;

    /**
     * replace vertex V to vertex X
     * @param Vertex v
     * @param Vertex x
     */
    virtual void replaceElement(Vertex v, Vertex x) = 0;

    /**
     * replace edge weight
     * @param Edge target edge
     * @param int x new weight
     */
    virtual void replaceEdge(const Edge& e, int x) = 0;

    /**
     * insert new Vertex
     * @param Vertex* v
     */
    virtual void insertVertex(Vertex* v) = 0;

    /**
     * insert new edge between Vertexes V and W with weight o
     * @param Vertex v
     * @param Vertex w
     * @param int o
     */
    virtual void insertEdge(Vertex v, Vertex w, int o) = 0;

    /**
     * remove Vertex
     * @param Vertex v
     */
    virtual void removeVertex(Vertex v) = 0;

    /**
    * remove edge
    * @param edge v
    */
    virtual void removeEdge(const Edge& e) = 0;

    /**
    * return vector of incident edges to vertex V
    * @param Vertex v
    */
    virtual std::vector<Edge> incidentEdges(Vertex v) = 0;

    /**
     * return vector of vertexes
     * @return std::vector<Vertex*>*
     */
    virtual std::vector<Vertex*>* vertices() = 0;

    /**
     * return vector of Edge
     * @return std::vector<Edge*>
     */
    virtual std::vector<Edge>* edges() = 0;

    /**
     * draw graph on standard output
     */
    virtual void dump() = 0;
};

#endif /* GRAPH_HPP_ */
