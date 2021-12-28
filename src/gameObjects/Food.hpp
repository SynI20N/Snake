#pragma once

#include "../openGL/Buffer.hpp"
#include "../openGL/Renderable.hpp"
#include <cstdlib>

class Field;
class Food : public Renderable{
    private:
        Field* field;
        Position placement;
        Color color;
    public:
        Food();
        Food(Color foodColor, Field* newField);
        void Reset();
        Position GetPosition();
        Color GetColor();
};