#pragma once
#include <vector>
#include <map>
#include <queue>
#include <limits>

class RouteGraph {
public:
    struct Edge {
        int to;
        double weight;
    };

    int getVertexCount() const { return vertices.size(); }
    double getDistance(int from, int to) const;
    const std::vector<Edge>& getEdges(int vertex) const { return adjacencyList[vertex]; }

private:
    struct Node {
        std::string place_id;
        double latitude;
        double longitude;
        int visit_time;
        double importance;
        std::vector<std::pair<std::string, double>> edges; // <destination_id, distance>
    };

    std::map<std::string, Node> nodes;
    std::vector<std::pair<double, double>> vertices;  // координаты вершин
    std::vector<std::vector<Edge>> adjacencyList;     // список смежности
    
    double calculateDistance(double lat1, double lon1, double lat2, double lon2);
    std::vector<std::string> dijkstra(const std::string& start, const std::string& end);

public:
    void addPlace(const std::string& id, double lat, double lon, int visit_time, double importance);
    void addEdge(const std::string& from, const std::string& to);
    std::vector<std::string> findOptimalRoute(const std::vector<std::string>& must_visit);
    double getTotalDistance(const std::vector<std::string>& route);
    int getTotalTime(const std::vector<std::string>& route);
}; 