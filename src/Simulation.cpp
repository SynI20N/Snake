#include "Simulation.hpp"
#include "Constants.hpp"

using namespace std;

typedef unordered_map<int, Velocity> Bindings;
const float speed = 10.0f;

Vector2 constrains;
Bindings keyBindings = {
    {GLFW_KEY_A, {-speed, 0}},
    {GLFW_KEY_D, {speed, 0}},
    {GLFW_KEY_W, {0, -speed}},
    {GLFW_KEY_S, {0, speed}},
};

Simulation::Simulation(){

}

Simulation::Simulation(Drawer drawer){
    srand(time(0));
    Simulation::drawer = drawer;
    constrains.x = drawer.GetMax(0);
    constrains.y = drawer.GetMax(1);
    field = new Field(constrains);
    snake = field->CreateSnake({5, 5}, Color::white, {-speed, 0});
    food = field->CreateFood(Color::green);
}

void Simulation::Step(){
    snake->Move(frameDelayF);
    snake->Eat(food);
    drawer.Redraw(field->GetScene());
    if(!snake->IsAlive())
    {
        glfwSetWindowShouldClose(drawer.GetWindow(), 1);
    }
}

void Simulation::OnInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS || keyBindings.find(key) == keyBindings.end())
    {
        return;
    }
    Velocity newVelocity = keyBindings.find(key)->second;
    snake->SetVelocity(newVelocity);
}
