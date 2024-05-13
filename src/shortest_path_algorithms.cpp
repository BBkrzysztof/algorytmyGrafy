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
        auto edges = graph.incidentEdges(u);
        for (const Edge& edge: edges) {
            Vertex* v = graph.opposite(u, edge);
            int weight = edge.weight;

            if (distance[u] != INF && distance[u] + weight < distance[*v]) {
                distance[*v] = distance[u] + weight;
                pathSum[*v] = pathSum[u] + weight;
                predecessor[*v] = u;
                queue.push(*v);
            }
        }

    }

    for (Vertex* v: *vertexes) {
        std::vector<int> path;
        Vertex current = *v;

        while (current != sourceVertex->id) {
            path.push_back(current.id);
            current = predecessor[current];
        }
        path.push_back(sourceVertex->id);
        std::reverse(path.begin(), path.end());
        buildResultMap(v->id, pathSum[*v], path, result);
    }
}

bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result) {
    auto vertexes = graph.vertices();
    int vertexesCount = vertexes->size();
    // store distance
    std::map<Vertex, int> distance;
    std::map<Vertex, int> pathSum;

    // store shortest path
    std::map<Vertex, Vertex> predecessor;

    // find source vertex (i assume it exists in graph)
    Vertex* sourceVertex = *std::find_if(
            (*vertexes).begin(),
            (*vertexes).end(),
            [sourceIndex](Vertex* element) {
                return element->id == sourceIndex;
            }
    );

    // set distance to inf
    for (Vertex* v: *vertexes) {
        //skip setting distance to start vertex
        distance[*v] = INF;
        //set pathSum
        pathSum[*v] = 0;
    }

    distance[*sourceVertex] = 0;

    for (const Vertex* i: *vertexes) {
        for (const Vertex* u: *vertexes) {
            auto edges = graph.incidentEdges(*u);
            for (const Edge& edge: edges) {
                Vertex* v = graph.opposite(*u, edge);
                int weight = edge.weight;
                if (distance[*u] != INF && distance[*u] + weight < distance[*v]) {
                    distance[*v] = distance[*u] + weight;
                    pathSum[*v] = pathSum[*u] + weight;
                    predecessor[*v] = *u;
                }
            }
        }
    }


    for (const Vertex* u: *vertexes) {
        auto edges = graph.incidentEdges(*u);
        for (const Edge& edge: edges) {
            Vertex* v = graph.opposite(*u, edge);
            int weight = edge.weight;
            if (distance[*u] != INF && distance[*u] + weight < distance[*v]) {
                return false;
            }
        }
    }

    for (Vertex* v: *vertexes) {
        std::vector<int> path;
        Vertex current = *v;

        while (current != sourceVertex->id) {
            path.push_back(current.id);
            current = predecessor[current];
        }
        path.push_back(sourceVertex->id);
        std::reverse(path.begin(), path.end());
        buildResultMap(v->id, pathSum[*v], path, result);
    }

    return true;
}

