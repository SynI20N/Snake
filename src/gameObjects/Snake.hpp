#pragma once

#include "../openGL/Buffer.hpp"
#include "../openGL/Renderable.hpp"
#include "Food.hpp"

struct Vector2
{
    float x;
    float y;
};

enum class Action {
    NOTHING = 0,
    LEFT = 1,
    RIGHT = 2,
    UP = 3,
    DOWN = 4
};
class Field;
class Snake: public Renderable{
    private:
        Position head;
        Vector2 direction;
        Color color;
        Field* field;
        bool alive;

        void OnReached();
        void DetectDirections(Position, Position);
        float VectorLength(float x, float y);
        void Die();

    public:
        Snake();
        Snake(Position startPosition, Color startColor, Vector2 startDirection, Field* newField);
        void Move(float timeStep);
        void BufferInput(Action action);
        void ChangeDirection();
        void TryEat(Food* food);
        bool IsAlive();
};