#pragma once
#include "graph.hpp"

bool dfs(Graph& g, int source, int sink, vector<bool>& visited, vector<Edge*>& path);