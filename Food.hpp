#pragma once

#include "Buffer.hpp"

class Food{
    private:
        Buffer buffer;
        Position placement;
        Color color;
    public:
        Food();
        Food(Position foodPosition, Color foodColor);
        void Reset();
        Position GetPosition();
        Color GetColor();
        Buffer* GetBuffer();
};