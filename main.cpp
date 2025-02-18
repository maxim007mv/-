#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <curl/curl.h>
#include "json.hpp"

using json = nlohmann::json;

class TravelPlanner {
private:
    struct TravelPlan {
        std::string startDate;
        std::string endDate;
        std::string country;
        std::vector<std::string> format;
        std::vector<std::string> goals;
        double budget;
        std::string expensivePurchases;
        std::string additionalWishes;
    };

    const std::string GEMINI_API_KEY = "AIzaSyD8RbTSYv6h8OZ6wQalp2HPJhR0pjzH8NI";
    const std::string GEMINI_API_URL = "https://generativelanguage.googleapis.com/v1beta/models/gemini-pro:generateContent";

    static size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* userp) {
        userp->append((char*)contents, size * nmemb);
        return size * nmemb;
    }

    std::string callGeminiAPI(const std::string& prompt) {
        CURL* curl = curl_easy_init();
        std::string response;

        if (curl) {
            // Подготовка JSON для запроса
            json request = {
                {"contents", {
                    {"parts", {
                        {"text", prompt}
                    }}
                }}
            };

            std::string url = GEMINI_API_URL + "?key=" + GEMINI_API_KEY;
            struct curl_slist* headers = NULL;
            headers = curl_slist_append(headers, "Content-Type: application/json");

            curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
            curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
            curl_easy_setopt(curl, CURLOPT_POSTFIELDS, request.dump().c_str());
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

            CURLcode res = curl_easy_perform(curl);
            
            curl_slist_free_all(headers);
            curl_easy_cleanup(curl);

            if (res != CURLE_OK) {
                return "Error: " + std::string(curl_easy_strerror(res));
            }
        }

        return response;
    }

    std::string generatePrompt() {
        std::string prompt = "Создай детальный план путешествия со следующими параметрами:\n";
        prompt += "Страна: " + plan.country + "\n";
        prompt += "Даты: с " + plan.startDate + " по " + plan.endDate + "\n";
        prompt += "Бюджет: " + std::to_string(plan.budget) + " рублей\n";
        
        prompt += "Формат отдыха: ";
        for (const auto& format : plan.format) {
            prompt += format + ", ";
        }
        prompt += "\n";

        prompt += "Цели путешествия: ";
        for (const auto& goal : plan.goals) {
            prompt += goal + ", ";
        }
        prompt += "\n";

        if (!plan.additionalWishes.empty()) {
            prompt += "Дополнительные пожелания: " + plan.additionalWishes + "\n";
        }

        prompt += "\nПожалуйста, создай подробный план путешествия, включая:\n";
        prompt += "1. Рекомендуемые места для посещения\n";
        prompt += "2. Примерный распорядок по дням\n";
        prompt += "3. Рекомендации по проживанию\n";
        prompt += "4. Транспортные советы\n";
        prompt += "5. Примерное распределение бюджета\n";
        prompt += "6. Местные особенности и советы\n";

        return prompt;
    }

public:
    TravelPlan plan;

    void setTravelDates(const std::string& start, const std::string& end) {
        plan.startDate = start;
        plan.endDate = end;
    }

    void setCountry(const std::string& country) {
        plan.country = country;
    }

    void addFormat(const std::string& format) {
        plan.format.push_back(format);
    }

    void addGoal(const std::string& goal) {
        plan.goals.push_back(goal);
    }

    void setBudget(double budget) {
        plan.budget = budget;
    }

    void setExpensivePurchases(const std::string& purchases) {
        plan.expensivePurchases = purchases;
    }

    void setAdditionalWishes(const std::string& wishes) {
        plan.additionalWishes = wishes;
    }

    std::string generatePlan() {
        std::string prompt = generatePrompt();
        std::string aiResponse = callGeminiAPI(prompt);

        // Парсинг JSON-ответа
        try {
            json response = json::parse(aiResponse);
            if (response.contains("candidates") && !response["candidates"].empty()) {
                return response["candidates"][0]["content"]["parts"][0]["text"];
            }
        } catch (const std::exception& e) {
            return "Ошибка при генерации плана: " + std::string(e.what());
        }

        return "Не удалось сгенерировать план путешествия.";
    }
};

int main() {
    TravelPlanner planner;
    // Пример использования
    planner.setTravelDates("2024-06-01", "2024-06-15");
    planner.setCountry("Италия");
    planner.setBudget(100000);
    
    std::string plan = planner.generatePlan();
    std::cout << plan << std::endl;
    
    return 0;
} 