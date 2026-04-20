#include "polygon.hpp"

Polygon::Polygon() : color(sf::Color::White), numVertices(0), vertices(nullptr) {}

Polygon::~Polygon() {
    delete[] vertices;
}

void Polygon::setColor(const sf::Color color) {
    this->color = color;
}

void Polygon::setCoordinate(int idx, Coordinate coord) {
    if (idx >= 0 && idx < numVertices) {
        vertices[idx] = coord;
    }
}

void Polygon::draw(sf::RenderTarget& window) {
    sf::ConvexShape shape;
    shape.setPointCount(numVertices);
    for (int i = 0; i < numVertices; ++i) {
        shape.setPoint(i, sf::Vector2f(static_cast<float>(vertices[i].x),
                                       static_cast<float>(vertices[i].y)));
    }
    shape.setFillColor(color);
    window.draw(shape);
}
