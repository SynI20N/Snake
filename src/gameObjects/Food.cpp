#include "Food.hpp"
#include <cstdlib>
#include <time.h>
#include "Field.hpp"

Food::Food(){
    
}

Food::Food(Color foodColor, Field* newField) : Renderable(){
    color = foodColor;
    field = newField;
    placement = Position(2, 0);

    (*GetBuffer()).Push({1, 1}, color);
    Reset();
}

void Food::Reset(){
    placement = field->GetRandomPoint();
    (*GetBuffer()).RemoveFirst();
    (*GetBuffer()).Push({placement[0], placement[1]}, color);
}

Position Food::GetPosition(){
    return placement;
}

Color Food::GetColor(){
    return color;
}