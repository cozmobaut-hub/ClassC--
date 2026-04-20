#include "isoscelestriangle.hpp"
#include <cmath>

static double dist_iso(const Coordinate& a, const Coordinate& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

static bool eq_iso(double a, double b) {
    return std::fabs(a - b) < 1e-6;
}

static bool tri_iso(double a, double b, double c) {
    return a > 0.0 && b > 0.0 && c > 0.0 &&
           a + b > c && a + c > b && b + c > a;
}

bool IsoscelesTriangle::validate() {
    double a = dist_iso(vertices[0], vertices[1]);
    double b = dist_iso(vertices[1], vertices[2]);
    double c = dist_iso(vertices[2], vertices[0]);

    return tri_iso(a, b, c) &&
           (eq_iso(a, b) || eq_iso(b, c) || eq_iso(a, c));
}
