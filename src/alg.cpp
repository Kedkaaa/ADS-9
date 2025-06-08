// Copyright 2022 NNTU-CS
#include  <iostream>
#include  <fstream>
#include  <locale>
#include  <cstdlib>
#include <algorithm>
#include <stdexcept>
#include  "tree.h"

PMTree::Node::~Node() {
    for (auto child : children)
        delete child;
}

PMTree::PMTree(const std::vector<char>& elems) {
    root = new Node('\0'); // фиктивный корень
    buildTree(root, elems);
}

PMTree::~PMTree() {
    delete root;
}

void PMTree::buildTree(Node* node, std::vector<char> remaining) {
    if (remaining.empty()) return;

    for (size_t i = 0; i < remaining.size(); ++i) {
        char val = remaining[i];
        Node* child = new Node(val);
        node->children.push_back(child);

        std::vector<char> nextRemaining = remaining;
        nextRemaining.erase(nextRemaining.begin() + i);
        buildTree(child, nextRemaining);
    }
}

void dfs(PMTree::Node* node, std::vector<char>& path, std::vector<std::vector<char>>& result) {
    if (node->value != '\0') path.push_back(node->value);
    if (node->children.empty()) result.push_back(path);
    else {
        for (auto child : node->children) {
            dfs(child, path, result);
        }
    }
    if (node->value != '\0') path.pop_back();
}

std::vector<std::vector<char>> getAllPerms(PMTree& tree) {
    std::vector<std::vector<char>> result;
    std::vector<char> path;
    dfs(tree.root, path, result);
    return result;
}

std::vector<char> getPerm1(PMTree& tree, int num) {
    auto all = getAllPerms(tree);
    if (num < 1 || num > (int)all.size()) return {};
    return all[num - 1];
}

int factorial(int n) {
    return (n <= 1) ? 1 : n * factorial(n - 1);
}

std::vector<char> getPerm2(PMTree& tree, int num) {
    std::vector<char> result;
    std::vector<char> available;

    for (auto child : tree.root->children)
        available.push_back(child->value);

    std::sort(available.begin(), available.end());

    --num;
    while (!available.empty()) {
        int n = available.size();
        int f = factorial(n - 1);
        int index = num / f;

        if (index >= (int)available.size()) return {}; // номер слишком большой

        result.push_back(available[index]);
        available.erase(available.begin() + index);
        num %= f;
    }

    return result;
}

