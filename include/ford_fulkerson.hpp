#pragma once
#include "graph.hpp"
#include "path_finding/dfs.hpp"
#include "path_finding/bfs.hpp"
#include "path_finding/fattest_path.hpp"
#include <chrono>
#include <math.h>

using namespace chrono;

struct FFstats {
    int max_flow;          // Maximum flow found
    double r;              // Ratio I / Ī (actual vs. expected iterations)
    double exec_time_ms;   // Execution time in milliseconds

    // Print stats in a readable format
    void print() const {
        cout << "Max Flow: " << max_flow << "\n"
             << "Iteration Ratio (r): " << r << "\n"
             << "Execution Time: " << exec_time_ms << " ms\n";
    }
};

typedef bool (*AugPathFinder)(Graph&, int, int, vector<bool>&, vector<Edge*>&); // algoritmo de busca de caminho aumentante

void printPath(const vector<Edge*>& path, int pathFlow);

int fordFulkerson(Graph& g,
                    AugPathFinder augPathFind);