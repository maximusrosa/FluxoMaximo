#include "ford_fulkerson.hpp"

bool dfs(Graph& g, int source, int sink, vector<bool>& visited, vector<Edge*>& path) {
    vector<int> stack;
    vector<Edge*> parent(g.getNumVertices(), nullptr);
    stack.push_back(source);

    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();

        if (u == sink) {
            while (parent[u] != nullptr) {
                path.push_back(parent[u]);
                u = parent[u]->residual->to;
            }
            reverse(path.begin(), path.end());
            return true;
        }

        visited[u] = true;

        for (Edge* e : g.getAdjList(u)) {
            if (!visited[e->to] && e->residualCapacity() > 0) {
                stack.push_back(e->to);
                parent[e->to] = e;
            }
        }
    }

    return false;
}

int fordFulkerson(Graph& g, 
                  function<bool(Graph&, int, int, vector<bool>&, vector<Edge*>&)> pathFind, 
                  int source, int sink) { 
    int maxFlow = 0;
    vector<Edge*> path;
    vector<bool> visited;

    while (true) {
        visited.assign(g.getNumVertices(), false);
        path.clear();
        if (!pathFind(g, source, sink, visited, path)) break;

        int pathFlow = INT_MAX;
        for (Edge* e : path) {
            pathFlow = min(pathFlow, e->residualCapacity());
        }

        for (Edge* e : path) {
            e->augment(pathFlow);
        }

        maxFlow += pathFlow;

        vector<int> pathVertices;
        pathVertices.push_back(source);
        for (Edge* e : path) {
            pathVertices.push_back(e->to);
        }

        cout << "Path: ";
        for (size_t i = 0; i < pathVertices.size(); ++i) {
            cout << pathVertices[i];
            if (i < pathVertices.size() - 1) cout << " -> ";
        }
        cout << ", Flow: " << pathFlow << "\n";
    }

    return maxFlow;
}
