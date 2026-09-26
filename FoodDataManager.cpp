#include "FoodDataManager.h"
#include "food.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using std::string;
using std::unordered_map;
using std::vector;

void FoodDataManager::loadCsv(const string& filePath) {
    std::ifstream file(filePath);

    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << '\n';
        return;
    }

    string line;

    // 헤더 건너뛰기
    std::getline(file, line);

    while (std::getline(file, line)) {
        vector<string> fields;
        string field;
        bool insideQuotes = false;

        for (char c : line) {
            if (c == '"') {
                insideQuotes = !insideQuotes;
            }
            else if (c == ',' && !insideQuotes) {
                fields.push_back(field);
                field.clear();
            }
            else {
                field += c;
            }
        }

        fields.push_back(field);

        // foodId ~ imageUrl까지 총 9개
        if (fields.size() < 9) {
            continue;
        }

        Food food(
            fields[0],  // foodId
            fields[1],  // foodName
            fields[2],  // category
            fields[3],  // subcategory
            fields[4],  // weight
            fields[5],  // recipe
            fields[6],  // allergyInfo
            fields[7],  // ingredients
            fields[8]   // imageUrl
        );

        foods.emplace(fields[0], food);
    }
}

/*
 * foodId에 해당하는 Food 객체를 const 참조로 반환한다.
 * 해당 Food 객체가 존재하지 않으면 std::out_of_range 예외가 발생한다.
 */
const Food& FoodDataManager::getFood(const string& foodId) {
    return foods.at(foodId);
}

const std::unordered_map<std::string, Food>&
FoodDataManager::getFoods() const
{
    return foods;
}