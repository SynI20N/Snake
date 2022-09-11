#pragma once

#include <GL/glew.h>
#include <vector>

using namespace std;

typedef vector<float> Position;
typedef vector<float> Velocity;
enum Color{
    white,
    green,
    red,
    blue,
};

class Square{
    private:
        GLfloat coords[18];
        GLfloat colors[18];
        Position position;
        Color color;
    public:
        Square(Position position, Color color);
        GLfloat* GetCoords();
        GLfloat* GetColor();
        Position GetPosition();
        bool Overlaps(Position somePosition);

        Square Copy();
};