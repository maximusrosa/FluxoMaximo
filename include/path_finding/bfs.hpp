#pragma once
#include "graph.hpp"
#include "path_finding/search_stats.hpp"
#include <queue>

bool bfs(Graph& g, int source, int sink, vector<bool>& visited, vector<Edge*>& path, PathSearchStats& stats);