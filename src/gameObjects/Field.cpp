#include "Field.hpp"

Field::Field(){

}

Field::Field(Vector2 newConstrains){
    scene = new BufferAssembler();
    constrains = newConstrains;
    
    for(float i = 1; i < newConstrains.x; i++)
    {
        for(float j = 1; j < newConstrains.y; j++)
        {
            availablePoints.push_back({i, j});
        }
    }
}

Snake* Field::CreateSnake(Position startPosition, Color snakeColor, Velocity startVelocity){
    Snake* snake = new Snake(startPosition, snakeColor, startVelocity, this);
    scene->Bind(snake->GetBuffer());
    return snake;
}

Food* Field::CreateFood(Color foodColor){
    Food* food = new Food(foodColor, this);
    scene->Bind(food->GetBuffer());
    return food;
}

Vector2 Field::GetConstrains(){
    return constrains;
}

Position Field::GetRandomPoint(){
    int randomIndex = rand() % availablePoints.size();
    
    Position result = availablePoints[randomIndex];
    availablePoints.erase(availablePoints.begin() + randomIndex);

    return result;
}

BufferAssembler Field::GetScene(){
    return (*scene);
}