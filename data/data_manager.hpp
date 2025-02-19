#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "../route_graph.hpp"

class DataManager {
public:
    // Загрузка данных
    static RouteGraph loadFromJson(const std::string& filename);
    static void saveToJson(const RouteGraph& graph, const std::string& filename);
    
    // Кэширование
    void cacheRoute(const std::string& key, const std::vector<int>& route);
    std::vector<int> getCachedRoute(const std::string& key);
    
    // Валидация
    static bool validateRoute(const RouteGraph& graph, const std::vector<int>& route);
    static bool validateTimeConstraints(const std::vector<std::pair<int, double>>& schedule);

private:
    std::unordered_map<std::string, std::vector<int>> routeCache;
}; 