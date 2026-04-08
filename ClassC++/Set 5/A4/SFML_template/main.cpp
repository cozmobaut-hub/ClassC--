#include <SFML/Graphics.hpp>
#include <vector>
#include <random>
#include <algorithm>
#include <cmath>
#include "Bubble.h"

static std::mt19937 gen(std::random_device{}());

float randFloat(float minVal, float maxVal) {
    std::uniform_real_distribution<float> dist(minVal, maxVal);
    return dist(gen);
}

int randInt(int minVal, int maxVal) {
    std::uniform_int_distribution<int> dist(minVal, maxVal);
    return dist(gen);
}

sf::Color randColor() {
    return sf::Color(
        static_cast<sf::Uint8>(randInt(0, 255)),
        static_cast<sf::Uint8>(randInt(0, 255)),
        static_cast<sf::Uint8>(randInt(0, 255))
    );
}

Bubble makeRandomBubble(float windowWidth, float windowHeight) {
    float radius = randFloat(10.f, 50.f);
    float x = randFloat(radius, windowWidth - radius);
    float y = randFloat(radius, windowHeight - radius);

    float xd = 0.f;
    float yd = 0.f;
    while (xd == 0.f) {
        xd = randFloat(-0.8f, 0.8f);
    }
    while (yd == 0.f) {
        yd = randFloat(-0.8f, 0.8f);
    }

    return Bubble(radius, x, y, xd, yd, randColor());
}

int main() {
    sf::Vector2u windowSize(640, 640);
    sf::RenderWindow window(sf::VideoMode(windowSize.x, windowSize.y), "SFML Test");

    const float winW = static_cast<float>(windowSize.x);
    const float winH = static_cast<float>(windowSize.y);

    std::vector<Bubble> bubbles;
    for (int i = 0; i < 5; ++i) {
        bubbles.push_back(makeRandomBubble(winW, winH));
    }

    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q ||
                    event.key.code == sf::Keyboard::Escape) {
                    window.close();
                }
                else if (event.key.code == sf::Keyboard::Space) {
                    if (bubbles.size() < 10) {
                        bubbles.push_back(makeRandomBubble(winW, winH));
                    }
                }
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    float mx = static_cast<float>(event.mouseButton.x);
                    float my = static_cast<float>(event.mouseButton.y);

                    bubbles.erase(
                        std::remove_if(bubbles.begin(), bubbles.end(),
                            [mx, my](const Bubble& b) {
                                return b.checkClicked(mx, my);
                            }),
                        bubbles.end()
                    );
                }
            }
        }

        if (clock.getElapsedTime().asSeconds() >= 1.f / 60.f) {
            for (std::vector<Bubble>::iterator it = bubbles.begin(); it != bubbles.end(); ++it) {
                it->updatePosition(winW, winH);
            }
            clock.restart();
        }

        window.clear();

        for (std::vector<Bubble>::const_iterator it = bubbles.begin(); it != bubbles.end(); ++it) {
            it->draw(window);
        }

        window.display();
    }

    return 0;
}