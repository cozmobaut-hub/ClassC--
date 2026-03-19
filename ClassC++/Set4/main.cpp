/*
CSCI 200 - Spring 2026
Lab 4C - SFML: Bob Ross
Your Name
Your Mines Username
*/

#include <SFML/Graphics.hpp>
using namespace std;

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Crates");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color(60, 60, 60)); // dark background

        // Common crate size
        float crateWidth = 90.f;
        float crateHeight = 90.f;
        float baseY = 420.f;

        // Helper lambda would be nice, but lab rules say no fancy stuff,
        // so we just repeat shapes with slight variations.

        // =========================
        // CRATE 1
        // =========================
        float x1 = 40.f;

        // Outer box
        sf::RectangleShape crate1Outer;
        crate1Outer.setSize(sf::Vector2f(crateWidth, crateHeight));
        crate1Outer.setPosition(sf::Vector2f(x1, baseY));
        crate1Outer.setFillColor(sf::Color(139, 69, 19)); // wood fill
        crate1Outer.setOutlineThickness(4.f);
        crate1Outer.setOutlineColor(sf::Color(80, 40, 10));
        window.draw(crate1Outer);

        // Vertical plank
        sf::RectangleShape crate1PlankVertical;
        crate1PlankVertical.setSize(sf::Vector2f(10.f, crateHeight - 10.f));
        crate1PlankVertical.setPosition(sf::Vector2f(x1 + 20.f, baseY + 5.f));
        crate1PlankVertical.setFillColor(sf::Color(160, 82, 45));
        window.draw(crate1PlankVertical);

        // Horizontal plank
        sf::RectangleShape crate1PlankHorizontal;
        crate1PlankHorizontal.setSize(sf::Vector2f(crateWidth - 10.f, 10.f));
        crate1PlankHorizontal.setPosition(sf::Vector2f(x1 + 5.f, baseY + 35.f));
        crate1PlankHorizontal.setFillColor(sf::Color(160, 82, 45));
        window.draw(crate1PlankHorizontal);

        // Diagonal plank (top-left to bottom-right)
        sf::RectangleShape crate1Diag1;
        crate1Diag1.setSize(sf::Vector2f(crateWidth * 1.4f, 8.f));
        crate1Diag1.setPosition(sf::Vector2f(x1 - 10.f, baseY + crateHeight - 10.f));
        crate1Diag1.setFillColor(sf::Color(110, 55, 25));
        crate1Diag1.setRotation(-45.f);
        window.draw(crate1Diag1);

        // Diagonal plank (bottom-left to top-right)
        sf::RectangleShape crate1Diag2;
        crate1Diag2.setSize(sf::Vector2f(crateWidth * 1.4f, 8.f));
        crate1Diag2.setPosition(sf::Vector2f(x1 - 5.f, baseY + 10.f));
        crate1Diag2.setFillColor(sf::Color(110, 55, 25));
        crate1Diag2.setRotation(45.f);
        window.draw(crate1Diag2);

        // =========================
        // CRATE 2
        // =========================
        float x2 = 170.f;

        sf::RectangleShape crate2Outer;
        crate2Outer.setSize(sf::Vector2f(crateWidth, crateHeight));
        crate2Outer.setPosition(sf::Vector2f(x2, baseY));
        crate2Outer.setFillColor(sf::Color(139, 69, 19));
        crate2Outer.setOutlineThickness(4.f);
        crate2Outer.setOutlineColor(sf::Color(80, 40, 10));
        window.draw(crate2Outer);

        sf::RectangleShape crate2PlankVertical;
        crate2PlankVertical.setSize(sf::Vector2f(12.f, crateHeight - 12.f));
        crate2PlankVertical.setPosition(sf::Vector2f(x2 + 35.f, baseY + 6.f));
        crate2PlankVertical.setFillColor(sf::Color(160, 82, 45));
        window.draw(crate2PlankVertical);

        sf::RectangleShape crate2PlankHorizontal;
        crate2PlankHorizontal.setSize(sf::Vector2f(crateWidth - 12.f, 12.f));
        crate2PlankHorizontal.setPosition(sf::Vector2f(x2 + 6.f, baseY + 50.f));
        crate2PlankHorizontal.setFillColor(sf::Color(160, 82, 45));
        window.draw(crate2PlankHorizontal);

        sf::RectangleShape crate2Diag1;
        crate2Diag1.setSize(sf::Vector2f(crateWidth * 1.3f, 7.f));
        crate2Diag1.setPosition(sf::Vector2f(x2 - 5.f, baseY + crateHeight - 12.f));
        crate2Diag1.setFillColor(sf::Color(110, 55, 25));
        crate2Diag1.setRotation(-45.f);
        window.draw(crate2Diag1);

        sf::RectangleShape crate2Diag2;
        crate2Diag2.setSize(sf::Vector2f(crateWidth * 1.3f, 7.f));
        crate2Diag2.setPosition(sf::Vector2f(x2 - 2.f, baseY + 12.f));
        crate2Diag2.setFillColor(sf::Color(110, 55, 25));
        crate2Diag2.setRotation(45.f);
        window.draw(crate2Diag2);

        // =========================
        // CRATE 3
        // =========================
        float x3 = 300.f;

        sf::RectangleShape crate3Outer;
        crate3Outer.setSize(sf::Vector2f(crateWidth, crateHeight));
        crate3Outer.setPosition(sf::Vector2f(x3, baseY));
        crate3Outer.setFillColor(sf::Color(150, 75, 30));
        crate3Outer.setOutlineThickness(4.f);
        crate3Outer.setOutlineColor(sf::Color(90, 45, 15));
        window.draw(crate3Outer);

        sf::RectangleShape crate3PlankVertical;
        crate3PlankVertical.setSize(sf::Vector2f(10.f, crateHeight - 8.f));
        crate3PlankVertical.setPosition(sf::Vector2f(x3 + 25.f, baseY + 4.f));
        crate3PlankVertical.setFillColor(sf::Color(175, 95, 45));
        window.draw(crate3PlankVertical);

        sf::RectangleShape crate3PlankVertical2;
        crate3PlankVertical2.setSize(sf::Vector2f(10.f, crateHeight - 8.f));
        crate3PlankVertical2.setPosition(sf::Vector2f(x3 + 55.f, baseY + 4.f));
        crate3PlankVertical2.setFillColor(sf::Color(175, 95, 45));
        window.draw(crate3PlankVertical2);

        sf::RectangleShape crate3PlankHorizontal;
        crate3PlankHorizontal.setSize(sf::Vector2f(crateWidth - 10.f, 8.f));
        crate3PlankHorizontal.setPosition(sf::Vector2f(x3 + 5.f, baseY + 60.f));
        crate3PlankHorizontal.setFillColor(sf::Color(160, 82, 45));
        window.draw(crate3PlankHorizontal);

        sf::RectangleShape crate3Diag1;
        crate3Diag1.setSize(sf::Vector2f(crateWidth * 1.3f, 6.f));
        crate3Diag1.setPosition(sf::Vector2f(x3 - 6.f, baseY + crateHeight - 10.f));
        crate3Diag1.setFillColor(sf::Color(110, 55, 25));
        crate3Diag1.setRotation(-45.f);
        window.draw(crate3Diag1);

        sf::RectangleShape crate3Diag2;
        crate3Diag2.setSize(sf::Vector2f(crateWidth * 1.3f, 6.f));
        crate3Diag2.setPosition(sf::Vector2f(x3 - 2.f, baseY + 10.f));
        crate3Diag2.setFillColor(sf::Color(110, 55, 25));
        crate3Diag2.setRotation(45.f);
        window.draw(crate3Diag2);

        // =========================
        // CRATE 4
        // =========================
        float x4 = 430.f;

        sf::RectangleShape crate4Outer;
        crate4Outer.setSize(sf::Vector2f(crateWidth, crateHeight));
        crate4Outer.setPosition(sf::Vector2f(x4, baseY));
        crate4Outer.setFillColor(sf::Color(139, 69, 19));
        crate4Outer.setOutlineThickness(4.f);
        crate4Outer.setOutlineColor(sf::Color(80, 40, 10));
        window.draw(crate4Outer);

        sf::RectangleShape crate4PlankHorizontal1;
        crate4PlankHorizontal1.setSize(sf::Vector2f(crateWidth - 10.f, 8.f));
        crate4PlankHorizontal1.setPosition(sf::Vector2f(x4 + 5.f, baseY + 15.f));
        crate4PlankHorizontal1.setFillColor(sf::Color(160, 82, 45));
        window.draw(crate4PlankHorizontal1);

        sf::RectangleShape crate4PlankHorizontal2;
        crate4PlankHorizontal2.setSize(sf::Vector2f(crateWidth - 10.f, 8.f));
        crate4PlankHorizontal2.setPosition(sf::Vector2f(x4 + 5.f, baseY + 40.f));
        crate4PlankHorizontal2.setFillColor(sf::Color(160, 82, 45));
        window.draw(crate4PlankHorizontal2);

        sf::RectangleShape crate4PlankHorizontal3;
        crate4PlankHorizontal3.setSize(sf::Vector2f(crateWidth - 10.f, 8.f));
        crate4PlankHorizontal3.setPosition(sf::Vector2f(x4 + 5.f, baseY + 65.f));
        crate4PlankHorizontal3.setFillColor(sf::Color(160, 82, 45));
        window.draw(crate4PlankHorizontal3);

        sf::RectangleShape crate4Diag1;
        crate4Diag1.setSize(sf::Vector2f(crateWidth * 1.3f, 6.f));
        crate4Diag1.setPosition(sf::Vector2f(x4 - 8.f, baseY + crateHeight - 8.f));
        crate4Diag1.setFillColor(sf::Color(110, 55, 25));
        crate4Diag1.setRotation(-45.f);
        window.draw(crate4Diag1);

        sf::RectangleShape crate4Diag2;
        crate4Diag2.setSize(sf::Vector2f(crateWidth * 1.3f, 6.f));
        crate4Diag2.setPosition(sf::Vector2f(x4 - 4.f, baseY + 8.f));
        crate4Diag2.setFillColor(sf::Color(110, 55, 25));
        crate4Diag2.setRotation(45.f);
        window.draw(crate4Diag2);

        // =========================
        // CRATE 5
        // =========================
        float x5 = 560.f;

        sf::RectangleShape crate5Outer;
        crate5Outer.setSize(sf::Vector2f(crateWidth, crateHeight));
        crate5Outer.setPosition(sf::Vector2f(x5, baseY));
        crate5Outer.setFillColor(sf::Color(150, 75, 30));
        crate5Outer.setOutlineThickness(4.f);
        crate5Outer.setOutlineColor(sf::Color(90, 45, 15));
        window.draw(crate5Outer);

        sf::RectangleShape crate5PlankVertical1;
        crate5PlankVertical1.setSize(sf::Vector2f(12.f, crateHeight - 10.f));
        crate5PlankVertical1.setPosition(sf::Vector2f(x5 + 15.f, baseY + 5.f));
        crate5PlankVertical1.setFillColor(sf::Color(175, 95, 45));
        window.draw(crate5PlankVertical1);

        sf::RectangleShape crate5PlankVertical2;
        crate5PlankVertical2.setSize(sf::Vector2f(12.f, crateHeight - 10.f));
        crate5PlankVertical2.setPosition(sf::Vector2f(x5 + 45.f, baseY + 5.f));
        crate5PlankVertical2.setFillColor(sf::Color(175, 95, 45));
        window.draw(crate5PlankVertical2);

        sf::RectangleShape crate5PlankHorizontal;
        crate5PlankHorizontal.setSize(sf::Vector2f(crateWidth - 10.f, 10.f));
        crate5PlankHorizontal.setPosition(sf::Vector2f(x5 + 5.f, baseY + 30.f));
        crate5PlankHorizontal.setFillColor(sf::Color(160, 82, 45));
        window.draw(crate5PlankHorizontal);

        sf::RectangleShape crate5Diag1;
        crate5Diag1.setSize(sf::Vector2f(crateWidth * 1.3f, 6.f));
        crate5Diag1.setPosition(sf::Vector2f(x5 - 10.f, baseY + crateHeight - 10.f));
        crate5Diag1.setFillColor(sf::Color(110, 55, 25));
        crate5Diag1.setRotation(-45.f);
        window.draw(crate5Diag1);

        sf::RectangleShape crate5Diag2;
        crate5Diag2.setSize(sf::Vector2f(crateWidth * 1.3f, 6.f));
        crate5Diag2.setPosition(sf::Vector2f(x5 - 4.f, baseY + 8.f));
        crate5Diag2.setFillColor(sf::Color(110, 55, 25));
        crate5Diag2.setRotation(45.f);
        window.draw(crate5Diag2);

        window.display();
    }

    return 0;
}
