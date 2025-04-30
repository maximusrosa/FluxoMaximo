#include "dfs.hpp"

bool dfs(Graph& g, int source, int sink, vector<bool>& visited, vector<Edge*>& path) {
    vector<int> stack;
    vector<Edge*> parent(g.getNumVertices(), nullptr);
    stack.push_back(source);

    while (!stack.empty()) {
        int u = stack.back();
        stack.pop_back();

        if (u == sink) {
            // Reconstrói o caminho a partir do nó de destino
            while (parent[u] != nullptr) {
                path.push_back(parent[u]);
                u = parent[u]->residual->to;
            }
            reverse(path.begin(), path.end());
            
            return true;
        }

        visited[u] = true;

        // Verifica se existe pseudocaminho aumentante
        for (Edge* e : g.getAdjList(u)) {
            if (!visited[e->to] && e->residualCapacity() > 0) {
                stack.push_back(e->to);
                parent[e->to] = e;
            }
        }
    }

    return false;
}
