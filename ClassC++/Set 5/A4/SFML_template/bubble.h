#ifndef BUBBLE_H
#define BUBBLE_H

#include <SFML/Graphics.hpp>

class Bubble {
private:
    sf::CircleShape m_shape;
    float m_xDir;
    float m_yDir;

public:
    Bubble();
    Bubble(float radius, float x, float y, float xd, float yd, const sf::Color& color);

    void draw(sf::RenderWindow& window) const;
    void updatePosition(float windowWidth, float windowHeight);
    bool checkClicked(float mouseX, float mouseY) const;
};

#endif