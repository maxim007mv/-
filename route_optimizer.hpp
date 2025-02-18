#pragma once
#include <vector>
#include <string>
#include <map>
#include "route_graph.hpp"
#include "schedule_optimizer.hpp"
#include "visit_time_predictor.hpp"

class RouteOptimizer {
public:
    struct Location {
        std::string name;
        double rating;
        int timeRequired; // в часах
        double cost;
        std::vector<std::string> categories; // музей, ресторан, etc.
    };

    struct Day {
        std::vector<Location> places;
        double totalCost;
        int totalTime;
    };

private:
    double totalBudget;
    int totalDays;
    std::vector<std::string> preferences;
    std::map<std::string, Location> attractions;
    std::vector<Day> optimizedPlan;
    RouteGraph graph;
    ScheduleOptimizer scheduler;
    VisitTimePredictor predictor;
    
    struct OptimizedRoute {
        std::vector<std::string> places;
        std::vector<std::pair<std::string, int>> schedule;
        std::map<std::string, double> best_visit_times;
        double total_distance;
        int total_time;
    };

    void loadAttractions(const std::string& country);
    bool checkBudgetConstraints(const std::vector<Day>& plan);
    double calculateRouteScore(const std::vector<Day>& plan);
    void optimizeForPreferences();

public:
    RouteOptimizer(double budget, int days, const std::vector<std::string>& prefs);
    OptimizedRoute generateOptimalRoute(const std::string& country);
    std::string getDetailedPlan();
    double getEstimatedCosts();
    std::vector<std::string> getRecommendations();
}; 