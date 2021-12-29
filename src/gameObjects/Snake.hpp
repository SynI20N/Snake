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
        Vector2 direction;
        Color color;
        Field* field;
        bool alive;
    public:
        Snake();
        Snake(Position startPosition, Color startColor, Vector2 startDirection, Field* newField);
        void Move(float timeStep);
        void ChangeDirection(Vector2 newDirection);
        void Eat(Food* food);
        void Die();
        bool IsAlive();
};