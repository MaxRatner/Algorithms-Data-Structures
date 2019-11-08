#include <vector>
#include <set>
#include <iostream>

using namespace std;

const int N = 1000000000;

class Graph {
public:
    Graph(){};
    void ReadGraph();
    void Dijkstra();
private:
    int n, m;//вершины и ребра соответственно
    vector<vector<pair<int, int> > > graph;
    int a, b;
};

void Graph::ReadGraph() {
    cin >> n >> m;
    vector<vector<pair<int, int> > > graph;//объявляем граф
    /*for (int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            vector<pair<int, int> > temp(n, make_pair(0, 0));
        }
    }*/
    
    for(int i = 0; i < m; i++){
        int in, out, l;
        cin >> in >> out >> l;
        //заполняем граф
        graph[in].push_back(make_pair(l, out));
        graph[out].push_back(make_pair(l, in));
    }
    
    
    cin >> a >> b;
};

void Graph::Dijkstra(){
    
    int s = a;
    vector<long long> d(n, N);
    d[s] = 0;
    
    set<pair<int, int> > verticles;
    pair<int, int> start = make_pair(0, s);
    verticles.insert(start);
    
    
    while(!verticles.empty()){
        
        //Выбираем вершину с наименьшим d
        int u = verticles.begin()->second;
        verticles.erase(verticles.begin());
        
        //Проводим релаксацию
        for (auto v: graph[u]){
            int j = v.first;
            int wt = v.second;
            
            if (d[j] > wt + d[u]){
                verticles.erase(make_pair(d[j], j));
                d[j] = d[u] + wt;
                verticles.insert(make_pair(d[j], j));
                /*
                pair<int, int> temp = make_pair(d[v.second], v.second);
                verticles.erase(temp);
                d[v.second] = v.first + d[u];
                temp = make_pair(d[v.second], v.second);
                verticles.insert(temp);*/
            }
        }
    }
    
    //Вывод расстояния
    cout << d[b];
}

int main(){
    
    Graph g;
    g.ReadGraph();
    
    g.Dijkstra();
    return 0;
}
