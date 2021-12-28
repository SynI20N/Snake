#pragma once

#include "../openGL/Buffer.hpp"
#include "../openGL/Renderable.hpp"
#include "Food.hpp"

struct Vector2
{
    float x;
    float y;
};

class Field;
class Snake: public Renderable{
    private:
        Position head;
        Velocity velocity;
        Color color;
        Field* field;
        bool alive;
    public:
        Snake();
        Snake(Position startPosition, Color startColor, Velocity startVelocity, Field* newField);
        void Move(float timeStep);
        void SetVelocity(Velocity newVelocity);
        void Eat(Food* food);
        void Die();
        bool IsAlive();
};