#pragma once
#include <vector>
#include <queue>
#include <limits>
#include "../route_graph.hpp"

class DijkstraAlgorithm {
public:
    struct PathResult {
        std::vector<int> path;
        double totalDistance;
    };

    static PathResult findShortestPath(const RouteGraph& graph, int start, int end) {
        std::vector<double> distances(graph.getVertexCount(), std::numeric_limits<double>::infinity());
        std::vector<int> previous(graph.getVertexCount(), -1);
        std::priority_queue<std::pair<double, int>> pq;
        
        distances[start] = 0;
        pq.push({0, start});
        
        while (!pq.empty()) {
            int current = pq.top().second;
            pq.pop();
            
            if (current == end) break;
            
            for (const auto& edge : graph.getEdges(current)) {
                double newDist = distances[current] + edge.weight;
                if (newDist < distances[edge.to]) {
                    distances[edge.to] = newDist;
                    previous[edge.to] = current;
                    pq.push({-newDist, edge.to});
                }
            }
        }
        
        PathResult result;
        result.totalDistance = distances[end];
        
        // Восстановление пути
        int current = end;
        while (current != -1) {
            result.path.push_back(current);
            current = previous[current];
        }
        std::reverse(result.path.begin(), result.path.end());
        
        return result;
    }
}; 