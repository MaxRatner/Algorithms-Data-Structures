/*
 Дано число N и последовательность из N целых чисел. Найти вторую порядковую статистику на заданных диапазонах.
 Для решения задачи используйте структуру данных Sparse Table. Требуемое время обработки каждого диапазона O(1). Время подготовки структуры данных O(nlogn)
 
 */
#include <iostream>
#include <vector>
#include <math.h>
#include <algorithm>

using namespace std;

class SparseTable {
public:
    void CreateTable();
    void RMQ();
    pair<int, int> min_pair(pair<int, int>, pair<int, int>);
private:
    int n, m;
    vector<int> sequence;
    vector<vector<pair<int, int> > > ST;
};

pair<int, int> SparseTable::min_pair(pair<int, int> pair1, pair<int, int> pair2) {
    vector<int> temp;
    temp.push_back(sequence[pair1.first]);
    temp.push_back(sequence[pair1.second]);
    
    if (pair2.second != pair1.first && pair2.second != pair1.second) {
        temp.push_back(sequence[pair2.second]);
    }
    if (pair2.first != pair1.first && pair2.first != pair1.second) {
        temp.push_back(sequence[pair2.first]);
    }
    
    sort(temp.begin(), temp.end());
    
    pair<int, int> min;
    if (temp[0] == sequence[pair1.first]) {
        min.first = pair1.first;
        
        if (temp[1] == sequence[pair1.second]) {
            min.second = pair1.second;
        } else {
            if (pair2.first != pair1.first && temp[1] == sequence[pair2.first]) {
                min.second = pair2.first;
            } else {
                min.second = pair2.second;
            }
        }
    }
    
    if (temp[0] == sequence[pair2.first]) {
        min.first = pair2.first;
        if (temp[1] == sequence[pair2.second]) {
            min.second = pair2.second;
        } else {
            if (temp[1] == sequence[pair1.first] && pair1.first != pair2.first) {
                min.second = pair1.first;
            } else {
                min.second = pair1.second;
            }
        }
    }
    
    return min;
}

void SparseTable::CreateTable() {
    cin >> n >> m;
    sequence = vector<int>(n);
    for (int i = 0; i < n; i++) {
        cin >> sequence[i];
    }
    
    ST = vector<vector<pair<int, int> > >(int(log2(n)) + 1, vector<pair<int, int> >(n, make_pair(-1, -1)));
    
    for (int i = 0; i < n - 1; i++) {
        if (sequence[i] < sequence[i + 1]) {
            ST[1][i] = make_pair(i, i + 1);
        } else {
            ST[1][i] = make_pair(i + 1, i);
        }
    }
    
    for (int i = 2; i < int(log2(n)) + 1; i++) {
        for (int j = 0; j < n; j++) {
            if (pow(2, i - 1) < n - j) {
                ST[i][j] = min_pair(ST[i - 1][j], ST[i - 1][j + pow(2, i - 1)]);
            }
        }
    }
}

void SparseTable::RMQ() {
    vector<pair<int, int> > ranges(m, pair<int, int>(make_pair(0, 0)));
    
    for ( int i = 0; i < m; i++) {
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        int len = r - l + 1;
        int k = int(log2(len));
        cout << sequence[min_pair(ST[k][l], ST[k][r - pow(2, k) + 1]).second] << endl;
    }
}

int main() {
    SparseTable table;
    table.CreateTable();
    table.RMQ();
    
    return 0;
}
