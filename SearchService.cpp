#include "SearchService.h"

using std::string;
using std::vector;


SearchService::SearchService(
    Trie& trie,
    FoodDataManager& foodDataManager
)
    : trie(trie),
    foodDataManager(foodDataManager)
{
}


/*
 * 음식 이름을 정확하게 검색한다.
 *
 * Trie에서 음식 이름에 해당하는 foodId를 찾은 후,
 * FoodDataManager에서 해당 foodId의 Food 객체를 조회하여 반환한다.
 */
const Food& SearchService::search(const string& foodName) {
    string foodId = trie.search(foodName);

    return foodDataManager.getFood(foodId);
}


/*
 * 입력한 prefix로 시작하는 음식들을 검색한다.
 *
 * Trie에서 prefix에 해당하는 모든 foodId를 검색한 후,
 * FoodDataManager에서 각 foodId에 해당하는 Food 객체를 조회한다.
 */
vector<const Food*> SearchService::autoComplete(
    const string& prefix) 
{
    vector<const Food*> results;

    // Trie에서 prefix에 해당하는 foodId들을 검색한다.
    vector<string> foodIds = trie.autoComplete(prefix);

    // 각 foodId를 Food 객체로 변환한다.
    for (const string& foodId : foodIds) {
        results.push_back(
            &foodDataManager.getFood(foodId)
        );
    }

    return results;
}


/*
 * 입력한 음식 이름과 편집 거리가 maxDistance 이하인
 * 음식들을 검색한다.
 *
 * Trie에서 유사한 음식 이름을 검색한 후,
 * 각 음식 이름을 다시 정확하게 검색하여 foodId를 얻고
 * FoodDataManager에서 Food 객체를 조회한다.
 */
vector<const Food*> SearchService::approximateSearch(
    const string& target,
    int maxDistance) 
{
    vector<const Food*> results;

    // Trie에서 target과 유사한 음식 이름을 검색한다.
    vector<string> foodNames =
        trie.approximateSearch(target, maxDistance);

    // 검색된 음식 이름을 이용하여 Food 객체를 조회한다.
    for (const string& foodName : foodNames) {
        string foodId = trie.search(foodName);

        results.push_back(
            &foodDataManager.getFood(foodId)
        );
    }

    return results;
}