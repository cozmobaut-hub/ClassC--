#include "equilateraltriangle.hpp"
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

bool EquilateralTriangle::validate() {
    double a = dist(vertices[0], vertices[1]);
    double b = dist(vertices[1], vertices[2]);
    double c = dist(vertices[2], vertices[0]);

    return tri(a, b, c) && eq(a, b) && eq(b, c);
}
