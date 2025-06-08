// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TREE_H_
#define INCLUDE_TREE_H_
#include <vector>

class PMTree {
 public:
    struct Node {
        char value;
        std::vector<Node*> children;

        explicit Node(char v) : value(v) {}
        ~Node();
    };

    Node* root;

    explicit PMTree(const std::vector<char>& elems);
    ~PMTree();

 private:
    void buildTree(Node* node, std::vector<char> remaining);
};

// Генерация всех перестановок
std::vector<std::vector<char>> getAllPerms(PMTree& tree);

// Получение перестановки №num: способ 1 (перебором)
std::vector<char> getPerm1(PMTree& tree, int num);

// Получение перестановки №num: способ 2 (навигацией по дереву)
std::vector<char> getPerm2(PMTree& tree, int num);

#endif  // INCLUDE_TREE_H_
