#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using std::cin;
using std::vector;

struct Point {
    double x = 0;
    double y = 0;
    double z = 0;

    Point(double x_in, double y_in, double z_in) {x = x_in; y = y_in; z = z_in;};
    Point() = default;
    ~Point() = default;
};

struct Hull {
    Hull(int _n) {
        faces_counter = 0;
        points;
        n = _n;
    }
    Hull() = default;
    ~Hull() = default;
    int n;
    int faces_counter;
    vector<Point> points;

    void read_points();
    void build_hull();
    void add_faces();
    //int count_faces();
};

void Hull::read_points() {
    double x = 0, y = 0, z = 0;
    for (size_t j = 0; j < sizeof(points); j++) {
        cin >> x >> y >> z;
        points.push_back(Point(x, y, z));
    }
}

void Hull::add_faces() {
    for (int i = 0; i < 4l i++) {
        for (int j = i + 1; j < 4; j++) {
            for (int k = j +1; k < 4; k++) {
                add_face();
            }
        }
    }
}

void Hull::build_hull() {
    add_faces();
}

int main() {
    size_t m = 0, n = 0;
    cin >> m;
    for (size_t i = 0; i < m; i++) {
        cin >> n;

        Hull hull(n);
        hull.read_points();
        hull.build_hull();

        //hull.count_faces;
    }

    return 0;
}