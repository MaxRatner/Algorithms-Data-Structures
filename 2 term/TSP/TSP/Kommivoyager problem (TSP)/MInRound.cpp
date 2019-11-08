#include "MinOst.h"

/*void Graph::DFS(int v, vector<bool> &visited) {
    visited[v] = true;
    round.push_back(v);
    
    for (int i = 0; i < ostov[v].size(); i++) {
        if (!visited[ostov[v][i]]) {
            DFS(ostov[v][i], visited);
        }
    }
}

double Graph::FindRound() {
    vector <bool> visited(n, false);
    
    DFS(0, visited);
    
    round.push_back(0);
    double answer = 0;
    for( int i = 0; i < round.size() - 1; i++ ) {
        answer += g[round[i]][round[i + 1]];
    }
    
    return answer;
}*/
