#include "Food.hpp"
#include <stdlib.h>
#include <time.h>

Food::Food(){
    
}

Food::Food(Position foodPosition, Color foodColor){
    placement = foodPosition;
    color = foodColor;
    buffer = Buffer();

    buffer.Push(placement, color);
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