#pragma once

#include "vertex.hpp"

class Edge {
public:
    int weight;
    Vertex* v;
    Vertex* w;

    explicit Edge(Vertex* v = nullptr, Vertex* w = nullptr, int weight = 0) {
        this->weight = weight;
        this->v = v;
        this->w = w;
    }

    Edge(const Edge& other) {
        this->weight = other.weight;
        this->w = other.w;
        this->v = other.v;
    }

    Edge(const Edge& other, int weight) {
        this->weight = weight;
        this->w = other.w;
        this->v = other.v;
    }

    static Edge getEdge(int v, int w) {
        return Edge(
                new Vertex(0, v),
                new Vertex(0, w),
                0
        );
    }
};