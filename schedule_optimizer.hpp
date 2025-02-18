#pragma once
#include <vector>
#include <random>
#include <algorithm>

class ScheduleOptimizer {
private:
    struct Activity {
        std::string name;
        int duration;
        double priority;
        std::vector<std::pair<int, int>> possible_times; // <start_hour, end_hour>
    };

    struct Individual {
        std::vector<std::pair<Activity, int>> schedule; // <activity, start_time>
        double fitness;
    };

    std::vector<Activity> activities;
    const int POPULATION_SIZE = 100;
    const int GENERATIONS = 50;
    const double MUTATION_RATE = 0.1;

    double calculateFitness(const Individual& ind);
    Individual crossover(const Individual& parent1, const Individual& parent2);
    void mutate(Individual& ind);

public:
    void addActivity(const std::string& name, int duration, double priority);
    std::vector<std::pair<std::string, int>> optimizeSchedule();
    bool isScheduleValid(const std::vector<std::pair<std::string, int>>& schedule);
}; 