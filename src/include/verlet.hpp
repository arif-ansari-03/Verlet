#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

using namespace std;

struct Vec2
{
    double x, y;

    Vec2(double x1, double y1)
    {
        x = x1;
        y = y1;
    }

    Vec2(Vec2 &A)
    {
        x = A.x;
        y = A.y;
    }

    Vec2(const Vec2 &A)
    {
        x = A.x;
        y = A.y;
    }

    Vec2()
    { x = 0, y = 0; }

    Vec2 operator+(Vec2 A)
    {
        Vec2 B;
        B.x = x + A.x;
        B.y = y + A.y;
        return B;
    }
    Vec2 operator-(Vec2 A)
    {
        Vec2 B;
        B.x = x - A.x;
        B.y = y - A.y;
        return B;
    }
    Vec2 operator*(Vec2 A)
    {
        Vec2 B;
        B.x = x * A.x;
        B.y = y * A.y;
        return B;
    }
    Vec2 operator/(Vec2 A)
    {
        Vec2 B;
        B.x = x / A.x;
        B.y = y / A.y;
        return B;
    }

    Vec2 operator+=(Vec2 A)
    {
        x += A.x;
        y += A.y;
        return *this;
    }

    Vec2 operator*(double a)
    {
        return Vec2(x * a, y * a);
    }

    Vec2 operator/(double a)
    {
        // if (a == 0) return *this;
        return Vec2(x / a, y / a);
    }

    double length()
    {
        return sqrt(x*x + y*y);
    }
};


struct particle
{
    Vec2 position;
    Vec2 old_position;
    Vec2 acceleration;

    sf::CircleShape shape;

    particle()
    {
        shape.setRadius(5.0f);
        shape.setFillColor(sf::Color::Green);
        shape.setPosition(sf::Vector2f(position.x-5.f, position.y-5.f));
    }

    void update(double dt)
    {
        const Vec2 velocity = position - old_position;

        old_position = position;

        position = position + velocity + acceleration * dt * dt;

        acceleration = {};

        shape.setPosition(sf::Vector2f(position.x, position.y));
    }

    void accelerate(Vec2 acc)
    {
        acceleration += acc;
    }
};


struct Solver
{
    Vec2 gravity = {0.f, 100.f};
    vector<particle> P;

    void init(int a)
    {
        P.resize(a);
    }

    void apply_gravity()
    {
        for (auto &particle : P)
        particle.accelerate(gravity);
    }

    void update_position(double dt)
    {
        for (auto &particle: P)
        particle.update(dt);
    }

    void apply_constraint()
    {
        Vec2 center = {450.f, 450.f};
        double radius = 400.f;

        for (auto &particle: P)
        {
            Vec2 to_obj = particle.position - center;
            double dist = to_obj.length();

            if (dist > radius - 10.f)
            {
                Vec2 n = to_obj / to_obj.length() * (radius - 10.f);
                particle.position = center + n;
            }
        }
    }

    void update(double dt)
    {
        apply_gravity();
        apply_constraint();
        update_position(dt);
    }
};