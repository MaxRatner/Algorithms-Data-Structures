/*
 У художника-авангардиста есть полоска разноцветного холста.
 За один раз он перекрашивает некоторый отрезок полоски в некоторый цвет.
 После каждого перекрашивания специально обученный фотограф делает снимок части получившегося творения для музея современного искусства.
 Для правильного экспонирования требуется знать яркость самого темного цвета на выбранном фотографом отрезке. Напишите программу для определения яркости самого темного цвета на отрезке.
 Требуемая скорость определения яркости — O(log N).
 Цвет задается тремя числами R, G и B (0 ≤ R, G, B ≤ 255), его яркость = R + G + B.
*/

#include <iostream>
#include <vector>

using namespace std;

const int N = 10000000;

class SegmentTree {
public:
    void Build(int, int, int);
    void CountBright();
    int FindMin(int v, int tl, int tr, int l, int r);
    void Update(int v, int tl, int tr, int l, int r, int new_val);
    
    void push(int, int, int);
private:
    vector<int> tree;
    vector<int> tAdd;
    vector<int> sequence;
    int n;
};

void SegmentTree::Build(int v, int l, int r) {
    if (l == r) {
        tree[v] = sequence[l];
    }
    else {
        int m = (l + r) / 2;
        Build(v * 2 + 1, l, m);
        Build(v * 2 + 2, m + 1, r);
        tree[v] = min(tree[v * 2 + 1], tree[v * 2 + 2]);
    }
}

// Ищет для заданных l и r минимальную ячейку
// Для запроса суммы представляет из себя также рекурсивную функцию, которой таким же образом передаётся информация о текущей вершине дерева (т.е. числа v, tl, tr, которым в основной программе следует передавать значения 1, 0, n-1 соответственно), а помимо этого — также границы l и r текущего запроса.
int SegmentTree::FindMin(int v, int tl, int tr, int l, int r) {
    push(v, tl, tr);
    
    if (tl > r || tr < l) {
        return N;
    }
    
    if (l <= tl && tr <= r) {
        return tree[v];
    }

    int tm = tl + (tr - tl) / 2;
    int child_1 = FindMin(v * 2 + 1, tl, tm, l, r);
    int child_2 = FindMin(v * 2 + 2, tm + 1, tr, l, r);
    return min(child_1, child_2);
}

//Запрос модификации. Ему точно так же передаётся информация о текущей вершине дерева отрезков, а дополнительно указывается индекс меняющегося элемента, а также его новое значение.
/*void SegmentTree::Update(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr) {
        tree[v] = new_val;
        return;
    }
    
    int tm = tl + (tr - tl) / 2;
    if (pos <= tm) {
        Update(v * 2 + 1, tl, tm, pos, new_val);
    } else {
        Update(v * 2 + 2, tm + 1, tr, pos, new_val);
    }
    tree[v] = min(tree[v * 2 + 1], tree[v * 2 + 2]);
}*/

void SegmentTree::Update(int v, int tl, int tr, int l, int r, int new_val) {
    push(v, tl, tr);
    if (r < tl || tr < l) {
        return;
    }
    if (l <= tl && tr <= r) {
        tAdd[v] = new_val;
        push(v, tl, tr);
        return;
    }
    int tm = tl + (tr - tl) / 2;
    Update(v * 2 + 1, tl, tm, l, r, new_val);
    Update(v * 2 + 2, tm + 1, tr, l, r, new_val);
    
    tree[v] = min(tree[v * 2 + 1], tree[v * 2 + 2]);
}

void SegmentTree::push(int v, int tl, int tr) {
    if (tAdd[v] != N) {
        tree[v] = tAdd[v];
        if (tl != tr) {
            tAdd[v * 2 + 1] = tAdd[v];
            tAdd[v * 2 + 2] = tAdd[v];
        }
        tAdd[v] = N;
    }
}


void SegmentTree::CountBright() {
    cin >> n;
    tree = vector<int>(4 * n, N);
    tAdd = vector<int>(4 * n, N);
    sequence = vector<int>(n);
    for (int i = 0; i < n; i++) {
        int r, g, b;
        cin >> r >> g >> b;
        sequence[i] = r + g + b;
    }
    //OK
    
    Build(0, 0, n - 1);
    
    //Здесь мы уже собрали дерево отрезков с минимумами
    
    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        int c, d, r, g, b, e, f;
        cin >> c >> d >> r >> g >> b >> e >> f;
        int a = r + g + b;
        //Окрашиваем отрезок
        
        Update(0, 0, n - 1, c, d, a);
        
        int k = FindMin(0, 0, n - 1, e, f);
        //Считаем минимальную яркость
        cout << k << ' ';
    }
    
}

int main() {
    SegmentTree t;
    t.CountBright();
}
