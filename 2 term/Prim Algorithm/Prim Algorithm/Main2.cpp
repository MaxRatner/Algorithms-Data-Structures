//
//  Дан неориентированный связный граф. Требуется найти вес минимального
//  остовного дерева в этом графе.
//  Вариант 1. С помощью алгоритма Прима.
//

#include <iostream>
#include <vector>

using namespace std;

const int N = 100000000;

class Graph{
public:
    void ReadGraph();
    void Prim();
    
private:
    int n, m;//Vertexes and edges
    vector<vector<pair<int, int> > > g;
    
};

void Graph::ReadGraph(){
    
    cin >> n >> m;
    g = vector<vector<pair<int, int> > >(n + 1);
    
    for (int i = 0; i < m; i++){
        int a, b, len;
        cin >> a >> b >> len;
        bool flag = false;
        for (int j = 0; j < g[a].size(); j++){
            //Если уже есть в массиве, убираем двойные ребра
            if (g[a][j].first == b){
                if (len < g[a][j].second){
                    g[a][j].second = len;
                    flag = true;
                }
            }
        }
        if (flag){
            for (int j = 0; j < g[b].size(); j++){
                //Если уже есть в массиве, убираем двойные ребра
                if (g[b][j].first == a){
                    if (len < g[b][j].second){
                        g[b][j].second = len;
                    }
                }
            }
        }
        
        //Если это ребро в первый раз
        if (!flag){
            g[a].push_back(make_pair(b, len));
            g[b].push_back(make_pair(a, len));
        }
    }
    
    
}

void Graph::Prim(){
    
    vector<int> min(n + 1, N);
    vector<bool> used(n + 1, false);
    min[1] = 0;
    long long sum = 0;
    
    for (int i = 0; i < n; i++){
        int v = -1;
        // Выбираем вершину с минимальным ребром
        for (int j = 1; j <= n; j++){
            if (!used[j] && (v == -1 || min[j] < min[v])){
                v = j;
            }
        }
        sum += min[v];
        used[v] = true;
        
        for (int to = 0; to < g[v].size(); to++){
            if (!used[g[v][to].first] && g[v][to].second < min[g[v][to].first]){
                min[g[v][to].first] = g[v][to].second;
            }
        }
    }
    cout << sum;
}

int main() {
    Graph graph;
    graph.ReadGraph();
    graph.Prim();
    
    return 0;
}
