#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct PathSearchStats {
    vector<double> s_i;  // n_i' / n
    vector<double> t_i;  // m_i' / m
    double s_bar;
    double t_bar;
    // Heap operations (if applicable)
    vector<int> heap_insert_ops, heap_deletemin_ops, heap_update_ops;

    void print() const {
        cout << "Vertex Coverage (s̄): " << s_bar << "\n"
                  << "Edge Coverage (t̄): " << t_bar << "\n";
    }
};
