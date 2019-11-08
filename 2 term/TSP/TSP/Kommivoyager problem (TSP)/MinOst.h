#include <iostream>
#include <vector>
#include <set>
#include <math.h>
#include <time.h>
#include <algorithm>
#include <cmath>

using namespace std;

const int N = 100000000;

class Graph{
public:
    void Prim();
    void Coordinates(int n_dots);
    
    double Sort();
    int ReturnLength(vector<int> permutation);
    
    double FindRound();
    void DFS(int v, vector<bool> &visited);
    
private:
    int n;
    vector<vector<int> > g;
    
    vector<vector<int> > ostov;
    vector<int> round;
};
