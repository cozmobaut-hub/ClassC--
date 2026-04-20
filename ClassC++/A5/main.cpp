#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

#include "scalenetriangle.hpp"
#include "isoscelestriangle.hpp"
#include "equilateraltriangle.hpp"
#include "rhombus.hpp"

int main() {
    std::ifstream fin("polygons.txt");
    if (!fin) {
        std::cerr << "Could not open polygons.txt\n";
        return 1;
    }

    std::vector<Polygon*> polys;
    std::string line;

    while (std::getline(fin, line)) {
        if (line.empty()) continue;

        std::istringstream iss(line);
        char t;
        double x1, y1, x2, y2, x3, y3, x4, y4;
        int r, g, b;

        Polygon* p = nullptr;

        if (!(iss >> t >> x1 >> y1 >> x2 >> y2 >> x3 >> y3)) continue;

        if (t == 'S') {
            if (!(iss >> r >> g >> b)) continue;
            p = new ScaleneTriangle();
            p->setCoordinate(0, {x1, y1});
            p->setCoordinate(1, {x2, y2});
            p->setCoordinate(2, {x3, y3});
        } else if (t == 'I') {
            if (!(iss >> r >> g >> b)) continue;
            p = new IsoscelesTriangle();
            p->setCoordinate(0, {x1, y1});
            p->setCoordinate(1, {x2, y2});
            p->setCoordinate(2, {x3, y3});
        } else if (t == 'E') {
            if (!(iss >> r >> g >> b)) continue;
            p = new EquilateralTriangle();
            p->setCoordinate(0, {x1, y1});
            p->setCoordinate(1, {x2, y2});
            p->setCoordinate(2, {x3, y3});
        } else if (t == 'R') {
            if (!(iss >> x4 >> y4 >> r >> g >> b)) continue;
            p = new Rhombus();
            p->setCoordinate(0, {x1, y1});
            p->setCoordinate(1, {x2, y2});
            p->setCoordinate(2, {x3, y3});
            p->setCoordinate(3, {x4, y4});
        } else {
            continue;
        }

        if (p->validate()) {
            p->setColor(sf::Color(r, g, b));
            polys.push_back(p);
        } else {
            std::cout << "polygon is invalid - \"" << line << "\"" << std::endl;
            delete p;
        }
    }

    sf::RenderWindow window(sf::VideoMode(800, 600), "Polygons");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear(sf::Color::White);
        for (Polygon* p : polys) {
            p->draw(window);
        }
        window.display();
    }

    for (Polygon* p : polys) delete p;
    return 0;
}
