#pragma once

#include "Square.hpp"
#include "Buffer.hpp"

class Field{
    private:
        Buffer buffer;
        vector<Position> walls;
        Color color;
    public:
        Field(Color color);
        void Randomize();
        Buffer* GetBuffer();
};