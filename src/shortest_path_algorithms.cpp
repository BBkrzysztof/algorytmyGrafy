#include "../include/graphs/shortest_path_algorithms.hpp"

void buildResultMap(
        const int lastIndex,
        const int pathLength,
        const std::vector<int>& path,
        ShortestPathResult& result
) {
    result[lastIndex] = {pathLength, path};
}

void dijkstra(Graph& graph, int sourceIndex, ShortestPathResult& result) {
    auto vertexes = graph.vertices();
    int vertexesCount = vertexes->size();

    // find source vertex (i assume it exists in graph)
    Vertex* sourceVertex = *std::find_if(
            (*vertexes).begin(),
            (*vertexes).end(),
            [sourceIndex](Vertex* element) {
                return element->id == sourceIndex;
            }
    );

    // store distance
    std::map<Vertex, int> distance;
    // store shortest path sum
    std::map<Vertex, int> pathSum;
    // store shortest path
    std::map<Vertex, Vertex> predecessor;
    //priority queue for selecting next vertex
    std::priority_queue<Vertex, std::vector<Vertex>, std::greater<>> queue;


    // set distance to inf
    for (Vertex* v: *vertexes) {
        //skip setting distance to start vertex
        distance[*v] = INF;
        //set pathSum
        pathSum[*v] = 0;
    }
    distance[*sourceVertex] = 0;
    queue.push(*sourceVertex);

    while (!queue.empty()) {
        Vertex u = queue.top();
        queue.pop();

        for (const Edge& edge: graph.incidentEdges(u)) {
            Vertex* v = graph.opposite(u, edge);
            int weight = edge.weight;

            if (distance[u] != INF && distance[u] + weight <= distance[*v]) {
                distance[*v] = distance[u] + weight;
                pathSum[*v] = pathSum[u] + weight;
                predecessor[*v] = u;
                queue.push(*v);
            }
        }

    }

    for (int i = (vertexesCount - 1); i > 0; i--) {
        std::vector<int> path;
        Vertex current = *(*vertexes)[i];
        while (current != *sourceVertex) {
            path.push_back(current.id);
            current = predecessor[current];
        }
        path.push_back(sourceVertex->id);
        std::reverse(path.begin(), path.end());

        std::cout << "z " << sourceVertex->id << " do " << (*vertexes)[i]->id << "   "
                  << pathSum[*(*vertexes)[i]] << " Path: [";
        for (int z: path) {
            std::cout << " " << z << ", ";
        }
        std::cout << " ] " << std::endl;

        buildResultMap((*vertexes)[i]->id, pathSum[*(*vertexes)[i]], path, result);
    }

//    while (*current != -1) {
//        path.push_back(current->id);
//        current = &predecessor[*current];
//    }
//    std::reverse(path.begin(), path.end());
//
//    std::cout << "z " << sourceVertex->id << " do " << v->id << "   "
//              << pathSum[*v] << " Path: [";
//    for (int i: path) {
//        std::cout << " " << i << ", ";
//    }
//    std::cout << " ] " << std::endl;
//
//    buildResultMap(v->id, pathSum[*v], path, result);


}

//bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result) {
//    auto vertexes = graph.vertices();
//    int vertexesCount = vertexes.size();
//
//    std::vector<int> distance(vertexesCount, std::numeric_limits<int>::max());
//    std::vector<int> parent(vertexesCount, -1);
//    distance[sourceIndex] = 0;
//
//    // Relax edges repeatedly
//    for (int i = 1; i <= vertexesCount - 1; ++i) {
//        for (int u = 0; u < vertexesCount; ++u) {
//            for (int v = 0; v < vertexesCount; ++v) {
//                if (graph[u][v] != 0 && distance[u] != std::numeric_limits<int>::max() &&
//                    distance[u] + graph[u][v] < distance[v]) {
//                    distance[v] = distance[u] + graph[u][v];
//                    parent[v] = u;
//                }
//            }
//        }
//    }
//
//    // Check for negative-weight cycles
//    for (int u = 0; u < vertexesCount; ++u) {
//        for (int v = 0; v < vertexesCount; ++v) {
//            if (graph[u][v] != 0 && distance[u] != std::numeric_limits<int>::max() &&
//                distance[u] + graph[u][v] < distance[v]) {
//                return false;
//            }
//        }
//    }
//
//    for (int i = 0; i < vertexesCount; ++i) {
//        std::vector<int> path;
//        int current = i;
//        while (current != -1) {
//            path.push_back(current);
//            current = parent[current];
//        }
//
//        std::reverse(path.begin(), path.end());
//        buildResultMap(i, distance[i], path, result);
//    }
//}

