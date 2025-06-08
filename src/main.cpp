// Copyright 2022 NNTU-CS
#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <vector>
#include <matplot/matplot.h>
#include "tree.h"

using namespace std;
using namespace matplot;

void experiment() {
    vector<double> ns;
    vector<double> t1, t2, t3;

    random_device rd;
    mt19937 gen(rd());

    for (int n = 1; n <= 8; ++n) {
        vector<char> input;
        for (int i = 0; i < n; ++i)
            input.push_back('1' + i);

        PMTree tree(input);
        int total = factorial(n);
        uniform_int_distribution<> dis(1, total);

        int permIndex = dis(gen);

        auto start = chrono::high_resolution_clock::now();
        auto all = getAllPerms(tree);
        auto end = chrono::high_resolution_clock::now();
        t1.push_back(chrono::duration<double, milli>(end - start).count());

        start = chrono::high_resolution_clock::now();
        auto p1 = getPerm1(tree, permIndex);
        end = chrono::high_resolution_clock::now();
        t2.push_back(chrono::duration<double, milli>(end - start).count());

        start = chrono::high_resolution_clock::now();
        auto p2 = getPerm2(tree, permIndex);
        end = chrono::high_resolution_clock::now();
        t3.push_back(chrono::duration<double, milli>(end - start).count());

        ns.push_back(n);
    }

    semilogy(ns, t1, "-o")->label("getAllPerms");
    semilogy(ns, t2, "-x")->label("getPerm1");
    semilogy(ns, t3, "-s")->label("getPerm2");
    legend();
    xlabel("n (size of alphabet)");
    ylabel("Time (ms)");
    title("Time vs n for permutation algorithms");
    save("result/plot.png");
}

int main() {
    vector<char> in = {'1','2','3'};
    PMTree tree(in);

    cout << "All permutations:\n";
    auto all = getAllPerms(tree);
    for (const auto& perm : all) {
        for (char c : perm) cout << c;
        cout << '\n';
    }

    cout << "Perm #1: ";
    for (char c : getPerm1(tree, 1)) cout << c;
    cout << "\n";

    cout << "Perm #2: ";
    for (char c : getPerm2(tree, 2)) cout << c;
    cout << "\n";

    experiment();
  
    return 0;
}
