#pragma once
#include "graph.hpp"

bool dfs(Graph& g, int source, int sink, vector<bool>& visited, vector<Edge*>& path);

int fordFulkerson(Graph& g,
                  function<bool(Graph&, int, int, vector<bool>&, vector<Edge*>&)> pathFind,
                  int source, int sink);