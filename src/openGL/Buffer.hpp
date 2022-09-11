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
        Square RemoveFirst();
        Square RemoveLast();
        GLfloat* GetInfo();
        GLfloat* GetColorInfo();
        bool Contains(Position position);
        int GetCount();

        Square Get(int index);
        Square GetLast();
        Square GetFirst();
        void ReplaceFirst(Position, Color);
        void ReplaceLast(Position, Color);
        void Replace(int, Position, Color);
        int Size();
};