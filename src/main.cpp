#include <SFML/Graphics.hpp>
#include <verlet.hpp>
#include <iostream>

using namespace std;

int main()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 0;
    sf::RenderWindow window(sf::VideoMode(900, 900), "SFML works!", sf::Style::Default, settings);
    sf::CircleShape shape(200.f);
    shape.setFillColor(sf::Color::White);
    shape.setPosition(250.f, 250.f);


    Solver solver(0);

    int i = 0;
    int nn = 100;

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        if (++i <= nn * 600 && !(i%600)) solver.add_particle({400.f, 400.f});
        
        window.clear();
        
        window.draw(shape);

        solver.update(0.005);

        for (auto &particle: solver.P)
        {
            window.draw(particle.shape);
        }
        window.display();
    }

    return 0;
}