#pragma once
#include <vector>
#include <string>
#include <map>

class BudgetManager {
private:
    struct Expense {
        std::string category;
        double amount;
        double priority;
    };

    double totalBudget;
    int duration;
    std::vector<Expense> plannedExpenses;
    std::map<std::string, double> averageCosts;

public:
    BudgetManager(double budget, int days);
    void addExpenseCategory(const std::string& category, double amount, double priority);
    std::map<std::string, double> optimizeBudget();
    std::string getBudgetBreakdown();
    bool isWithinBudget();
    std::vector<std::string> getSavingTips();
}; 