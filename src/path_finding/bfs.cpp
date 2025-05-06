#include "path_finding/bfs.hpp"

bool bfs(Graph& g, int source, int sink, vector<bool>& visited, vector<Edge*>& path, PathSearchStats& stats) {
    queue<int> q;
    vector<Edge*> parent(g.getNumVertices(), nullptr);
    
    // Reset visited array
    fill(visited.begin(), visited.end(), false);
    
    int vertexVisits = 0;
    int edgeVisits = 0;

    q.push(source);
    visited[source] = true;
    vertexVisits++;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == sink) {
            // Reconstruct path from sink to source
            while (parent[u] != nullptr) {
                path.push_back(parent[u]);
                u = parent[u]->from;
            }
            reverse(path.begin(), path.end());

            // Accumulate statistics
            stats.s_bar += static_cast<double>(vertexVisits) / g.getNumVertices();
            stats.t_bar += static_cast<double>(edgeVisits) / g.getNumResidualEdges();

            return true;
        }

        for (Edge* e : g.getAdjList(u)) {
            if (e->residualCapacity() > 0) {
                edgeVisits++;
                
                if (!visited[e->to]) {
                    visited[e->to] = true;
                    vertexVisits++;
                    q.push(e->to);
                    parent[e->to] = e;
                }
            }
        }
    }

    // Update statistics on failure
    stats.s_bar += static_cast<double>(vertexVisits) / g.getNumVertices();
    stats.t_bar += static_cast<double>(edgeVisits) / g.getNumResidualEdges();

    return false;
}