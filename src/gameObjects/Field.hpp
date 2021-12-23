#pragma once

#include "../openGL/Square.hpp"
#include "../openGL/Buffer.hpp"

class Field{
    private:
        Buffer buffer;
        Color color;
    public:
        Field();
        void Randomize();
        Buffer* GetBuffer();
        Position GetRandomPoint();
};