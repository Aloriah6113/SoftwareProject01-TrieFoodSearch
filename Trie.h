// Trie.h
#pragma once

#include <string>
#include <vector>

class TrieNode;

class Trie {
public:
    Trie();
    
    ~Trie();

    TrieNode* insert(const std::string& foodName, const std::string& foodId);

    std::string search(const std::string& foodName);

    std::vector<std::string> autoComplete(const std::string& prefix);

    std::string approximateSearch(const std::string& input, int maxDistance = 1);

private:
    TrieNode* root;

    void dfs(TrieNode* node, std::vector<std::string>& foodIds);
};