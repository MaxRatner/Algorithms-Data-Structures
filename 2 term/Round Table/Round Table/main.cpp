#include <iostream>
#include <vector>
#include <math.h>
#include <iomanip>
#include <queue>
#include <stack>

using namespace std;

class RoundTable {
public:
    void Solver();
    void Read();
    bool Find_path(const vector<vector<int>> &graph, double  mid);
private:
    vector<pair<int, int> > columns;
    int x_left, x_right, r, n;
};

bool RoundTable::Find_path(const vector<vector<int>> &graph, double mid) {
    vector<bool> used(graph.size(), false);
    queue<int> verts;
    
    for(int i = 0; i < graph.size(); i++) {
        if (columns[i].first - r - x_left < mid) {
            if (x_right - columns[i].first - r < mid) {
                return true;
            }
            verts.push(i);
        }
    }
    
    while (!verts.empty()) {
        stack<int> way_stack;
        way_stack.push(verts.front());
        used[verts.front()] = true;
        verts.pop();
        
        while (!way_stack.empty()) {
            int temp = way_stack.top();
            way_stack.pop();
            
            for (int i = 0; i < graph[temp].size(); i++) {
                if(!used[graph[temp][i]]) {
                    if (x_right - columns[graph[temp][i]].first - r < mid) {
                        return true;
                    }
                    used[graph[temp][i]] = true;
                    way_stack.push(graph[temp][i]);
                }
            }
        }
    }
    return false;
}

void RoundTable::Read() {
    cin >> x_left >> x_right >> r >> n;
    
    for ( int i = 0; i < n; i++) {
        pair<int, int> column;
        cin >> column.first >> column.second;
        columns.push_back(column);
    }
}

void RoundTable::Solver() {
    double right = x_right - x_left;
    double left = 0;
    while(right - left > 0.00001) {
        
        vector<vector<int> > graph(n);
        double mid = (right + left) / 2;
        
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                int x = columns[i].first - columns[j].first;
                int y = columns[i].second - columns[j].second;
                double len = sqrt(pow(x, 2) + pow(y, 2)) - 2 * r;
                if (len < mid) {
                    graph[i].push_back(j);
                }
            }
        }
        
        if (Find_path(graph, mid)) {
            right = mid;
        } else {
            left = mid;
        }
    }
    
    cout << fixed << setprecision(3) << left;
}

int main() {
    RoundTable task;
    task.Read();
    task.Solver();
    
    return 0;
}
