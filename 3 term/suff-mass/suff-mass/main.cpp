#include <iostream>
#include <vector>

using std::vector;

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
    
    // определяем сумму для точек
    Point operator+(Point &p2) {
        return {this->x + p2.x, this->y + p2.y};
    }
};

vector<Point> read_polyhedron(size_t n, short  k) {
    vector<Point> Q;
    
    return
}

vector<Point> find_Minkovsky_sum(vector<Point> &V, vector<Point> &W, size_t n, size_t m) {
    
}

int main() {
    size_t n = 0, m = 0;
    std::cin >> n;
    
    vector<Point> V = read_polyhedron(n , -1);
    
    return 0;
}
