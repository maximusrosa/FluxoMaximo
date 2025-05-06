#pragma once
#include <iostream>
#include <vector>

using namespace std;

struct PathSearchStats {
    // Percentual of vertices and edges covered (s̄ and t̄)
    double s_bar, t_bar = 0;

    // Heap operations (for Fattest Path)
    double i_bar = 0; // insert / number of vertices
    double d_bar = 0; // deletemin / number of vertices
    double u_bar = 0; // update / number of edges
};
