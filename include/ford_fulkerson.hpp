#pragma once
#include "graph.hpp"

typedef bool (*AugPathFinder)(Graph&, int, int, vector<bool>&, vector<Edge*>&); // algoritmo de busca de caminho aumentante

int fordFulkerson(Graph& g,
                    AugPathFinder augPathFind);