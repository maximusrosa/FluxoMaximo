#include "../include/ford_fulkerson.hpp"


int main(){
    DiGraph g;
    DiNode s,t;

    // Example usage
    cout << "Maximum flow using BFS: " << ford_fulkerson(g, s, t, "bfs") << endl;
    cout << "Maximum flow using DFS: " << ford_fulkerson(g, s, t, "dfs") << endl;
    cout << "Maximum flow using Fattest Path: " << ford_fulkerson(g, s, t, "fattest") << endl;
}

