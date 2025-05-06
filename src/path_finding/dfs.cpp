#include "path_finding/dfs.hpp"

bool dfs(Graph& g, int source, int sink, vector<bool>& visited, vector<Edge*>& path, PathSearchStats& stats) {
    stack<int> s;
    vector<Edge*> parent(g.getNumVertices(), nullptr);
    
    // Resetar o vetor de visitados antes de começar
    fill(visited.begin(), visited.end(), false);
    
    int vertexVisits = 0;
    int edgeVisits = 0;

    s.push(source);

    // Gerador de números aleatórios
    static minstd_rand rng(random_device{}());

    while (!s.empty()) {
        int u = s.top();
        s.pop();
        
        // Se não visitamos ainda, marque e incremente o contador
        if (!visited[u]) {
            visited[u] = true;
            vertexVisits++;
            
            // Verifique se é o destino imediatamente após marcar como visitado
            if (u == sink) {
                // Reconstrói o caminho a partir do nó de destino
                while (parent[u] != nullptr) {
                    path.push_back(parent[u]);
                    u = parent[u]->from;
                }
                reverse(path.begin(), path.end());
                
                // Acumula frações s_i e t_i
                stats.s_bar += static_cast<double>(vertexVisits) / g.getNumVertices();
                stats.t_bar += static_cast<double>(edgeVisits) / g.getNumResidualEdges();
                
                return true;
            }
            
            // Embaralha a lista de adjacência
            auto adjList = g.getAdjList(u);
            shuffle(adjList.begin(), adjList.end(), rng);
            
            for (Edge* e : adjList) {
                edgeVisits++;  // Aresta foi examinada
                
                if (!visited[e->to] && e->residualCapacity() > 0) {
                    s.push(e->to);
                    parent[e->to] = e;
                }
            }
        }
    }
    
    // Se falhou, ainda assim acumula stats
    stats.s_bar += static_cast<double>(vertexVisits) / g.getNumVertices();
    stats.t_bar += static_cast<double>(edgeVisits) / g.getNumResidualEdges();
    
    return false;
}