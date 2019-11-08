#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

class Graph {
public:
    Graph() {};
    void ReadGraph();
    int MaxFlow();
    int BFS();
private:
    int n, m;
    vector<vector<int> > g;
    vector<vector<int> > f;
    int N = 100000000;
};

void Graph::ReadGraph() {
    cin >> n >> m;
    g = vector<vector<int> >(n, vector<int>(n, 0));
    for (int i = 0; i < m; i++){
        int a, b, l;
        cin >> a >> b >> l;
        
        g[a - 1][b - 1] = l;
    }
}

int Graph::BFS() {
    int s = 0;
    int t = n - 1;
    // Первая вершина в очереди
    queue<int> q;
    q.push(s);

    // Родители
    vector<int> parents(n, N);
    parents[s] = 0;
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        if (u == t) {
            break;
        }
        
        for (int i = 0; i < n; i++) {
            int v = i;
            // Если есть поток
            if (f[u][v] == 0){
                continue;
            }
            
            // Если вершина еще не посещена
            if (parents[v] == N) {
                parents[v] = u;
                q.push(v);
            }
        }
    }
    
    if (parents[n - 1] == N) {
        return 0;
    }
    
    int ans = N;
    int v = n - 1;
    int v_par = parents[v];
    while (v != 0) {
        v_par = parents[v];
        if(f[v_par][v] < ans) {
            ans = f[v_par][v];
        }
        v = v_par;
    }
    
    v = n - 1;
    while (v != 0) {
        v_par = parents[v];
        f[v][v_par] += ans;
        f[v_par][v] = max(0, f[v_par][v] - ans);
        v = v_par;
    }
    
    return ans;
}

int Graph::MaxFlow() {
    int ans = 0;
    int flow = -1;
    f = g;
    while (flow > 0 || flow == -1) {
        flow = BFS();
        ans += flow;
    }
    return ans;
}

int main() {
    Graph graph;
    graph.ReadGraph();
    int max_flow = graph.MaxFlow();
    
    cout << max_flow;
    return 0;
}
