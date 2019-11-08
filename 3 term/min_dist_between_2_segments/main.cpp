#include <iostream>
#include <iomanip>
#include <cmath>
const double Eps = 1e-11;

struct Point {
    double x = 0;
    double y = 0;
    double z = 0;

    Point(double x_in, double y_in, double z_in) {x = x_in; y = y_in; z = z_in;};
    Point() = default;
    ~Point() = default;
};

struct Segment {
    double x = 0;
    double y = 0;
    double z = 0;

    Segment(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}

    Segment(const Point& start, const Point& finish) {
        x = finish.x - start.x;
        y = finish.y - start.y;
        z = finish.z - start.z;
    }
    Segment() = default;
    ~Segment() = default;

    double Dot(Segment v) {
        return (x * (v).x + y * (v).y + z * (v).z);
    }
    double Norm() {
        return this->Dot(*this);  // norm = length of vector
    }
    //
    double D_func(Segment& v) {
        Segment u = *this;
        return u.Norm() * v.Norm() - u.Dot(v) * u.Dot(v);
    }

    Segment operator+( const Segment& other ) {
        return {this->x + other.x, this->y + other.y, this->z + other.z};
    }

    // определнеи умножения между сегментом и скаляром
    Segment operator*( double c ) {
        return {this->x * c, this->y * c, this->z * c};
    }
};

void line_to_line(Segment& u, Segment& v, Segment& w, double& sc, double& tc, double& sN, double& sD, double& tN, double& tD) {
    double D = sD; // >= 0
    sD = D; // sc = sN / sD, default sD = D >= 0
    tD = D;

    if (D <= 0.0 + Eps) {
        sN = 0.0;         // force using point P0 on segment S1
        sD = 1.0;         // to prevent possible division by 0.0 later
        tN = v.Dot(w);
        tD = v.Dot(v);
    } else {                 // get the closest points on the infinite lines
        sN = (u.Dot(v) * v.Dot(w) - v.Dot(v) * u.Dot(w));
        tN = (u.Dot(u) * v.Dot(w) - u.Dot(v) * u.Dot(w));
        if (sN <= 0.0) {        // sc < 0 => the s=0 edge is visible
            sN = 0.0;
            tN = v.Dot(w);
            tD = v.Dot(v);
        }
        else if (sN >= sD) {  // sc > 1  => the s=1 edge is visible
            sN = sD;
            tN = v.Dot(w) + u.Dot(v);
            tD = v.Dot(v);
        }
    }
}

double min_dist_between_2_segments(Segment& u, Segment& v, Segment& w) {
    double sc, tc = 0.0;
    double sN, sD = u.D_func(v); // sc = sN / sD, default sD = D >= 0
    double tN, tD = sD;

    //сначала находим минимальное расстояние между прямыми
    line_to_line(u, v, w, sc, tc, sN, sD, tN, tD);

    if (tN <= 0.0) {            // tc < 0 => the t=0 edge is visible
        tN = 0.0;
        // recompute sc for this edge
        if (-u.Dot(w) <= 0.0)
            sN = 0.0;
        else if (-u.Dot(w) >= u.Dot(u))
            sN = sD;
        else {
            sN = -u.Dot(w);
            sD = u.Dot(u);
        }
    }
    else if (tN >= tD) {      // tc > 1  => the t=1 edge is visible
        tN = tD;
        // recompute sc for this edge
        if ((-u.Dot(w) + u.Dot(v)) <= 0.0)
            sN = 0;
        else if ((-u.Dot(w) + u.Dot(v)) >= u.Dot(u))
            sN = sD;
        else {
            sN = (-u.Dot(w) + u.Dot(v));
            sD = u.Dot(u);
        }
    }

    sc = (abs(sN) < Eps ? 0.0 : sN / sD);
    tc = (abs(tN) < Eps ? 0.0 : tN / tD);

    Segment dP = w + (u * sc) + (v * tc * (-1));  // =  S1(sc) - S2(tc)
    return sqrt(dP.Norm());   // return the closest distance
}

int main() {
    // читаем точки
    Point a, b, c, d;
    std::cin >> a.x >> a.y >> a.z;
    std::cin >> b.x >> b.y >> b.z;
    std::cin >> c.x >> c.y >> c.z;
    std::cin >> d.x >> d.y >> d.z;
    // инициализируем отрезки
    Segment seg1(a, b);
    Segment seg2(c, d);
    Segment seg3(c, a);

    //количество значений после запятой
    std::cout << std::fixed << std::setprecision(8);

    // само расстояние
    std::cout << min_dist_between_2_segments(seg1, seg2, seg3);

    return 0;
}