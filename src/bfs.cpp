#include "bfs.hpp"

bool bfs(Graph& g, int source, int sink, vector<bool>& visited, vector<Edge*>& path) {
    queue<int> q;
    vector<Edge*> parent(g.getNumVertices(), nullptr);
    q.push(source);
    visited[source] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == sink) {
            // Reconstrói o caminho a partir do nó de destino
            while (parent[u] != nullptr) {
                path.push_back(parent[u]);
                u = parent[u]->residual->to;
            }
            reverse(path.begin(), path.end());
            
            return true;
        }

        // Verifica se existe pseudocaminho aumentante
        for (Edge* e : g.getAdjList(u)) {
            if (!visited[e->to] && e->residualCapacity() > 0) {
                q.push(e->to);
                visited[e->to] = true;
                parent[e->to] = e;
            }
        }
    }

    return false;
}