#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

using namespace std;

float length(sf::Vector2f a)
{
    return sqrt(a.x*a.x + a.y*a.y);
}

struct particle
{
    sf::Vector2f position;
    sf::Vector2f old_position;
    sf::Vector2f acceleration;
    float radius;
    sf::CircleShape shape;
    sf::Vector2f rr;

    particle()
    {
        position = {400.f, 400.f};
        old_position = position;
        radius = 10.f;
        rr = {radius, radius};
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(position-rr);
    }

    particle(sf::Vector2f pos)
    {
        position = pos;
        old_position = position;
        radius = 10.f;
        rr = {radius, radius};
        shape.setRadius(radius);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(position-rr);
    }

    void update(float dt)
    {
        const sf::Vector2f velocity = position - old_position;

        old_position = position;

        position = position + velocity + acceleration * dt * dt;

        acceleration = {};

        shape.setPosition(position - rr);
    }

    void accelerate(sf::Vector2f acc)
    {
        acceleration += acc;
    }
};


struct Solver
{
    sf::Vector2f gravity = {0.f, 5.f};
    vector<particle> P;
    int n;

    Solver(int a)
    {
        P = vector<particle>(a);
        n = a;
    }

    void add_particle(sf::Vector2f pos)
    {
        P.emplace_back(particle(pos));
        n++;
    }

    void apply_gravity()
    {
        for (auto &particle : P)
        particle.accelerate(gravity);
    }

    void update_position(float dt)
    {
        for (auto &particle: P)
        particle.update(dt);
    }

    void apply_constraint()
    {
        sf::Vector2f center = {450.f, 450.f};
        float radius = 200.f;

        for (auto &particle: P)
        {
            sf::Vector2f to_obj = particle.position - center;
            float dist = length(to_obj);

            if (dist > radius - particle.radius)
            {
                sf::Vector2f n = to_obj / length(to_obj) * (radius - particle.radius);
                particle.position = center + n;
            }
        }

        // float border_x = 900.f, border_y = 900.f
        // for (auto &particle: P)
        // {
        //     if (particle.position.x > )
        // }
    }

    void solve_collisions()
    {
        for (int i = 0; i < n-1; i++)
        for (int j = i+1; j < n; j++)
        {
            sf::Vector2f col_axis = P[i].position - P[j].position;
            float dist = length(col_axis);
            if (dist < P[i].radius+P[j].radius)
            {
                col_axis = col_axis / dist;
                dist = P[i].radius+P[j].radius - dist;
                P[i].position = P[i].position + col_axis * .5f * dist;
                P[j].position = P[j].position - col_axis * .5f * dist;
            }
        }
    }

    void update(float dt)
    {
        for (int i = 0; i < 2; i++)
        {
            apply_gravity();
            apply_constraint();
            solve_collisions();
            update_position(dt);
        }
    }
};