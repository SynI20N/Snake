#pragma once

#include "../openGL/BufferAssembler.hpp"
#include <cstdlib>
#include "Food.hpp"
#include "Snake.hpp"

class Field{
    private:
        BufferAssembler* scene;
        Vector2 constrains;
        vector<Position> availablePoints;
    public:
        Field();
        Field(Vector2 newConstrains);
        Snake* CreateSnake(Position startPosition, Color snakeColor, Velocity startVelocity);
        Food* CreateFood(Color foodColor);
        Vector2 GetConstrains();
        Position GetRandomPoint();
        BufferAssembler GetScene();
};