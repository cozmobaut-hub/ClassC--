#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

int main() {
    sf::Vector2u windowSize(640, 640);
    sf::RenderWindow window(
        sf::VideoMode(windowSize.x, windowSize.y),
        "SFML Puppy Plural"
    );

    /////////////////////////////////////
    // BEGIN ANY FILE LOADING

    
    // Head
    sf::CircleShape head(30.f);        // radius 30
    head.setOrigin(30.f, 30.f);        // center origin

    // Ears
    sf::CircleShape earLeft(12.f);
    earLeft.setOrigin(12.f, 12.f);
    sf::CircleShape earRight(12.f);
    earRight.setOrigin(12.f, 12.f);

    // Body
    sf::RectangleShape body(sf::Vector2f(60.f, 80.f));
    body.setOrigin(30.f, 40.f);

   
    head.setFillColor(sf::Color(200, 180, 160));
    earLeft.setFillColor(sf::Color(180, 150, 130));
    earRight.setFillColor(sf::Color(180, 150, 130));
    body.setFillColor(sf::Color(190, 170, 150));

    
    const int puppyCount = 5;
    sf::Vector2f positions[puppyCount] = {
        { 80.f, 320.f },
        { 200.f, 320.f },
        { 320.f, 320.f },
        { 440.f, 320.f },
        { 560.f, 320.f }
    };

    // 5 different main colors for the puppies
    sf::Color colors[puppyCount] = {
        sf::Color::Red,
        sf::Color::Green,
        sf::Color::Blue,
        sf::Color::Yellow,
        sf::Color(255, 105, 180) // hot pink
    };

    // END ANY FILE LOADING
    /////////////////////////////////////

    while (window.isOpen()) {
        // EVENT HANDLING
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        // Black background
        window.clear(sf::Color::Black);

        // DRAWING: 5 puppies
        for (int i = 0; i < puppyCount; ++i) {
            sf::Vector2f basePos = positions[i];

            // color this puppy
            sf::Color c = colors[i];

            sf::CircleShape headP = head;
            sf::CircleShape earLeftP = earLeft;
            sf::CircleShape earRightP = earRight;
            sf::RectangleShape bodyP = body;

            // tint each whole puppy by the chosen color (overriding neutral)
            headP.setFillColor(c);
            earLeftP.setFillColor(c);
            earRightP.setFillColor(c);
            bodyP.setFillColor(c);

            // position relative parts
            headP.setPosition(basePos.x, basePos.y - 30.f);
            earLeftP.setPosition(basePos.x - 25.f, basePos.y - 55.f);
            earRightP.setPosition(basePos.x + 25.f, basePos.y - 55.f);
            bodyP.setPosition(basePos.x, basePos.y + 30.f);

            window.draw(bodyP);
            window.draw(headP);
            window.draw(earLeftP);
            window.draw(earRightP);
        }

        window.display();
    }
    
    return 0;
}
