#include "Snake.hpp"
#include <cstdlib>
#include <cmath>
#include <iostream>
#include "Field.hpp"
#include "../Constants.hpp"

using namespace std;

bool newCycle = true;
Vector2 tailDirection = { 0, 0 };
Position desiredHead = Position(2, 0);
Vector2 headDirection = { 0, 0 };
Position tail = Position(2, 0);
Buffer* snakeBuffer;
bool isTp = false;

Snake::Snake() {

}

Snake::Snake(Position startPosition, Color snakeColor, Vector2 startDirection, Field* newField) : Renderable() {
    color = snakeColor;
    head = startPosition;
    direction = startDirection;
    field = newField;
    alive = true;

    const int length = 5;

    snakeBuffer = GetBuffer();
    for (int i = length; i > 0; i--)
    {
        snakeBuffer->Push({head[0] - i, head[1]}, color);
    }
    snakeBuffer->Push({ head[0], head[1] }, Color::blue);

    tail[0] = head[0] - length;
    tail[1] = head[1];

    OnReached();

}

void Snake::Move(float timeStep) 
{
    double delta = speed * timeStep;
    head[0] += delta * headDirection.x;
    head[1] += delta * headDirection.y;
    tail[0] += delta * tailDirection.x;
    tail[1] += delta * tailDirection.y;

    bool reachedX = (headDirection.x) * head[0] > (headDirection.x) * desiredHead[0];
    bool reachedY = (headDirection.y) * head[1] > (headDirection.y) * desiredHead[1];

    if ((reachedX || reachedY) && !isTp)
    {
        OnReached();
    }

    if(!alive)
    {
        return;
    }


    if (head[0] > field->GetConstrains().x || head[0] <= 0)
    {
        head[0] = fabs(field->GetConstrains().x - fabs(head[0]));
        isTp = false;
    }
    if (head[1] > field->GetConstrains().y || head[1] <= 0)
    {
        head[1] = fabs(field->GetConstrains().y - fabs(head[1]));
        isTp = false;
    }

    snakeBuffer->ReplaceLast(head, Color::blue);
    snakeBuffer->ReplaceFirst(tail, Color::white);
    
    
}

void Snake::OnReached()
{
    snakeBuffer->RemoveFirst();
    auto newTailSquare = snakeBuffer->GetFirst();
    auto afterTailSquare = snakeBuffer->Get(1);
    auto headSquare = snakeBuffer->RemoveLast();

    head[0] = round(head[0]);
    head[1] = round(head[1]);
    tail[0] = newTailSquare.GetPosition()[0];
    tail[1] = newTailSquare.GetPosition()[1];

    snakeBuffer->Push(head, Color::white);
    snakeBuffer->Push(head, Color::blue);

    DetectDirections(afterTailSquare.GetPosition(), tail);

    desiredHead[0] = head[0] + direction.x;
    desiredHead[1] = head[1] + direction.y;
    isTp = false;
    if (desiredHead[0] > field->GetConstrains().x || desiredHead[0] <= 0)
    {
        desiredHead[0] = abs(field->GetConstrains().x - abs(desiredHead[0]));
        isTp = true;
    }
    if (desiredHead[1] > field->GetConstrains().y || desiredHead[1] <= 0)
    {
        desiredHead[1] = abs(field->GetConstrains().y - abs(desiredHead[1]));
        isTp = true;
    }

    if (GetBuffer()->Contains(desiredHead))
    {
        Die();
    }
}

void Snake::DetectDirections(Position afterTailPosition, Position tailPosition)
{
    headDirection.x = direction.x;
    headDirection.y = direction.y;

    Vector2 _tailDirection[] = { 
        { afterTailPosition[0] - tailPosition[0], afterTailPosition[1] - tailPosition[1] },
        { afterTailPosition[0] - tailPosition[0] - field->GetConstrains().x, 0 },
        { afterTailPosition[0] - tailPosition[0] + field->GetConstrains().x, 0 },
        { 0, afterTailPosition[1] - tailPosition[1] - field->GetConstrains().y },
        { 0, afterTailPosition[1] - tailPosition[1] + field->GetConstrains().y },
    };

    auto resultDirection = _tailDirection[0];
    auto minLength = VectorLength(resultDirection.x, resultDirection.y);
    for (int i = 1; i < 5; i++) 
    {
        auto currDirection = _tailDirection[i];
        auto length = VectorLength(currDirection.x, currDirection.y);
        if (length < minLength) {
            minLength = length;
            resultDirection = currDirection;
        }
    }

    tailDirection = resultDirection;
}

float Snake::VectorLength(float x, float y)
{
    return sqrt(x * x + y * y);
}

void Snake::Die() {
    GetBuffer()->ReplaceLast(head, Color::red);
    alive = false;
}

bool Snake::IsAlive() {
    return alive;
}

void Snake::TryEat(Food* food) {
    if (!GetBuffer()->Contains(food->GetPosition()))
    {
        return;
    }
    GetBuffer()->RemoveLast();
    GetBuffer()->Push(food->GetPosition(), color);
    GetBuffer()->Push(food->GetPosition(), food->GetColor());
    food->Reset();
}

void Snake::ChangeDirection(Vector2 newDirection) {
    if (headDirection.x + newDirection.x == 0 && headDirection.y + newDirection.y == 0)
    {
        return;
    }
    direction = newDirection;
}