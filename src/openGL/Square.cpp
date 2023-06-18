#include "Square.hpp"
#include <cmath>

using namespace std;

Square::Square(Position position, Color color){
    this->position.push_back(position[0]);
    this->position.push_back(position[1]);
    this->color = color;
    coords[0] = position[0];
    coords[1] = position[1];
    coords[2] = 0;

    coords[3] = position[0] - 1.0f;
    coords[4] = position[1];
    coords[5] = 0;

    coords[6] = position[0];
    coords[7] = position[1] - 1.0f;
    coords[8] = 0;

    coords[9] = position[0] - 1.0f;
    coords[10] = position[1];
    coords[11] = 0;

    coords[12] = coords[6];
    coords[13] = coords[7];
    coords[14] = coords[8];

    coords[15] = position[0] - 1.0f;
    coords[16] = position[1] - 1.0f;
    coords[17] = 0;

    switch(color)
    {
        case white:
            for(int i = 0; i < 6; i++)
            {
                colors[3*i + 0] = 1;
                colors[3*i + 1] = 1;
                colors[3*i + 2] = 1;
            }
            break;
        case green:
            for(int i = 0; i < 6; i++)
            {
                colors[3*i + 0] = 0;
                colors[3*i + 1] = 1;
                colors[3*i + 2] = 0;
            }
            break;
        case red:
            for(int i = 0; i < 6; i++)
            {
                colors[3*i + 0] = 1;
                colors[3*i + 1] = 0;
                colors[3*i + 2] = 0;
            }
            break;
        case blue:
            for(int i = 0; i < 6; i++)
            {
                colors[3*i + 0] = 0;
                colors[3*i + 1] = 0;
                colors[3*i + 2] = 1;
            }
            break;
    }
}

Position Square::GetPosition(){
    return Position(position);
}

bool Square::Overlaps(Position somePosition){
    float epsilon = 0.01f;
    bool equalX = fabs(somePosition[0] - position[0]) < epsilon;
    bool equalY = fabs(somePosition[1] - position[1]) < epsilon;
    if(equalX && equalY)
    {
        return true;
    }
    return false;
}

Square Square::Copy()
{
    return Square(position, color);
}

GLfloat* Square::GetCoords(){
    return coords;
}

GLfloat* Square::GetColor(){
    return colors;
}