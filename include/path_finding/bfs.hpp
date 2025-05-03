#pragma once
#include "graph.hpp"
#include <queue>

bool bfs(Graph& g, int source, int sink, vector<bool>& visited, vector<Edge*>& path);