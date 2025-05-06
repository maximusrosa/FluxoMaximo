#pragma once
#include "ford_fulkerson.hpp"
#include <filesystem>

using namespace std;
namespace fs = filesystem;

struct GraphInfo {
    string type;
    int numVertices;
    int numEdges;
};

void printUsage(const char* programName) {
    cerr << "Uso: " << programName << " <arquivo_de_grafo> <método_de_busca>" << endl;
    cerr << "Métodos de busca disponíveis: bfs, dfs, fattest" << endl;
}

void parseArguments(int argc, char *argv[], string& filePath, AugPathFinder& pathFinder, string& methodName) {
    if (argc != 3) {
        cerr << "Número inválido de argumentos." << endl;
        printUsage(argv[0]);
        exit(1);
    }

    filePath = argv[1];
    string searchMethod = argv[2];

    switch (searchMethod[0]) {
        case 'b':
            pathFinder = bfs;
            methodName = "bfs";
            break;
        case 'd':
            pathFinder = dfs;
            methodName = "dfs";
            break;
        case 'f':
            pathFinder = fattestPath;
            methodName = "fattest";
            break;
        default:
            cerr << "Método de busca inválido: " << searchMethod << endl;
            printUsage(argv[0]);
            exit(1);
    }
}

string getGraphTypeFromPath(const string& filePath) {
    fs::path path(filePath);
    auto parent = path.parent_path(); // graphs/matching
    return parent.filename();         // matching
}

void saveStatsToCSV(const string& filename, const GraphInfo& graphInfo, const FFstats& stats) {
    ofstream file(filename, ios::app); // append

    // Cabeçalho
    if (file.tellp() == 0) {
        file << "graph_type,n,m,max_flow,r,exec_time_ms,"
             << "s_bar,t_bar,"
             << "i_bar,d_bar,u_bar\n";
    }

    file << graphInfo.type << ","
         << graphInfo.numVertices << ","
         << graphInfo.numEdges << ","
         << stats.max_flow << ","
         << stats.r << ","
         << stats.exec_time_ms << ","
         << stats.searchStats.s_bar << ","
         << stats.searchStats.t_bar << ","
         << stats.searchStats.i_bar << ","
         << stats.searchStats.d_bar << ","
         << stats.searchStats.u_bar << "\n";
}