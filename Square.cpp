#include "Square.hpp"

using namespace std;

Square::Square(Position position, Color color){
    Square::position.push_back(position[0]);
    Square::position.push_back(position[1]);
    for(int i = 0; i < 18; i++)
    {
        if(i == 0 || i == 6 || i == 12)
        {
            coords[i] = position[0];
        }
        else if(i == 1 || i == 4 || i == 10)
        {
            coords[i] = position[1];
        }
        else if(i == 3 || i == 9 || i == 15)
        {
            coords[i] = position[0] - 1;
        }
        else if(i == 7 || i == 13 || i == 16)
        {
            coords[i] = position[1] - 1;
        }
        else
        {
            coords[i] = 0;
        }
    }

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
    if(somePosition[0] == position[0] && somePosition[1] == position[1])
    {
        return true;
    }
    return false;
}

GLfloat* Square::GetCoords(){
    return coords;
}

GLfloat* Square::GetColor(){
    return colors;
}