#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <limits>
#include <cstdlib>

#include "Food.h"
#include "FoodDataManager.h"
#include "Trie.h"
#include "SearchService.h"

using std::cin;
using std::cout;
using std::string;
using std::vector;
using std::unordered_set;

void printFood(const Food& food)
{
    cout << "\n===== 음식 정보 =====\n";
    cout << "음식 이름: " << food.getFoodName() << '\n';
    cout << "대분류: " << food.getCategory() << '\n';
    cout << "중분류: " << food.getSubcategory() << '\n';
    cout << "중량: " << food.getWeight() << '\n';
    cout << "재료: " << food.getIngredients() << '\n';
    cout << "레시피: " << food.getRecipe() << '\n';
    cout << "알레르기 정보: " << food.getAllergyInfo() << '\n';
    cout << "이미지 URL: " << food.getImageUrl() << '\n';
    cout << "====================\n";
}

int main()
{
    // 콘솔 UTF-8 설정
    system("chcp 65001 > nul");

    // 음식 데이터 로드
    FoodDataManager foodDataManager;
    foodDataManager.loadCsv("Data/foods.csv");

    cout << "Food 개수: "
        << foodDataManager.getFoods().size()
        << "\n\n";


    // Trie 구축
    Trie trie;

    for (const auto& pair : foodDataManager.getFoods()) {
        const Food& food = pair.second;

        trie.insert(
            food.getFoodName(),
            food.getFoodId()
        );
    }


    // Trie 테스트
    const auto& foods = foodDataManager.getFoods();

    if (!foods.empty()) {
        const Food& testFood = foods.begin()->second;

        cout << "테스트 음식: ["
            << testFood.getFoodName()
            << "]\n";

        cout << "Trie 테스트: ["
            << trie.search(testFood.getFoodName())
            << "]\n\n";
    }


    // SearchService 생성
    SearchService searchService(
        trie,
        foodDataManager
    );


    // 검색
    while (true) {
        cout << "검색할 음식 이름을 입력하세요 (종료: exit): ";

        string input;
        std::getline(cin, input);

        if (input == "exit") {
            break;
        }

        if (input.empty()) {
            continue;
        }


        vector<const Food*> results;
        unordered_set<string> addedFoodIds;


        // 1. 정확한 검색
        string foodId = trie.search(input);

        if (!foodId.empty()) {
            const Food& exactFood =
                foodDataManager.getFood(foodId);

            results.push_back(&exactFood);
            addedFoodIds.insert(foodId);

            cout << "\n정확한 검색 결과\n";
            cout << "1. "
                << exactFood.getFoodName()
                << '\n';
        }
        else {
            cout << "\n정확히 일치하는 검색 결과가 없습니다.\n";
            cout << "다음 음식을 찾으시나요?\n";
        }


        // 2. 자동완성 검색
        vector<const Food*> prefixResults =
            searchService.autoComplete(input);

        for (const Food* food : prefixResults) {
            if (addedFoodIds.find(food->getFoodId())
                == addedFoodIds.end()) {

                results.push_back(food);
                addedFoodIds.insert(food->getFoodId());
            }
        }


        // 3. 오타 허용 검색
        vector<const Food*> approximateResults =
            searchService.approximateSearch(input, 2);

        for (const Food* food : approximateResults) {
            if (addedFoodIds.find(food->getFoodId())
                == addedFoodIds.end()) {

                results.push_back(food);
                addedFoodIds.insert(food->getFoodId());
            }
        }


        // 검색 결과가 없는 경우
        if (results.empty()) {
            cout << "추가 검색 결과가 없습니다.\n\n";
            continue;
        }


        // 검색 결과 출력
        if (foodId.empty()) {
            for (size_t i = 0; i < results.size(); ++i) {
                cout << i + 1
                    << ". "
                    << results[i]->getFoodName()
                    << '\n';
            }
        }
        else {
            for (size_t i = 1; i < results.size(); ++i) {
                cout << i + 1
                    << ". "
                    << results[i]->getFoodName()
                    << '\n';
            }
        }


        // 상세 정보 선택
        cout << "\n상세 정보를 확인할 음식 번호를 입력하세요 "
            "(0: 다시 검색): ";

        int choice;
        cin >> choice;

        cin.ignore(
            std::numeric_limits<std::streamsize>::max(),
            '\n'
        );


        if (choice == 0) {
            cout << '\n';
            continue;
        }


        if (choice < 1 ||
            choice > static_cast<int>(results.size())) {

            cout << "잘못된 번호입니다.\n\n";
            continue;
        }


        // 음식 상세 정보 출력
        printFood(*results[choice - 1]);

        cout << '\n';
    }

    return 0;
}