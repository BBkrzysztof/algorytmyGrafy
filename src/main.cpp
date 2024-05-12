#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <map>
#include <queue>

//#include "adjacency_list_graph.cpp"
#include "adjacency_matrix_graph.cpp"
#include "adjacency_list_graph.cpp"
//#include "shortest_path_algorithms.cpp"

#include "../include/graphs/vertex.hpp"

const int INF = std::numeric_limits<int>::max();


void dijkstra(const std::unique_ptr<Graph>& graph, int source) {
    auto vertexes = graph->vertices();
    int vertexesCount = vertexes->size();

    // find source vertex (i assume it exists in graph)
    Vertex* sourceVertex = *std::find_if(
            (*vertexes).begin(),
            (*vertexes).end(),
            [source](Vertex* element) {
                return element->id == source;
            }
    );

    // store distance
    std::map<Vertex*, int> distance;
    // store shortest path sum
    std::map<Vertex*, int> pathSum;
    // store shortest path
    std::vector<int> predecessor(vertexesCount, -1);

    //priority queue for selecting next vertex
    std::priority_queue<Vertex, std::vector<Vertex>, std::greater<>> queue;


    // set distance to inf
    for (Vertex* v: *vertexes) {
        //skip setting distance to start vertex
        distance[v] = INF;
        //set pathSum
        pathSum[v] = 0;
    }
    distance[sourceVertex] = 0;
    queue.push(*sourceVertex);

    while (!queue.empty()) {
        Vertex u = queue.top();
        queue.pop();

        for (const Edge& edge: graph->incidentEdges(u)) {
            Vertex* v = graph->opposite(u, edge);
            int weight = edge.weight;
            if (distance[&u] != INF && distance[&u] + weight < distance[v]) {
                distance[v] = distance[&u] + weight;
                pathSum[v] = pathSum[&u] + weight;
//                predecessor[]
            }
        }

    }
    for (Vertex* v: *vertexes) {
        std::cout << "z " << sourceVertex->id << " do " << v->id << "   "
                  << pathSum[v] << std::endl;
    }
}

int main() {


    std::ifstream inputStream2{"graphV4d0.5.txt"};
    std::unique_ptr<Graph> m2 = AdjacencyMatrixGraph::createGraph(inputStream2);
    m2->dump();

    dijkstra(m2,0);

//    auto d =  m2->incidentEdges(Vertex(0, 0));
//    m2->dump();

}