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
    int vertexesCount = vertexes.size();

    // store distance
    std::vector<int> distance(vertexesCount, INF);
    // store shortest path sum
    std::vector<int> pathSum(vertexesCount, 0);
    // store shortest path
    std::vector<int> predecessor(vertexesCount, -1);
    //priority queue for selecting next vertex
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> queue;

    distance[sourceIndex] = 0;
    queue.emplace(0, sourceIndex);

    while (!queue.empty()) {
        auto u = queue.top().second;
        queue.pop();

        for (int v = 0; v < vertexesCount; ++v) {
            if (vertexes[u][v] && distance[u] != INF && distance[u] + vertexes[u][v] < distance[v]) {
                distance[v] = distance[u] + vertexes[u][v];
                pathSum[v] = pathSum[u] + vertexes[u][v];
                predecessor[v] = u;
                queue.emplace(distance[v], v);
            }
        }
    }

    // todo implement duping result to map
    for (int i = 0; i < vertexesCount; ++i) {
        std::vector<int> path;
        int current = i;
        while (current != -1) {
            path.push_back(current);
            current = predecessor[current];
        }

        std::reverse(path.begin(), path.end());
        buildResultMap(i, pathSum[i], path, result);
    }
}

bool bellmanFord(Graph& graph, int sourceIndex, ShortestPathResult& result) {
    auto vertexes = graph.vertices();
    int vertexesCount = vertexes.size();

    std::vector<int> distance(vertexesCount, std::numeric_limits<int>::max());
    std::vector<int> parent(vertexesCount, -1);
    distance[sourceIndex] = 0;

    // Relax edges repeatedly
    for (int i = 1; i <= vertexesCount - 1; ++i) {
        for (int u = 0; u < vertexesCount; ++u) {
            for (int v = 0; v < vertexesCount; ++v) {
                if (graph[u][v] != 0 && distance[u] != std::numeric_limits<int>::max() &&
                    distance[u] + graph[u][v] < distance[v]) {
                    distance[v] = distance[u] + graph[u][v];
                    parent[v] = u;
                }
            }
        }
    }

    // Check for negative-weight cycles
    for (int u = 0; u < vertexesCount; ++u) {
        for (int v = 0; v < vertexesCount; ++v) {
            if (graph[u][v] != 0 && distance[u] != std::numeric_limits<int>::max() &&
                distance[u] + graph[u][v] < distance[v]) {
                return false;
            }
        }
    }

    for (int i = 0; i < vertexesCount; ++i) {
        std::vector<int> path;
        int current = i;
        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }

        std::reverse(path.begin(), path.end());
        buildResultMap(i, distance[i], path, result);
    }
}

