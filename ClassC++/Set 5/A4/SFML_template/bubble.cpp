#include "Bubble.h"
#include <cmath>

Bubble::Bubble()
: m_shape(), m_xDir(0.f), m_yDir(0.f) {
    m_shape.setRadius(20.f);
    m_shape.setOrigin(20.f, 20.f);
    m_shape.setPosition(100.f, 100.f);
    m_shape.setFillColor(sf::Color::White);
}

Bubble::Bubble(float radius, float x, float y, float xd, float yd, const sf::Color& color)
: m_shape(), m_xDir(xd), m_yDir(yd) {
    m_shape.setRadius(radius);
    m_shape.setOrigin(radius, radius);
    m_shape.setPosition(x, y);
    m_shape.setFillColor(color);
}

void Bubble::draw(sf::RenderWindow& window) const {
    window.draw(m_shape);
}

void Bubble::updatePosition(float windowWidth, float windowHeight) {
    m_shape.move(m_xDir, m_yDir);

    sf::FloatRect bounds = m_shape.getGlobalBounds();
    float left   = bounds.left;
    float top    = bounds.top;
    float right  = bounds.left + bounds.width;
    float bottom = bounds.top  + bounds.height;

    if (right > windowWidth) {
        m_shape.move(windowWidth - right, 0.f);
        m_xDir = -m_xDir;
    }
    if (bottom > windowHeight) {
        m_shape.move(0.f, windowHeight - bottom);
        m_yDir = -m_yDir;
    }
    if (left < 0.f) {
        m_shape.move(-left, 0.f);
        m_xDir = -m_xDir;
    }
    if (top < 0.f) {
        m_shape.move(0.f, -top);
        m_yDir = -m_yDir;
    }
}

bool Bubble::checkClicked(float mouseX, float mouseY) const {
    sf::Vector2f center = m_shape.getPosition();
    float radius = m_shape.getRadius();
    float dx = mouseX - center.x;
    float dy = mouseY - center.y;
    return dx * dx + dy * dy <= radius * radius;
}