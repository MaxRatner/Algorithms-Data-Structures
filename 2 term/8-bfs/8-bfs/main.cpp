//Сейчас нужно написать positions и в конце каждой строки добавлять 0123 (RDLU)


#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <map>


using namespace std;

class Graph{
public:
    Graph(){}
    void BFS();
    void Positions(vector <int> &state, vector <vector <int> > &neighbors);
    char Symbol(int &m);
private:
    vector<int> octopus;//восьминашки
    vector<int> key = {1, 2, 3, 4, 5, 6, 7, 8, 0};
};

char Graph::Symbol(int &m){
    if (m == 0) return 'R';
        if (m == 1) {
            return 'D';
        } else {
            if (m == 2) {
                return 'L';
            } else {
                return 'U';
            }
        }
}

void Graph::Positions(vector <int> &current, vector <vector <int> > &neighbors){
    int null = 0;
    
    for (int i = 0; i < 9; i++){
        if (current[i] == 0){
            null = i;
        }
    }
    
    if (null != 8 && null != 5 && null != 2){
        vector<int> temp = current;
        swap(temp[null], temp[null + 1]);
        temp.push_back(0);
        neighbors.push_back(temp);
    }
    if (null != 6 && null != 7 && null != 8){
        vector<int> temp = current;
        swap(temp[null], temp[null + 3]);
        temp.push_back(1);
        neighbors.push_back(temp);
    }
    if (null != 0 && null != 3 && null != 6){
        vector<int> temp = current;
        swap(temp[null], temp[null - 1]);
        temp.push_back(2);
        neighbors.push_back(temp);
    }
    if (null != 0 && null != 1 && null != 2){
        vector<int> temp = current;
        swap(temp[null], temp[null - 3]);
        temp.push_back(3);
        neighbors.push_back(temp);
    }
}

void Graph::BFS(){
    
    //Reading start position
    for (int i = 0; i < 9; i++){
        int temp;
        cin >> temp;
        octopus.push_back(temp);
    }
    
    //Dynamic BFS
    queue<vector<int> > q;
    q.push(octopus);
    
    set<vector<int> > used;
    used.insert(octopus);
    
    map<vector<int>, string > way;
    map<vector<int>, int> length;
    way.insert(pair<vector<int>, string>(octopus, ""));
    length.insert(pair<vector<int>, int>(octopus, 0));

    bool flag(false);
    
    while (!q.empty()){
        vector<int> current = q.front();
        q.pop();
        //If this is key position
        if (current == key){
            flag = true;
            break;
        }
        
        //searching all possible variantes
        vector <vector <int> > neighbors;
        Positions(current, neighbors);
        
        for (int i = 0; i < neighbors.size(); i++){
            //Сохраняем последний символ - движение, которое мы совершили
            int m = neighbors[i][9];
            neighbors[i].pop_back();
            vector<int> temp = neighbors[i];
            
            //If this is new position
            if (!used.count(temp)){
                used.insert(temp);
                q.push(temp);
                //обновление пути и длины для этого положения
                int dist = length[current] + 1;
                length.insert(pair<vector<int>, int>(temp, dist));
                string path = way[current] + Symbol(m);
                way.insert(pair<vector<int>, string>(temp, path));
            }
        }
    }
    
    
    if (!flag){
        cout << "-1";
    } else {
        cout << length[key] << endl;
        cout << way[key] << endl;
    }
}

int main() {
    
    Graph g;
    g.BFS();

    return 0;
}
