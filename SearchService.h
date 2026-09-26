#pragma once

#include <string>
#include <vector>

#include "Trie.h"
#include "FoodDataManager.h"

class SearchService {
public:
    /*
     * Trie와 FoodDataManager를 참조로 받아
     * 검색 서비스에서 사용할 객체를 초기화한다.
     */
    SearchService(
        Trie& trie,
        FoodDataManager& foodDataManager
    );

    /*
     * 음식 이름을 정확하게 검색한다.
     * 검색된 음식의 Food 객체를 반환한다.
     */
    const Food& search(const std::string& foodName);

    /*
     * 입력한 prefix로 시작하는 음식들을 검색한다.
     * 검색된 음식의 Food 객체들을 반환한다.
     */
    std::vector<const Food*> autoComplete(
        const std::string& prefix
    );

    /*
     * 입력한 음식 이름과 편집 거리가
     * maxDistance 이하인 음식들을 검색한다.
     * 검색된 음식의 Food 객체들을 반환한다.
     */
    std::vector<const Food*> approximateSearch(
        const std::string& target,
        int maxDistance
    );

private:
    Trie& trie;
    FoodDataManager& foodDataManager;
};