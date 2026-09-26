#pragma once

#include "Food.h"

#include <unordered_map>
#include <string>

class FoodDataManager {
public:
    void loadCsv(const std::string& filePath);

    const Food& getFood(const std::string& foodId);

    const std::unordered_map<std::string, Food>& getFoods() const;
    
private:
    std::unordered_map<std::string, Food> foods;
};