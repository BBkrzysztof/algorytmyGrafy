#include "../include/graphs/adjacency_matrix_graph.hpp"

AdjacencyMatrixGraph::AdjacencyMatrixGraph() {
    this->adjacencyMatrix = new std::map<Vertex, std::map<Vertex, Edge>>();
    this->vertexes = new std::vector<Vertex*>();
}

void AdjacencyMatrixGraph::insertEdge(Vertex v, Vertex w, int o) {
    this->adjacencyMatrix->at(v).at(w) = Edge(
            &v,
            &w,
            o
    );

    this->vertexCount++;
}

void AdjacencyMatrixGraph::insertVertex(Vertex* v) {

    this->vertexes->push_back(v);

    for (std::pair<Vertex, std::map<Vertex, Edge>> row: *this->adjacencyMatrix) {
        (*this->adjacencyMatrix)[row.first][*v] = Edge(
                &row.first,
                v,
                0
        );
    }


    (*this->adjacencyMatrix)[*v] = std::map<Vertex, Edge>();

    for (Vertex* vertex: *this->vertexes) {
        (*this->adjacencyMatrix)[*v][*vertex] = Edge(
                v,
                vertex,
                0
        );
    }
}

void AdjacencyMatrixGraph::replaceEdge(const Edge& e, int x) {
    this->adjacencyMatrix->at(*e.v).at(*e.w) = Edge(e, x);
}

void AdjacencyMatrixGraph::dump() {
    std::cout << std::endl;
    for (const auto& element: *this->adjacencyMatrix) {
        for (const auto& i: element.second) {
            std::cout << "   " << i.second.weight << "   ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

std::unique_ptr<Graph> AdjacencyMatrixGraph::createGraph(std::istream& is) {

    int vertexCount = 0;
    int edgesCount = 0;
    is >> vertexCount;
    is >> edgesCount;

    std::unique_ptr<Graph> graph = std::make_unique<AdjacencyMatrixGraph>();

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

void AdjacencyMatrixGraph::replaceElement(Vertex v, Vertex x) {

    for (auto& row: *this->adjacencyMatrix) {
        auto copy = row.second.at(v);
        row.second.erase(v);
        row.second[x] = copy;
    }

    auto copy = this->adjacencyMatrix->at(v);
    this->adjacencyMatrix->erase(v);
    (*this->adjacencyMatrix)[x] = copy;

    auto oldVertex = std::find_if(
            (*this->vertexes).begin(),
            (*this->vertexes).end(),
            [v](Vertex* element) {
                return element->id == v.id;
            });

    if (oldVertex != this->vertexes->end()) {
        (*oldVertex)->o = x.o;
    }
}

AdjacencyMatrixGraph::~AdjacencyMatrixGraph() {
    std::destroy(this->adjacencyMatrix->begin(), this->adjacencyMatrix->end());
    std::destroy(this->vertexes->begin(), this->vertexes->end());
}

void AdjacencyMatrixGraph::removeEdge(const Edge& e) {
    this->adjacencyMatrix->at(*e.v).at(*e.w) = Edge(e, 0);
}

std::vector<Vertex*>* AdjacencyMatrixGraph::vertices() {
    return this->vertexes;
}

std::vector<Edge>* AdjacencyMatrixGraph::edges() {
    auto* result = new std::vector<Edge>();

    for (const auto& row: *this->adjacencyMatrix) {
        for (const std::pair<Vertex, Edge> element: row.second) {
            result->push_back(element.second);
        }
    }

    return result;
}

std::vector<Vertex*> AdjacencyMatrixGraph::endVertices(Edge e) {
    std::vector<Vertex*> result;
    result.push_back(e.v);
    result.push_back(e.w);

    return result;
}

Vertex* AdjacencyMatrixGraph::opposite(Vertex v, Edge e) {

    if (*e.v == v) {
        return e.w;
    } else if (*e.w == v) {
        return e.v;
    }

    return nullptr;
}

void AdjacencyMatrixGraph::removeVertex(Vertex v) {
    this->adjacencyMatrix->erase(v);

    for (auto& row: *this->adjacencyMatrix) {
        row.second.erase(v);
    }
}

std::vector<Edge> AdjacencyMatrixGraph::incidentEdges(Vertex v) {
    std::vector<Edge> edges;

    for (auto& element: this->adjacencyMatrix->at(v)) {
        if (element.second.weight != 0) {
            edges.push_back(element.second);
        }
    }

    return edges;
}

bool AdjacencyMatrixGraph::areAdjacent(Vertex v, Vertex w) {
    return this->adjacencyMatrix->at(v).at(w).weight != 0;
}
