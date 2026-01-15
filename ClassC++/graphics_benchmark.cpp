#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <random>
#include <chrono>

using namespace std;

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int NUM_CIRCLES = 1000;
const float CIRCLE_RADIUS = 5.0f;
const float MAX_SPEED = 200.0f;

struct Circle {
    sf::CircleShape shape;
    sf::Vector2f velocity;
};

int main() {
    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(WINDOW_WIDTH, WINDOW_HEIGHT)), "Graphics Benchmarker");

    // Center the window
    sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
    window.setPosition(sf::Vector2i(
        (desktop.size.x - WINDOW_WIDTH) / 2,
        (desktop.size.y - WINDOW_HEIGHT) / 2
    ));

    // Disable V-Sync for benchmarking
    window.setVerticalSyncEnabled(false);

    // Random number generator
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<float> posX(0, WINDOW_WIDTH - 2 * CIRCLE_RADIUS);
    uniform_real_distribution<float> posY(0, WINDOW_HEIGHT - 2 * CIRCLE_RADIUS);
    uniform_real_distribution<float> vel(-MAX_SPEED, MAX_SPEED);

    // Create circles
    vector<Circle> circles;
    for (int i = 0; i < NUM_CIRCLES; ++i) {
        Circle c;
        c.shape.setRadius(CIRCLE_RADIUS);
        c.shape.setFillColor(sf::Color::White);
        c.shape.setPosition(sf::Vector2f(posX(gen), posY(gen)));
        c.velocity = sf::Vector2f(vel(gen), vel(gen));
        circles.push_back(c);
    }

    // Font for FPS display
    sf::Font font;
    if (!font.openFromFile("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf")) {
        // Fallback
    }
    sf::Text fpsText(font, "FPS: 0", 20);
    fpsText.setFillColor(sf::Color::White);
    fpsText.setPosition(sf::Vector2f(10, 10));

    // FPS calculation
    sf::Clock clock;
    int frameCount = 0;
    float fps = 0.0f;

    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        frameCount++;

        // Calculate FPS every second
        static float timeAccumulator = 0.0f;
        timeAccumulator += deltaTime.asSeconds();
        if (timeAccumulator >= 1.0f) {
            fps = frameCount / timeAccumulator;
            frameCount = 0;
            timeAccumulator = 0.0f;
            fpsText.setString("FPS: " + to_string(static_cast<int>(fps)));
        }

        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }
            if (event->is<sf::Event::KeyPressed>() && event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape) {
                window.close();
            }
        }

        // Update circles
        for (auto& c : circles) {
            c.shape.move(c.velocity * deltaTime.asSeconds());

            // Bounce off walls
            sf::Vector2f pos = c.shape.getPosition();
            if (pos.x <= 0 || pos.x >= WINDOW_WIDTH - 2 * CIRCLE_RADIUS) {
                c.velocity.x = -c.velocity.x;
                pos.x = max(0.0f, min(pos.x, WINDOW_WIDTH - 2 * CIRCLE_RADIUS));
                c.shape.setPosition(pos);
            }
            if (pos.y <= 0 || pos.y >= WINDOW_HEIGHT - 2 * CIRCLE_RADIUS) {
                c.velocity.y = -c.velocity.y;
                pos.y = max(0.0f, min(pos.y, WINDOW_HEIGHT - 2 * CIRCLE_RADIUS));
                c.shape.setPosition(pos);
            }
        }

        // Draw
        window.clear(sf::Color::Black);
        for (const auto& c : circles) {
            window.draw(c.shape);
        }
        window.draw(fpsText);
        window.display();
    }

    cout << "Benchmark completed. Average FPS: " << fps << endl;
    return 0;
}