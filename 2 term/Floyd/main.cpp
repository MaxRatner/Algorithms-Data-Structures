#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

const int N = 1000000000;
class Graph{
public:
    Graph(){};
    void ReadGraph();
    void Floyd();
    //void ArbitrageCheck();
private:
    vector< vector <float> > graph;
    int n;
};

void Graph::ReadGraph(){
    
    cin >> n;
    
    for (int i = 0; i < n; i++){
        vector<float> temp(n, 1);
        graph.push_back(temp);
    }
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            if (i == j){
                continue;
            }
            float l;
            cin >> l;
            if (l == -1){
                l = N;
            }
            graph[i][j] = l;
        }
    }
};

void Graph::Floyd(){
    
    int A[n + 1][n][n];
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            A[0][i][j] = graph[i][j];
        }
    }
    
    for (int k = 1; k <= n; k++){
        for (int i = 0; i < n; i++){
            for (int j = 0; j < n; j++){
                A[k][i][j] = max(A[k - 1][i][j], A[k - 1][i][k - 1] * A[k - 1][k - 1][j]);
            }
        }
    }
    
    
    bool flag = false;
    for (int i = 0; i < n; i++){
        if (A[n][i][i] > 1){
            cout << "YES";
            flag = true;
            break;
        }
    }
    
    if (!flag){
        cout << "NO";
    }
}

int main(){
    
    Graph g;
    g.ReadGraph();
    g.Floyd();
    
    return 0;
}
