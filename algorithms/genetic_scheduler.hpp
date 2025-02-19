#pragma once
#include <vector>
#include <random>
#include <algorithm>
#include "../route_graph.hpp"

class GeneticScheduler {
public:
    struct Schedule {
        std::vector<int> route;
        double fitness;
    };

    GeneticScheduler(int populationSize = 100, double mutationRate = 0.1, int generations = 1000)
        : populationSize(populationSize), mutationRate(mutationRate), generations(generations) {
        rng.seed(std::random_device{}());
    }

    Schedule optimizeSchedule(const RouteGraph& graph, const std::vector<int>& points) {
        std::vector<Schedule> population = initializePopulation(points);
        
        for (int gen = 0; gen < generations; ++gen) {
            evaluatePopulation(population, graph);
            std::vector<Schedule> newPopulation;
            
            while (newPopulation.size() < populationSize) {
                Schedule parent1 = selectParent(population);
                Schedule parent2 = selectParent(population);
                Schedule child = crossover(parent1, parent2);
                if (std::uniform_real_distribution<>(0, 1)(rng) < mutationRate) {
                    mutate(child);
                }
                newPopulation.push_back(child);
            }
            
            population = std::move(newPopulation);
        }
        
        evaluatePopulation(population, graph);
        return *std::max_element(population.begin(), population.end(),
            [](const Schedule& a, const Schedule& b) { return a.fitness < b.fitness; });
    }

private:
    int populationSize;
    double mutationRate;
    int generations;
    std::mt19937 rng;
    
    std::vector<Schedule> initializePopulation(const std::vector<int>& points) {
        std::vector<Schedule> population(populationSize);
        for (auto& schedule : population) {
            schedule.route = points;
            std::shuffle(schedule.route.begin(), schedule.route.end(), rng);
        }
        return population;
    }

    void evaluatePopulation(std::vector<Schedule>& population, const RouteGraph& graph) {
        for (auto& schedule : population) {
            schedule.fitness = calculateFitness(schedule.route, graph);
        }
    }

    Schedule selectParent(const std::vector<Schedule>& population) {
        int idx1 = std::uniform_int_distribution<>(0, populationSize-1)(rng);
        int idx2 = std::uniform_int_distribution<>(0, populationSize-1)(rng);
        return population[idx1].fitness > population[idx2].fitness ? population[idx1] : population[idx2];
    }

    Schedule crossover(const Schedule& p1, const Schedule& p2) {
        Schedule child;
        child.route = p1.route;
        int point = std::uniform_int_distribution<>(0, p1.route.size()-1)(rng);
        std::copy(p2.route.begin() + point, p2.route.end(), child.route.begin() + point);
        return child;
    }

    void mutate(Schedule& schedule) {
        int i = std::uniform_int_distribution<>(0, schedule.route.size()-1)(rng);
        int j = std::uniform_int_distribution<>(0, schedule.route.size()-1)(rng);
        std::swap(schedule.route[i], schedule.route[j]);
    }

    double calculateFitness(const std::vector<int>& route, const RouteGraph& graph) {
        // Простая реализация: обратная сумма расстояний между точками
        double totalDist = 0.0;
        for (size_t i = 1; i < route.size(); ++i) {
            totalDist += graph.getDistance(route[i-1], route[i]);
        }
        return 1.0 / (totalDist + 1.0);
    }
}; 