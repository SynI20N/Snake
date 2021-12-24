#include "Snake.hpp"
#include <cstdlib>
#include <cmath>

using namespace std;

Snake::Snake(){
    
}

Snake::Snake(Position startPosition, Color snakeColor, Velocity startVelocity){
    color = snakeColor;
    head = startPosition;
    velocity = startVelocity;
    buffer = Buffer();
    alive = true;

    for(int i = 0; i < 10; i++)
    {
        buffer.Push(head, Color::white);
    }
}

void Snake::Move(Vector2 constrains, vector<Food*> walls){
    head[0] += velocity[0];
    head[1] += velocity[1];
    if(head[0] > constrains.x || head[0] <= 0)
    {
        head[0] = abs(constrains.x - abs(head[0]));
    }
    if(head[1] > constrains.y || head[1] <= 0)
    {
        head[1] = abs(constrains.y - abs(head[1]));
    }
    buffer.Pop();
    for(int i = 0; i < walls.size(); i++)
    {
        if(walls[i]->GetBuffer()->Contains(head))
        {
            Die();
            break;
        }
    }
    if(buffer.Contains(head))
    {
        Die();
    }
    else
    {
        Square first = buffer.Erase();
        buffer.Push(first.GetPosition(), Color::white);
        buffer.Push(head, Color::blue);
    }
}

void Snake::Die(){
    Square first = buffer.Erase();
    buffer.Push(first.GetPosition(), Color::white);
    buffer.Push(head, Color::red);
    alive = false;
}

bool Snake::IsAlive(){
    return alive;
}

void Snake::Eat(Food* food){
    if(!buffer.Contains((*food).GetPosition()))
    {
        return;
    }
    buffer.Erase();
    buffer.Push((*food).GetPosition(), color);
    buffer.Push((*food).GetPosition(), (*food).GetColor());
    (*food).Reset();
}

void Snake::SetVelocity(Velocity newVelocity){
    if(velocity[0] + newVelocity[0] == 0 && velocity[1] + newVelocity[1] == 0)
    {
        return;
    }
    velocity = newVelocity;
}

Buffer* Snake::GetBuffer(){
    return &buffer;
}