#pragma once
#include "route_optimizer.hpp"
#include "budget_manager.hpp"
#include "season_analyzer.hpp"
#include <string>
#include <vector>
#include <map>
#include <chrono>

struct TravelPlan {
    std::string startDate;
    std::string endDate;
    std::string country;
    std::vector<std::string> format;
    std::vector<std::string> goals;
    double budget;
    std::string additionalWishes;
};

class TravelPlanner {
private:
    TravelPlan plan;
    RouteOptimizer routeOptimizer;
    BudgetManager budgetManager;
    SeasonAnalyzer seasonAnalyzer;
    
    std::string formatPlan(const std::vector<RouteOptimizer::Day>& route,
                          const std::map<std::string, double>& budget,
                          const SeasonAnalyzer::WeatherData& weather);

public:
    TravelPlanner(const TravelPlan& p) : 
        plan(p),
        routeOptimizer(p.budget, 
            std::chrono::duration_cast<std::chrono::hours>(
                std::chrono::system_clock::from_time_t(std::stoi(p.endDate)) - 
                std::chrono::system_clock::from_time_t(std::stoi(p.startDate))
            ).count() / 24,
            p.goals),
        budgetManager(p.budget, 
            std::chrono::duration_cast<std::chrono::hours>(
                std::chrono::system_clock::from_time_t(std::stoi(p.endDate)) - 
                std::chrono::system_clock::from_time_t(std::stoi(p.startDate))
            ).count() / 24),
        seasonAnalyzer(p.country, p.startDate, p.endDate) {}
    
    std::string generatePlan() {
        auto route = routeOptimizer.generateOptimalRoute(plan.country);
        auto budgetBreakdown = budgetManager.optimizeBudget();
        auto weatherInfo = seasonAnalyzer.getWeatherForecast();
        
        return formatPlan(route, budgetBreakdown, weatherInfo);
    }
    
    std::vector<std::string> getAlternativeRoutes();
    std::vector<std::string> getEmergencyContacts();
    std::string getLocalCustomsInfo();
}; 