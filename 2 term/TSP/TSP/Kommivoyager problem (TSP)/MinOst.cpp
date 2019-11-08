#include "MinOst.h"

void Graph::Prim() {
    
    vector<int> path;
    //path.push_back(0);
    
    vector<double> min(n, N);
    set<pair<int, int>> unused_verts;
    
    set<int> used;
    
    unused_verts.insert(make_pair(0, 0));
    min[0] = 0;
    
    vector<int> parents(n, -1);
    parents[0] = 0;
    
    ostov = vector<vector<int> >(n, vector<int>());

    for (int i = 0; i < n; i++) {
        if (unused_verts.empty()) {
            break;
        }
        
        // Берем вершину с минимальным ребром
        int v = unused_verts.begin()->second;
        unused_verts.erase(unused_verts.begin());
        used.insert(v);
        
        if (v != 0) {
            ostov[v].push_back(parents[v]);
            ostov[parents[v]].push_back(v);
        }
        
        //path.push_back(v);
        
        // Обновляем минимальное растояние до каждой вершины
        
        for (int to = 0; to < n; to++) {
            if (g[v][to] == 0 || v == to) {
                continue;
            }
            if (g[v][to] < min[to] && used.count(to) == 0) {
                unused_verts.erase(make_pair(min[to], to));
                min[to] = g[v][to];
                parents[to] = v;
                unused_verts.insert(make_pair(min[to], to));
            }
        }
    }
}

void Graph::DFS(int v, vector<bool> &visited) {
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
    
    double answer = 0;
    for (int i = 0; i < round.size() - 1; i++) {
        answer += g[round[i]][round[i + 1]];
    }
    
    return answer;
}
