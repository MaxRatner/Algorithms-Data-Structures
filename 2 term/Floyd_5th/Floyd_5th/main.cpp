#include <iostream>
#include <vector>

using namespace std;

class Graph{
public:
    Graph(){};
    void ReadGraph();
    void Floyd();
private:
    vector<vector <int> > graph;
    int n;
};

void Graph::ReadGraph(){
    
    cin >> n;
    
    for (int i = 0; i < n; i++){
        vector<int> temp(n, 0);
        graph.push_back(temp);
    }
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            int l;
            cin >> l;
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
                A[k][i][j] = min(A[k - 1][i][j], A[k - 1][i][k - 1] + A[k - 1][k - 1][j]);
            }
        }
    }
    
    for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            cout << A[n][i][j]  << ' ';
        }
        cout << endl;
    }
}

int main(){
    
    Graph g;
    g.ReadGraph();
    g.Floyd();
    
    return 0;
}
