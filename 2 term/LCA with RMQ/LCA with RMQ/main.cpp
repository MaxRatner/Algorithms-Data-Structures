#include <iostream>
#include <vector>

using namespace std;

typedef vector<int>::const_iterator iter;

class Graph {
public:
    void DFS(int, int);
    void Build_tree(int, int, int);
    void Prepare(int);
    
    long long Tree_min(long long, long long, long long, long long, long long);
    long long LCA(long long, long long);
    
    void solver();
private:
    vector < vector<int> > g;
    
    vector<int> h;
    vector<int> dfs_list;
    vector<int> first;
    vector<int> tree;
    vector<char> dfs_used;
};

void Graph::DFS(int v, int k = 1) {
    dfs_used[v] = true;
    h[v] = k;
    dfs_list.push_back(v);
    
    for (iter i = g[v].begin(); i != g[v].end(); i++) {
        if (!dfs_used[*i]) {
            DFS(*i, k + 1);
            dfs_list.push_back(v);
        }
    }
}

void Graph::Build_tree(int i, int l, int r) {
    
    if (l == r)
        tree[i] = dfs_list[l];
    
    else {
        int m = (l + r) >> 1;
        Build_tree (2 * i, l, m);
        Build_tree (2 * i + 1, m + 1, r);
        
        if (h[tree[2 * i]] < h[tree[2 * i + 1]])
            tree[i] = tree[2 * i];
        else
            tree[i] = tree[2 * i + 1];
    }
}

void Graph::Prepare(int root) {
    int n = (int)g.size();
    h.resize(n);
    dfs_list.reserve(n * 2);
    dfs_used.assign(n, 0);
    
    DFS(root);
    
    int m = (int)dfs_list.size();
    tree.assign(dfs_list.size() * 4 + 1, -1);
    Build_tree(1, 0, m-1);
    
    first.assign(n, -1);
    for (int i = 0; i < m; i++) {
        int v = dfs_list[i];
        if (first[v] == -1) {
            first[v] = i;
        }
    }
}

long long Graph::Tree_min(long long i, long long sl, long long sr, long long l, long long r) {
    if (sl == l && sr == r) {
        return tree[i];
    }
    long long sm = (sl + sr) >> 1;
    
    if (r <= sm) {
        return Tree_min(2 * i, sl, sm, l, r);
    }
    
    if (l > sm) {
        return Tree_min(2 * i +1, sm + 1, sr, l, r);
    }
    
    long long ans1 = Tree_min(2 * i, sl, sm, l, sm);
    long long ans2 = Tree_min(2 * i + 1, sm + 1, sr, sm + 1, r);
    
    return h[ans1] < h[ans2] ? ans1 : ans2;
}

long long Graph::LCA(long long a, long long b) {
    int left = first[a];
    int right = first[b];
    
    if (left > right) {
        swap (left, right);
    }
    
    return Tree_min (1, 0, dfs_list.size() - 1, left, right);
}

void Graph::solver() {
    int root = 0;
    int n, m;
    cin >> n >> m;
    g = vector<vector<int> >(n);
    
    g[0].push_back(0);
    
    for (int i = 1; i < n; i++) {
        int a;
        cin >> a;
        g[a].push_back(i);
    }
    
    long long a1, a2,x, y, z;
    cin >> a1 >> a2 >> x >> y >> z;
    
    Prepare(root);
    
    long long v, answer, a3, a4;
    v = LCA(a1, a2);
    answer = v;
    a3 = (x * a1 + y * a2 + z) % n;
    a4 = (x * a2 + y * a3 + z) % n;
    a1 = a3;
    a2 = a4;
    
    for (int i = 0; i < m - 1; i++) {
        v = LCA((a1 + v) % n, a2);
        answer = answer + v;
        a3 = (x * a1 + y * a2 + z) % n;
        a4 = (x * a2 + y * a3 + z) % n;
        a1 = a3;
        a2 = a4;
    }
    
    cout << answer;
}

int main() {
    Graph graph;
    
    graph.solver();
    
    return 0;
}
