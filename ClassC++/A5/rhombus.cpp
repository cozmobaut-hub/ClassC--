#include "rhombus.hpp"
#include <cmath>

static double dist(const Coordinate& a, const Coordinate& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    return std::sqrt(dx * dx + dy * dy);
}

static bool eq(double a, double b) {
    return std::fabs(a - b) < 1e-6;
}

static bool tri(double a, double b, double c) {
    return a > 0 && b > 0 && c > 0 && a + b > c && a + c > b && b + c > a;
}

bool Rhombus::validate() {
    double a = dist(vertices[0], vertices[1]);
    double b = dist(vertices[1], vertices[2]);
    double c = dist(vertices[2], vertices[3]);
    double d = dist(vertices[3], vertices[0]);

    if (!(a > 0 && b > 0 && c > 0 && d > 0)) return false;
    if (!(eq(a, b) && eq(b, c) && eq(c, d))) return false;

    double t1a = dist(vertices[0], vertices[1]);
    double t1b = dist(vertices[1], vertices[2]);
    double t1c = dist(vertices[2], vertices[0]);

    double t2a = dist(vertices[0], vertices[2]);
    double t2b = dist(vertices[2], vertices[3]);
    double t2c = dist(vertices[3], vertices[0]);

    return tri(t1a, t1b, t1c) && tri(t2a, t2b, t2c);
}
