// Copyright 2022 NNTU-CS
#include <stdio.h>
#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include <fstream>
#include "tree.h"

using std::vector;
using std::cout;
using std::endl;

int main() {
    // Пример входного вектора
    vector<char> input = {'1', '2', '3'};

    // Создаем дерево перестановок
    PMTree tree(input);

    // Получаем все перестановки
    vector<vector<char>> allPerms = getAllPerms(tree);

    // Вывод всех перестановок
    cout << "Все перестановки:" << endl;
    for (const auto& perm : allPerms) {
        for (char c : perm)
            cout << c;
        cout << endl;
    }

    // Запрашиваем перестановки по номеру
    int permNum1 = 1;
    int permNum2 = 2;

    vector<char> p1 = getPerm1(tree, permNum1);
    vector<char> p2 = getPerm2(tree, permNum2);

    cout << "\nПерестановка #" << permNum1 << " (через getPerm1): ";
    for (char c : p1) cout << c;
    cout << endl;

    cout << "Перестановка #" << permNum2 << " (через getPerm2): ";
    for (char c : p2) cout << c;
    cout << endl;

    return 0;
}
