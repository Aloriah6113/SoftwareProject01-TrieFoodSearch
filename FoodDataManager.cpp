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
    // CSV 파일 열기
    std::ifstream file(filePath);

    // 파일을 열지 못한 경우
    if (!file.is_open()) {
        std::cerr << "Failed to open file: " << filePath << '\n';
        return;
    }

    string line;

    // 첫 번째 줄은 CSV 헤더이므로 건너뜀
    std::getline(file, line);

    // 파일의 나머지 줄을 하나씩 읽음
    while (std::getline(file, line)) {
        std::vector<string> fields;
        string field;
        bool insideQuotes = false;

        // CSV 한 줄을 필드 단위로 분리
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

        // 마지막 필드 추가
        fields.push_back(field);

        // 예상한 필드 개수가 아니면 해당 줄을 건너뜀
        if (fields.size() < 7) {
            continue;
        }

        // CSV 데이터로 Food 객체 생성
        Food food(
            fields[0], // foodId
            fields[1], // foodName
            fields[2], // category
            fields[3], // ingredients
            fields[4], // recipe
            fields[5], // allergyInfo
            fields[6]  // imageUrl
        );

        // foodId를 key로 Food 객체 저장
        foods[fields[0]] = food;
    }
}

/*
 * foodId에 해당하는 Food 객체를 const 참조로 반환한다.
 * 해당 Food 객체가 존재하지 않으면 std::out_of_range 예외가 발생한다.
 */
const Food& FoodDataManager::getFood(const string& foodId) {
    return foods.at(foodId);
}
