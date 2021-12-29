#include "Snake.hpp"
#include <cstdlib>
#include <cmath>
#include "Field.hpp"

using namespace std;

bool needInit = true;
float speed = 10.0f;
Velocity tailVelocity = Velocity(2, 0);
Position desiredHead = Position(2, 0);
Vector2 cachedDirection = {0, 0};
Position tail = Position(2, 0);

Snake::Snake(){
    
}

Snake::Snake(Position startPosition, Color snakeColor, Vector2 startDirection, Field* newField) : Renderable(){
    color = snakeColor;
    head = startPosition;
    direction = startDirection;
    field = newField;
    alive = true;

    for(int i = 0; i < 5; i++)
    {
        GetBuffer()->Push({head[0]++, head[1]}, color);
    }
}

void Snake::Move(float timeStep){
    if(needInit)
    {
        Square first = GetBuffer()->Erase();
        Square last = GetBuffer()->Pop();
        Square afterLast = GetBuffer()->Pop();
        GetBuffer()->Push(first.GetPosition(), color);
        GetBuffer()->Push(first.GetPosition(), color);
        desiredHead[0] = first.GetPosition()[0] + direction.x;
        desiredHead[1] = first.GetPosition()[1] + direction.y;
        if(desiredHead[0] > field->GetConstrains().x || desiredHead[0] <= 0)
        {
            desiredHead[0] = abs(field->GetConstrains().x - abs(desiredHead[0]));
        }
        if(desiredHead[1] > field->GetConstrains().y || desiredHead[1] <= 0)
        {
            desiredHead[1] = abs(field->GetConstrains().y - abs(desiredHead[1]));
        }
        tailVelocity[0] = afterLast.GetPosition()[0] - last.GetPosition()[0];
        tailVelocity[1] = afterLast.GetPosition()[1] - last.GetPosition()[1];
        head[0] = first.GetPosition()[0];
        head[1] = first.GetPosition()[1];
        tail[0] = last.GetPosition()[0];
        tail[1] = last.GetPosition()[1];
        GetBuffer()->PushFront(afterLast.GetPosition(), color);
        GetBuffer()->PushFront(last.GetPosition(), color);
        cachedDirection.x = direction.x;
        cachedDirection.y = direction.y;
        needInit = false;
    }
    head[0] += speed * cachedDirection.x * timeStep;
    head[1] += speed * cachedDirection.y * timeStep;
    tail[0] += speed * tailVelocity[0] * timeStep;
    tail[1] += speed * tailVelocity[1] * timeStep;
    bool notReachedX = (cachedDirection.x) * head[0] <= (cachedDirection.x) * desiredHead[0];
    bool notReachedY = (cachedDirection.y) * head[1] <= (cachedDirection.y) * desiredHead[1];
    if(notReachedX && notReachedY)
    {
        GetBuffer()->Pop();
        if(GetBuffer()->Contains(head))
        {
            Die();
            return;
        }
        GetBuffer()->Erase();
        GetBuffer()->Push(head, Color::blue);
        GetBuffer()->PushFront(tail, color);
    }
    else
    {
        head[0] = round(head[0]);
        head[1] = round(head[1]);
        GetBuffer()->Pop();
        GetBuffer()->Erase();
        GetBuffer()->Push(head, Color::blue);
        needInit = true;
    }
}

void Snake::Die(){
    Square first = GetBuffer()->Erase();
    GetBuffer()->Push(first.GetPosition(), color);
    GetBuffer()->Push(head, Color::red);
    alive = false;
}

bool Snake::IsAlive(){
    return alive;
}

void Snake::Eat(Food* food){
    if(!GetBuffer()->Contains(food->GetPosition()))
    {
        return;
    }
    GetBuffer()->Erase();
    GetBuffer()->Push(food->GetPosition(), color);
    GetBuffer()->Push(food->GetPosition(), food->GetColor());
    food->Reset();
    speed += 0.5f;
}

void Snake::ChangeDirection(Vector2 newDirection){
    if(direction.x + newDirection.x == 0 && direction.y + newDirection.y == 0)
    {
        return;
    }
    direction = newDirection;
}