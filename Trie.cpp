// Trie.cpp
#include "Trie.h"
#include "TrieNode.h"

#include <string>
#include <vector>
#include <algorithm>

using std::string;
using std::vector;


Trie::Trie() {
    root = new TrieNode;
}

Trie::~Trie() {
    delete root;
}

/*
 * 음식 이름을 문자 단위로 순회하면서 Trie에 삽입한다.
 * 해당 문자의 자식 노드가 존재한다면 해당 노드로 이동하고,
 * 존재하지 않으면 새로운 TrieNode를 생성하여 연결한다.
 */
TrieNode* Trie::insert(const string& foodName, const string& foodId) {
    TrieNode* current = root;
    int idx = 0;
    
    for (char ch : foodName) {
        // 현재 문자에 해당하는 자식 노드가 없으면 새로 생성한다.
        if (current->children.find(ch) ==
            current->children.end()) {
            current->children[ch] = new TrieNode;
        }

        // 해당 문자의 자식으로 이동한다.
        current = current->children[ch];
    }
    
    current->isEnd = true;
    current->foodId = foodId;

    return root;  // 근데 이거 return 없어도 되는거 아닌가?
}

/*
 * 음식 이름을 검색한다.
 * 음식 이름에 해당하는 노드까지 이동한 후,
 * 해당 노드가 음식명의 끝이라면 foodId를 반환한다.
 * 없다면 빈 문자열을 반환한다.
 */
string Trie::search(const string& foodName) {
    TrieNode* current = root;
    
    // 현재 문자에 해당하는 자식 노드가 존재하면 해당 노드로 이동한다.
    for (char ch : foodName) {
        if (current->children.find(ch) !=
            current->children.end()) {
            current = current->children[ch];
        }
        else {
            return "";
        }
    }
    
    if (current->isEnd == true) {
        return current->foodId;
    }
}
 
/*
 * 매개변수로 받은 node부터 하위 노드를 DFS로 탐색한다.
 * 현재 노드가 음식 이름의 끝이라면,
 * 해당 노드의 foodId를 foodIds에 추가한다.
 * 
 * foodIds는 참조로 전달하여 재귀 호출에서도
 * 동일한 결과 벡터에 foodId를 누적한다.
 */
void Trie::dfs(TrieNode* node, vector<string>& foodIds) {
    if (node->isEnd == true) {
        foodIds.push_back(node->foodId);
    }
    
    // 각 자식 노드로 이동하여 하위 노드를 재귀적으로 탐색한다.
    for (const auto& child : node->children) {
        // 각 자식 노드부터 다시 DFS를 수행한다.
        dfs(child.second, foodIds);
    }
}


/*
 * 입력한 문자열로 시작하는 음식들의 foodId를 검색한다.
 * 입력한 문자열에 해당하는 노드까지 이동한 후,
 * 해당 노드부터 DFS로 하위 노드들을 탬색하여
 * foodId들을 반환한다.
 * 
 * 입력한 문자열에 해당하는 노드가 없다면,
 * 빈 vector 반환한다.
 */
vector<string> Trie::autoComplete(const string& prefix) {
    TrieNode* current = root;
    vector<string> foodIds;
    
    // 입력받은 접두사의 마지막 노드로 이동
    for (char ch : prefix) {
        if (current->children.find(ch) !=
            current->children.end()) {
            current = current->children[ch];
        }
        else {
            return foodIds;
        }
    }

    dfs(current, foodIds);
    return foodIds;
}

vector<string> Trie::approximateSearch(
    const string& target,
    int maxDistance) {
    vector<string> results;

    // 첫 번째 DP row
    //
    // target이 빈 문자열이라고 생각했을 때
    // target의 앞쪽 j개 문자를 만드는 데 필요한 비용
    //
    // 예:
    // target = "apple"
    //
    // previousRow
    // [0, 1, 2, 3, 4, 5]
    vector<int> initialRow(target.size() + 1);

    for (int i = 0; i <= target.size(); ++i) {
        initialRow[i] = i;
    }

    // Trie의 root부터 탐색 시작
    approximateSearch(
        root,
        target,
        "",
        initialRow,
        maxDistance,
        results
    );

    return results;
}


void Trie::approximateSearch(
    TrieNode* node,
    const string& target,
    const string& currentWord,
    const vector<int>& previousRow,
    int maxDistance,
    vector<string>& results)
{
    for (const auto& child : node->children) {
        char ch = child.first;
        TrieNode* childNode = child.second;

        // 현재 Trie 경로에 새로운 문자를 추가한다.
        string currentWordWithChar = currentWord + ch;

        // 현재 Trie 경로에 대한 새로운 DP row
        vector<int> currentRow(target.size() + 1);

        // 첫 번째 열
        //
        // target이 빈 문자열일 때
        // currentWordWithChar의 모든 문자를 삭제해야 하므로
        // 편집 비용은 현재 문자열의 길이이다.
        currentRow[0] = currentWordWithChar.size();

        // target의 각 문자와 현재 Trie 문자를 비교한다.
        for (int j = 1; j <= target.size(); ++j) {
            if (ch == target[j - 1]) {
                // 문자가 같으면 추가적인 편집이 필요 없다.
                currentRow[j] = previousRow[j - 1];
            }
            else {
                // 세 가지 연산 중 최소 비용을 선택한다.
                //
                // previousRow[j]     : 삭제
                // currentRow[j - 1]  : 삽입
                // previousRow[j - 1]  : 치환
                currentRow[j] = 1 + std::min({
                    previousRow[j],
                    currentRow[j - 1],
                    previousRow[j - 1]
                    });
            }
        }

        // 현재 Trie 경로가 하나의 완성된 단어라면
        // target과의 편집 거리를 확인한다.
        //
        // currentRow의 마지막 값이
        // target 전체와 currentWordWithChar 사이의 편집 거리이다.
        if (childNode->isEnd &&
            currentRow[target.size()] <= maxDistance) {
            results.push_back(currentWordWithChar);
        }

        // 현재 Trie 가지에서 앞으로 더 내려갈 가능성이 있는지 확인한다.
        //
        // currentRow의 최솟값이 maxDistance보다 크다면
        // 이 가지 아래에서는 조건을 만족하는 단어를
        // 찾을 수 없으므로 더 이상 탐색하지 않는다.
        int minDistance = *std::min_element(
            currentRow.begin(),
            currentRow.end()
        );

        if (minDistance <= maxDistance) {
            approximateSearch(
                childNode,
                target,
                currentWordWithChar,
                currentRow,
                maxDistance,
                results
            );
        }
    }
}