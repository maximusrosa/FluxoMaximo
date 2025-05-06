#pragma once
#include "graph.hpp"
#include "path_finding/dfs.hpp"
#include "path_finding/bfs.hpp"
#include "path_finding/fattest_path.hpp"
#include <chrono>
#include <math.h>

using namespace chrono;

struct FFstats {
    int max_flow = 0;          
    double r = 0;              // Ratio I / Ī (actual vs. expected iterations)
    double exec_time_ms = 0;
     
    PathSearchStats searchStats; // Statistics from the path search algorithm

    void print() const {
        cout << "Max Flow: " << max_flow << "\n"
             << "Iteration Ratio (r): " << r << "\n"
             << "Execution Time: " << exec_time_ms << " ms\n";

        cout << "Path Search Stats:\n";
        cout << "s_bar: " << searchStats.s_bar << "\n";
        cout << "t_bar: " << searchStats.t_bar << "\n";
        
        cout << "i_bar: " << searchStats.i_bar << "\n";
        cout << "d_bar: " << searchStats.d_bar << "\n";
        cout << "u_bar: " << searchStats.u_bar << "\n";
    }
};

typedef bool (*AugPathFinder)(Graph&, int, int, vector<bool>&, vector<Edge*>&, PathSearchStats&); // algoritmo de busca de caminho aumentante

void printPath(const vector<Edge*>& path, int pathFlow);

FFstats fordFulkerson(Graph& g,
                    AugPathFinder augPathFind);