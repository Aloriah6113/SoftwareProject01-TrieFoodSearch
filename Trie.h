// Trie.h
#pragma once

#include <string>
#include <vector>

class TrieNode;

class Trie {
public:
    Trie();
    
    ~Trie();

    void insert(const std::string& foodName, const std::string& foodId);

    std::string search(const std::string& foodName);

    std::vector<std::string> autoComplete(const std::string& prefix);

    std::vector<std::string> approximateSearch(
        const std::string& target,
        int maxDistance
    );

private:
    TrieNode* root;

    void dfs(TrieNode* node, std::vector<std::string>& foodIds);

    void approximateSearch(
        TrieNode* node,
        const std::string& target,
        const std::string& currentWord,
        const std::vector<int>& previousRow,
        int maxDistance,
        std::vector<std::string>& results
    );
};