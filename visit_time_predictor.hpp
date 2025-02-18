#pragma once
#include <vector>
#include <random>
#include <cmath>

class VisitTimePredictor {
private:
    struct Layer {
        std::vector<std::vector<double>> weights;
        std::vector<double> biases;
        std::vector<double> outputs;
    };

    std::vector<Layer> layers;
    const double LEARNING_RATE = 0.01;

    struct VisitData {
        double month;
        double day_of_week;
        double hour;
        double is_holiday;
        double weather_score;
        double crowd_level;
    };

    double sigmoid(double x);
    std::vector<double> forward(const std::vector<double>& input);
    void backpropagate(const std::vector<double>& input, const std::vector<double>& target);

public:
    VisitTimePredictor();
    void train(const std::vector<VisitData>& data, const std::vector<double>& optimal_times);
    double predictBestTime(const VisitData& data);
    double getPredictionConfidence(const VisitData& data);
}; 