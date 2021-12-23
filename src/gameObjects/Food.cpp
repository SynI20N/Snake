#include "Food.hpp"
#include <cstdlib>
#include <time.h>

Food::Food(){
    
}

Food::Food(Color foodColor){
    color = foodColor;
    placement = Position(2, 0);
    buffer = Buffer();

    buffer.Push({1, 1}, color);
    Reset();
}

void Food::Reset(){
    placement[0] = rand() % 40 + 1;
    placement[1] = rand() % 40 + 1;
    buffer.Pop();
    buffer.Push({placement[0], placement[1]}, color);
}

Position Food::GetPosition(){
    return placement;
}

Color Food::GetColor(){
    return color;
}

Buffer* Food::GetBuffer(){
    return &buffer;
}