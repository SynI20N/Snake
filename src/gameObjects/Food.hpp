#pragma once

#include "../openGL/Buffer.hpp"
#include "Field.hpp"

class Food{
    private:
        Buffer buffer;
        Position placement;
        Color color;
    public:
        Food();
        Food(Color foodColor);
        void Reset();
        Position GetPosition();
        Color GetColor();
        Buffer* GetBuffer();
};