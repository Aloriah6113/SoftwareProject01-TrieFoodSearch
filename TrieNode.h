// TrieNode.h
#pragma once
#include <map>
#include <string>


class TrieNode {
public:
    TrieNode();
    ~TrieNode();

    friend class Trie;

private:
    std::map<char, TrieNode*> children;
    bool isEnd;
    std::string foodId;
};