#pragma once
#include <vector>
#include <string>
#include <map>
#include "route_graph.hpp"
#include "schedule_optimizer.hpp"
#include "visit_time_predictor.hpp"
#include "algorithms/dijkstra.hpp"
#include "algorithms/genetic_scheduler.hpp"
#include "data/data_manager.hpp"
#include <sstream>
#include <iomanip>

class RouteOptimizer {
public:
    struct Point {
        double x;
        double y;
    };

    struct Location {
        std::string name;
        double rating;
        int timeRequired; // в часах
        double cost;
        std::vector<std::string> categories; // музей, ресторан, etc.
        Point coordinates;  // добавляем координаты в Location
    };

    struct Day {
        std::vector<Location> places;
        double totalCost;
        int totalTime;
    };

    struct TravelPlan {
        struct DayPlan {
            int day_number;
            std::vector<std::pair<std::string, std::string>> schedule; // <место, время>
            double daily_cost;
            double total_distance;
            std::vector<std::string> meal_suggestions;
        };

        std::string city;
        std::vector<DayPlan> daily_plans;
        std::vector<std::string> recommendations;
        struct UsefulInfo {
            std::vector<std::string> transport_tips;
            std::vector<std::string> weather_forecast;
            std::map<std::string, std::string> emergency_contacts;
            std::vector<std::string> local_customs;
        } useful_info;
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
    DijkstraAlgorithm dijkstra;
    GeneticScheduler geneticScheduler;
    DataManager dataManager;
    
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

    bool validateInput(const std::vector<Point>& points) {
        if (points.empty()) return false;
        
        for (const auto& point : points) {
            if (!isValidCoordinates(point)) return false;
        }
        return true;
    }
    
    bool isValidCoordinates(const Point& point) {
        return point.x >= 0 && point.y >= 0 && 
               point.x <= maxCoordinate && point.y <= maxCoordinate;
    }
    
    static constexpr double maxCoordinate = 1000000.0;

public:
    RouteOptimizer(double budget, int days, const std::vector<std::string>& prefs);
    TravelPlan generateOptimalRoute(const std::string& city);
    std::string getDetailedPlan();
    double getEstimatedCosts();
    std::vector<std::string> getRecommendations();
    std::string formatTravelPlan(const TravelPlan& plan) {
        std::stringstream output;
        
        // Заголовок с красивой рамкой
        output << "╔══════════════════════════════════════════════════╗\n";
        output << "║           📝 План путешествия в " << std::left << std::setw(16) << plan.city << "║\n";
        output << "╚══════════════════════════════════════════════════╝\n\n";
        
        // План по дням в виде таблицы
        output << "🗓️  Детальный план по дням:\n";
        output << "┌──────────┬─────────────────────────┬──────────┬──────────┐\n";
        output << "│   Время  │         Место          │ Длит-ть  │  Цена    │\n";
        output << "├──────────┴─────────────────────────┴──────────┴──────────┤\n";

        for (const auto& day : plan.daily_plans) {
            output << "│ День " << day.day_number << std::string(54, ' ') << "│\n";
            output << "├──────────┬─────────────────────────┬──────────┬──────────┤\n";
            
            for (const auto& [place, time] : day.schedule) {
                output << "│ " << std::setw(8) << time 
                      << " │ " << std::setw(21) << place 
                      << " │ " << std::setw(8) << "2 часа"  // Здесь можно добавить реальную длительность
                      << " │ " << std::setw(8) << "₽1000"   // Здесь можно добавить реальную цену
                      << " │\n";
            }
            
            // Питание
            output << "├──────────┴─────────────────────────┴──────────┴──────────┤\n";
            output << "│ Питание:                                                  │\n";
            for (const auto& meal : day.meal_suggestions) {
                output << "│ • " << std::left << std::setw(52) << meal << " │\n";
            }
            
            // Итоги дня
            output << "├─────────────────────────────────────────────────────────┤\n";
            output << "│ Общее расстояние: " << std::setw(8) << day.total_distance << " км"
                   << std::string(24, ' ') << "│\n";
            output << "│ Стоимость дня: ₽" << std::setw(8) << day.daily_cost 
                   << std::string(27, ' ') << "│\n";
            output << "└─────────────────────────────────────────────────────────┘\n\n";
        }
        
        // Рекомендации в отдельном блоке
        output << "┌─────────────── 💡 Рекомендации ───────────────┐\n";
        for (const auto& rec : plan.recommendations) {
            output << "│ • " << std::left << std::setw(48) << rec << " │\n";
        }
        output << "└─────────────────────────────────────────────────┘\n\n";
        
        // Полезная информация в структурированных блоках
        output << "┌─────────────── ℹ️  Полезная информация ───────────────┐\n";
        
        // Транспорт
        output << "│ 🚇 Транспорт:                                          │\n";
        for (const auto& tip : plan.useful_info.transport_tips) {
            output << "│   • " << std::left << std::setw(48) << tip << " │\n";
        }
        
        // Погода
        output << "│ 🌤️  Погода:                                            │\n";
        for (const auto& weather : plan.useful_info.weather_forecast) {
            output << "│   • " << std::left << std::setw(48) << weather << " │\n";
        }
        
        // Местные обычаи
        output << "│ 🏺 Местные обычаи:                                     │\n";
        for (const auto& custom : plan.useful_info.local_customs) {
            output << "│   • " << std::left << std::setw(48) << custom << " │\n";
        }
        
        // Экстренные контакты
        output << "│ 🆘 Экстренные контакты:                               │\n";
        for (const auto& [service, phone] : plan.useful_info.emergency_contacts) {
            output << "│   • " << std::left << std::setw(20) << service 
                   << ": " << std::setw(27) << phone << " │\n";
        }
        
        output << "└──────────────────────────────────────────────────────┘\n";
        
        return output.str();
    }
}; 