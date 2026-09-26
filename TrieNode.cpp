// TrieNode.cpp
#include "TrieNode.h"

TrieNode::TrieNode() {
    isEnd = false;
    foodId = "";
}

TrieNode::~TrieNode() {
    for (const auto& child : children) {
        delete child.second;
    }
}