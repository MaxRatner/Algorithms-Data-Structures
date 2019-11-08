#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

#define _USE_MATH_DEFINES
//#define M_PI
using std::vector;
using std::cin;
using std::cout;

struct Point {
    double x = 0, y = 0;

    Point(double _x, double _y) {x = _x; y = _y;}
    Point() = default;
    ~Point() = default;

    // определяем порядок обхода точек (против часовой стрелки)
    bool operator<(Point &p2) {
        if (this->y < p2.y || (this->y == p2.y && this->x < p2.x)) {
            return true;
        } else  {
            return false;
        }
    }

    void read_point(int k) {
        cin >> x >> y;
        x = x * k;
        y = y * k;
    }
    // определяем сумму для точек
    Point operator+(Point &p2) {
        return {this->x + p2.x, this->y + p2.y};
    }
};

vector<Point> read_polyhedron(size_t len, int  k) {
    vector<Point> Q;
    Point t;
    for (size_t i = 0; i < len; i++) {
        t.read_point(k);
        Q.push_back(t);
    }
    reverse(Q.begin(), Q.end());
    return Q;
}

size_t find_min_p(vector<Point> &Q, size_t len) {
    size_t q_min_p = 0;
    Point Q_min = Q[0];
    for (size_t k = 1; k < len; k++) {
        if (Q[k] < Q_min) {
            Q_min = Q[k];
            q_min_p = k;
        }
    }
    return q_min_p;
}

double angle(Point &a, Point &b) {
    double t = atan2((b.y - a.y), (b.x - a.x));
    if (t >= 0) {
        return t;
    } else {
        return t + 2 * M_PI;
    }
}

// можно заменить v на _v
vector<Point> Minkovsky_sum(vector<Point> &V, vector<Point> &W, size_t n, size_t m) {
    // находим индекс самой левой точки в каждом многограннике
    size_t v_min_p = find_min_p(V, n);
    size_t w_min_p = find_min_p(W, m);
    rotate(V.begin(), V.begin() + v_min_p, V.end());
    rotate(W.begin(), W.begin() + w_min_p, W.end());

    int i = 0, j = 0;
    vector<Point> res;
    V.push_back(V[0]);
    V.push_back(V[1]);
    W.push_back(W[0]);
    W.push_back(W[1]);

    while (i <= n && j <= m) {
        Point t = V[i] + W[j];
        res.push_back(t);
        if (angle(V[i], V[i + 1]) < angle(W[j], W[j + 1])) {
            i++;
        } else if (angle(V[i], V[i + 1]) > angle(W[j], W[j + 1])) {
            j++;
        } else {
            i++;
            j++;
        }
    }
    return res;
}

bool Check_center(vector<Point> &Q){
    Q.push_back(Q[0]);
    Q.push_back(Q[1]);

    for (int i = 0; i < Q.size() - 2; i++) {
        double product = Q[i].x * Q[i + 1].y - Q[i + 1].x * Q[i].y;
        if (product < 0) {
            return false;
        } else if (product == 0) {
            if (Q[i].x == Q[i + 1].x && Q[i].y == Q[i + 1].y) {
                continue;
            }
            return ((Q[i].y * Q[i + 1].y < 0) ||
                    (Q[i].y == 0 && Q[i + 1].y == 0 && Q[i].x * Q[i + 1].x <= 0));
        }
    }
    return true;
}

int main() {
    size_t n = 0, m = 0;
    cin >> n;
    vector<Point> V = read_polyhedron(n , -1);

    cin >> m;
    vector<Point> W = read_polyhedron(m , 1);

    vector<Point> Q = Minkovsky_sum(V, W, n, m);

    if (Check_center(Q)) {
        cout << "YES";
    } else {
        cout << "NO";
    }

    return 0;
}
