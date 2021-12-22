#pragma once

#include "Buffer.hpp"
#include "Food.hpp"

struct Vector2
{
    int x;
    int y;
};


class Snake{
    private:
        Buffer buffer;
        Position head;
        Velocity velocity;
        Color color;
        bool alive;
    public:
        Snake();
        Snake(Position startPosition, Color startColor, Velocity startVelocity);
        void Move(Vector2 constrains, vector<Food*> walls);
        void SetVelocity(Velocity newVelocity);
        void Eat(Food* food);
        void Die();
        bool IsAlive();
        Buffer* GetBuffer();
};