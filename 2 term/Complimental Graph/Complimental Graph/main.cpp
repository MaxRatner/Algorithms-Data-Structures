#include <iostream>
#include<algorithm>
#include <vector>

using namespace std;

struct Component {
    vector<int> vertexes;
    Component(vector<int> arr_of_components) {
        for (int i = 0; i < arr_of_components.size(); i++) {
            vertexes.push_back(arr_of_components[i]);
        }
    }
};

class ComplementGraph {
public:
    ComplementGraph(int v, int e);
    void AddEdge(int v, int u);
    void DFS_Graph(int v);
    void DFS_TransGraph(int v);
    
    int GetAnswer();
private:
    int verts, edges;
    vector<vector<int>> arr, arr_transp;
    vector<Component> arr_of_components;
    vector<bool> used;
    vector<int> order, components;
    
    vector<vector<bool>> graph_of_components;
    vector<int> component_of_verticle;
};

ComplementGraph::ComplementGraph(int a, int b) {
    verts = a;
    edges = b;
    arr.resize(verts, vector<int>());
    arr_transp.resize(verts, vector<int>());
    used.resize(verts);
    component_of_verticle.resize(verts);
}

void ComplementGraph::AddEdge(int u, int v) {
    arr[u].push_back(v);
    arr_transp[v].push_back(u);
}

void ComplementGraph::DFS_Graph(int v) {
    used[v] = true;
    for (int i = 0; i < arr[v].size(); i++) {
        if (!used[arr[v][i]]) {
            DFS_Graph(arr[v][i]);
        }
    }
    order.push_back(v);
}

void ComplementGraph::DFS_TransGraph(int v) {
    used[v] = true;
    components.push_back(v);
    for (int i = 0; i < arr_transp[v].size(); i++) {
        if (!used[arr_transp[v][i]]) {
            DFS_TransGraph(arr_transp[v][i]);
        }
    }
}

int ComplementGraph::GetAnswer() {
    for (int i = 0; i < verts; i++) {
        if (!used[i]) {
            DFS_Graph(i);
        }
    }
    for (int i = 0; i < verts; i++) {
        used[i] = false;
    }
    for (int i = 0; i < verts; i++) {
        int cur = order[verts - i - 1];
        if (!used[cur]) {
            DFS_TransGraph(cur);
            arr_of_components.push_back(components);
            components.clear();
        }
    }
    if (arr_of_components.size() == 1) {
        return 0;
    }
    for (int i = 0; i < arr.size(); i++) {
        //находим, какой компоненте связности принадлежит данная вершина
        for (int k = 0; k < arr_of_components.size(); k++) {
            if (find(arr_of_components[k].vertexes.begin(), arr_of_components[k].vertexes.end(), i) != arr_of_components[k].vertexes.end()) {
                component_of_verticle[i] = k;
                break;
            }
        }
    }
    
    graph_of_components.resize(arr_of_components.size(), vector<bool>(arr_of_components.size()));
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < arr[i].size(); j++) {
            if (component_of_verticle[i] != component_of_verticle[arr[i][j]]) {
                graph_of_components[component_of_verticle[i]][component_of_verticle[arr[i][j]]] = true;
            }
        }
    }
    
    int x = 0;
    int y = 0;
    for (int i = 0; i < graph_of_components.size(); i++) {
        
        int cur_out = 0;
        for (int j = 0; j < graph_of_components.size(); j++) {
            if (graph_of_components[i][j] == true) {
                cur_out++;
                break;
            }
        }
        if (cur_out == 0) {
            x++;
        }
    }
    for (int i = 0; i < graph_of_components.size(); i++) {
        int cur_in = 0;
        for (int j = 0; j < graph_of_components.size(); j++) {
            if (graph_of_components[j][i] == true) {
                cur_in++;
                break;
            }
        }
        if (cur_in == 0) {
            y++;
        }
    }
    return max(x, y);
}

int main(){
    int v;
    int e;
    cin >> v;
    cin >> e;
    
    ComplementGraph graph(v, e);
    for (int i = 0; i < e; i++) {
        int a;
        int b;
        cin >> a >> b;
        graph.AddEdge(a - 1, b - 1);
    }
    cout << graph.GetAnswer();
}

