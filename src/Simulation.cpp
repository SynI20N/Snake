#include "Simulation.hpp"
#include "Constants.hpp"

using namespace std;

Vector2 constrains;
bool redrawed = true;

Simulation::Simulation(){

}

Simulation::Simulation(Drawer drawer){
    srand(time(0));
    Simulation::drawer = drawer;
    constrains.x = drawer.GetMax(0);
    constrains.y = drawer.GetMax(1);
    field = new Field(constrains);
    snake = field->CreateSnake(startPosition, Color::white, startDirection);
    food = field->CreateFood(Color::green);
}

void Simulation::Step(float deltaTime){
    if (snake->IsAlive())
    {
        snake->Move(deltaTime);
        snake->TryEat(food);
    }
    drawer.Redraw(field->GetScene());
}

void Simulation::OnInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS || keyBindings.find(key) == keyBindings.end())
    {
        return;
    }
    Vector2 newDirection = keyBindings.find(key)->second;
    snake->ChangeDirection(newDirection);
}
