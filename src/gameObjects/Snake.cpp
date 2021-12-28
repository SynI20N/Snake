#include "Snake.hpp"
#include <cstdlib>
#include <cmath>
#include "Field.hpp"

using namespace std;

bool needInit = true;
Square poped = Square({-1, -1}, Color::white);
Velocity tailVelocity = Velocity(2, 0);

Snake::Snake(){
    
}

Snake::Snake(Position startPosition, Color snakeColor, Velocity startVelocity, Field* newField) : Renderable(){
    color = snakeColor;
    head = startPosition;
    velocity = startVelocity;
    field = newField;
    alive = true;

    for(int i = 0; i < 70; i++)
    {
        head[0] += 1;
        GetBuffer()->Push({head[0], head[1]}, Color::white);
    }
    for(int i = 0; i < 20; i++)
    {
        head[1] += 1;
        GetBuffer()->Push({head[0], head[1]}, Color::white);
    }
    for(int i = 0; i < 70; i++)
    {
        head[0] -= 1;
        GetBuffer()->Push({head[0], head[1]}, Color::white);
    }
    for(int i = 0; i < 20; i++)
    {
        head[1] += 1;
        GetBuffer()->Push({head[0], head[1]}, Color::white);
    }
    for(int i = 0; i < 70; i++)
    {
        head[0] += 1;
        GetBuffer()->Push({head[0], head[1]}, Color::white);
    }
    for(int i = 0; i < 20; i++)
    {
        head[1] += 1;
        GetBuffer()->Push({head[0], head[1]}, Color::white);
    }
    for(int i = 0; i < 70; i++)
    {
        head[0] -= 1;
        GetBuffer()->Push({head[0], head[1]}, Color::white);
    }
    for(int i = 0; i < 20; i++)
    {
        head[1] += 1;
        GetBuffer()->Push({head[0], head[1]}, Color::white);
    }
}

void Snake::Move(float timeStep){
    if(needInit)
    {
        Square first = GetBuffer()->Erase();
        GetBuffer()->Push(first.GetPosition(), Color::white);
        GetBuffer()->Push(first.GetPosition(), Color::white);
        needInit = false;
        Square tail = GetBuffer()->Pop();
        poped = GetBuffer()->Pop();
        tailVelocity[0] = poped.GetPosition()[0] - tail.GetPosition()[0];
        tailVelocity[1] = poped.GetPosition()[1] - tail.GetPosition()[1];
        GetBuffer()->PushFront(poped.GetPosition(), color);
        GetBuffer()->PushFront(tail.GetPosition(), color);
        poped = Square({-1, -1}, Color::white);
    }
    if(!GetBuffer()->Contains(poped.GetPosition()))
    {
        float movedX = 0;
        float movedY = 0;
        poped = GetBuffer()->Pop();
        head[0] += velocity[0] * timeStep;
        head[1] += velocity[1] * timeStep;
        movedX = poped.GetPosition()[0] + 10 * tailVelocity[0] * timeStep;
        movedY = poped.GetPosition()[1] + 10 * tailVelocity[1] * timeStep;
        if(head[0] > field->GetConstrains().x || head[0] <= 0)
        {
            head[0] = abs(field->GetConstrains().x - abs(head[0]));
        }
        if(head[1] > field->GetConstrains().y || head[1] <= 0)
        {
            head[1] = abs(field->GetConstrains().y - abs(head[1]));
        }
        if(GetBuffer()->Contains(head))
        {
            Die();
        }
        GetBuffer()->Erase();
        GetBuffer()->Push(head, Color::white);
        GetBuffer()->PushFront({movedX, movedY}, Color::white);
        return;
    }
    needInit = true;
    head[0] = round(head[0]);
    head[1] = round(head[1]);
    GetBuffer()->Pop();
    GetBuffer()->Erase();
    GetBuffer()->Push(head, Color::white);
}

void Snake::Die(){
    Square first = GetBuffer()->Erase();
    GetBuffer()->Push(first.GetPosition(), Color::white);
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
}

void Snake::SetVelocity(Velocity newVelocity){
    if(velocity[0] + newVelocity[0] == 0 && velocity[1] + newVelocity[1] == 0)
    {
        return;
    }
    velocity = newVelocity;
}