#include <SFML/Graphics.hpp>
#include <verlet.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    sf::RenderWindow window(sf::VideoMode(900, 900), "SFML works!", sf::Style::Default, settings);
    sf::CircleShape shape(400.f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(55.f, 50.f);


    Solver solver;
    solver.init(2);
    solver.P[0].position = solver.P[0].old_position = {300.f, 700.f};
    solver.P[1].position = solver.P[1].old_position = {300.f, 500.f};

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear();
        
        window.draw(shape);

        solver.update(0.001);

        for (auto &particle: solver.P)
        {
            window.draw(particle.shape);
        }
        window.display();
    }

    // int qqq;
    // cin >> qqq;

    return 0;
}