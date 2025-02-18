#pragma once
#include <vector>
#include <string>
#include <map>

class SeasonAnalyzer {
public:
    struct WeatherData {
        double avgTemp;
        double rainChance;
        std::string bestActivities;
        std::vector<std::string> warnings;
    };

private:
    std::string country;
    std::string startDate;
    std::string endDate;
    std::map<std::string, WeatherData> seasonalData;

public:
    SeasonAnalyzer(const std::string& country, const std::string& start, const std::string& end);
    WeatherData getWeatherForecast();
    std::vector<std::string> getSeasonalActivities();
    std::vector<std::string> getPackingRecommendations();
    bool isGoodTimeToVisit();
}; 