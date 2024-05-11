#include "../include/graphs/adjacency_list_graph.hpp"

AdjacencyListGraph::AdjacencyListGraph() {
    this->adjacencyList = new std::map<Vertex, std::map<Vertex, Edge>>();

}

void AdjacencyListGraph::insertEdge(Vertex v, Vertex w, int o) {
    this->adjacencyList->at(v).at(w) = Edge(
            &v,
            &w,
            o
    );
}

void AdjacencyListGraph::insertVertex(Vertex* v) {
    this->adjacencyList->at(*v) = std::map<Vertex, Edge>();
}

void AdjacencyListGraph::replaceEdge(const Edge& e, int x) {
    this->adjacencyList->at(*e.v).at(*e.w) = Edge(e, x);
}

void AdjacencyListGraph::dump() {
    std::cout << std::endl;
    for (const auto& element: *this->adjacencyList) {
        for (const auto& i: element.second) {
            std::cout << "   {" << i.first.id << "; " << i.second.weight << "}   ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::unique_ptr<Graph> AdjacencyListGraph::createGraph(std::istream& is) {
    int vertexCount = 0;
    int edgesCount = 0;
    is >> vertexCount;
    is >> edgesCount;

    std::unique_ptr<Graph> graph = std::make_unique<AdjacencyListGraph>();

    for (int i = 0; i < vertexCount; ++i) {
        graph->insertVertex(Vertex::build(0, i == 0));
    }

    for (int i = 0; i < edgesCount; i++) {
        int vertexA, vertexB, weight;
        is >> vertexA;
        is >> vertexB;
        is >> weight;

        graph->insertEdge(
                Vertex(0, vertexA),
                Vertex(0, vertexB),
                weight
        );
    }

    return graph;
}

void AdjacencyListGraph::replaceElement(Vertex v, Vertex x) {


    auto copy = this->adjacencyList->at(v);
    this->adjacencyList->erase(v);
    (*this->adjacencyList)[x] = copy;
}

AdjacencyListGraph::~AdjacencyListGraph() {
    std::destroy(this->adjacencyList->begin(), this->adjacencyList->end());

}

void AdjacencyListGraph::removeEdge(const Edge& e) {
    this->adjacencyList->at(*e.v).erase(*e.w);
}

std::vector<Vertex*>* AdjacencyListGraph::vertices() {
    auto* vertices = new std::vector<Vertex*>();

    for (std::pair<Vertex, std::map<Vertex, Edge>> element: *this->adjacencyList) {
        vertices->push_back(&element.first);
    }

    return vertices;
}

std::vector<Edge>* AdjacencyListGraph::edges() {
    auto* result = new std::vector<Edge>();

    for (const auto& row: *this->adjacencyList) {
        for (const std::pair<Vertex, Edge> element: row.second) {
            result->push_back(element.second);
        }
    }

    return result;
}

std::vector<Vertex*> AdjacencyListGraph::endVertices(Edge e) {
    std::vector<Vertex*> result;
    result.push_back(e.v);
    result.push_back(e.w);

    return result;
}

Vertex* AdjacencyListGraph::opposite(Vertex v, Edge e) {

    if (*e.v == v) {
        return e.w;
    } else if (*e.w == v) {
        return e.v;
    }

    return nullptr;
}

void AdjacencyListGraph::removeVertex(Vertex v) {
    this->adjacencyList->erase(v);
    for (auto& row: *this->adjacencyList) {
        row.second.erase(v);
    }
}

std::vector<Edge> AdjacencyListGraph::incidentEdges(Vertex v) {
    std::vector<Edge> edges;
    for (auto& element: this->adjacencyList->at(v)) {
        edges.push_back(element.second);
    }

    return edges;
}

bool AdjacencyListGraph::areAdjacent(Vertex v, Vertex w) {
    try {
        this->adjacencyList->at(v).at(w).weight;
        return true;
    } catch (const std::out_of_range& e) {
        return false;
    }
}