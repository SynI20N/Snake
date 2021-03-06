#pragma once

#include "Square.hpp"
#include <vector>

using namespace std;

class Buffer{
    private:
        vector<Square> data;
    public:
        Buffer();
        void Push(Position position, Color color);
        void PushFront(Position position, Color color);
        Square Pop();
        Square Erase();
        GLfloat* GetInfo();
        GLfloat* GetColorInfo();
        bool Contains(Position position);
        int GetCount();
};