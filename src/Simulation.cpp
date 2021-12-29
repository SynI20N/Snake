#include "Simulation.hpp"
#include "Constants.hpp"

using namespace std;

typedef unordered_map<int, Vector2> Bindings;

Vector2 constrains;
bool redrawed = true;
Bindings keyBindings = {
    {GLFW_KEY_A, {-1, 0}},
    {GLFW_KEY_D, {1, 0}},
    {GLFW_KEY_W, {0, -1}},
    {GLFW_KEY_S, {0, 1}},
};

Simulation::Simulation(){

}

Simulation::Simulation(Drawer drawer){
    srand(time(0));
    Simulation::drawer = drawer;
    constrains.x = drawer.GetMax(0);
    constrains.y = drawer.GetMax(1);
    field = new Field(constrains);
    snake = field->CreateSnake({5, 5}, Color::white, {1, 0});
    food = field->CreateFood(Color::green);
}

void Simulation::Step(){
    snake->Move(frameDelayF);
    snake->Eat(food);
    drawer.Redraw(field->GetScene());
    redrawed = 1;
    if(!snake->IsAlive())
    {
        glfwSetWindowShouldClose(drawer.GetWindow(), 1);
    }
}

void Simulation::OnInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS || keyBindings.find(key) == keyBindings.end() && redrawed)
    {
        return;
    }
    Vector2 newDirection = keyBindings.find(key)->second;
    snake->ChangeDirection(newDirection);
    redrawed = 0;
}
