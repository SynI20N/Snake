#include "Simulation.hpp"
#include "openGL/BufferAssembler.hpp"
#include <thread>
#include <unordered_map>

using namespace std;

typedef unordered_map<int, Velocity> Bindings;

Vector2 constrains;
int redrawed = 5;
Bindings keyBindings = {
    {GLFW_KEY_A, {-0.1f, 0}},
    {GLFW_KEY_D, {0.1f, 0}},
    {GLFW_KEY_W, {0, -0.1f}},
    {GLFW_KEY_S, {0, 0.1f}},
};

Simulation::Simulation(){

}

Simulation::Simulation(Drawer drawer){
    srand(time(0));
    Simulation::drawer = drawer;
    constrains.x = drawer.GetMax(0);
    constrains.y = drawer.GetMax(1);
    scene = new BufferAssembler();
    snake = new Snake({5, 5}, Color::white, {0.1, 0});
    food = new Food(Color::green);
    int wallCount = 10;
    int j = 0;
    for(int count = 0; count < wallCount; count++)
    {
        int randX = rand() % 10 + 5;
        int mode = rand() % 2;
        for(int i = 0; i < randX; i++)
        {
            if(mode)
            {
                walls.push_back(new Food(Color::blue));
            }
            else
            {
                walls.push_back(new Food(Color::blue));
            }
            scene->Bind(walls[j]->GetBuffer());
            j++;
        }
    }
    scene->Bind(food->GetBuffer());
    scene->Bind(snake->GetBuffer());
}

void Simulation::Step(){
    snake->Move(constrains, walls);
    snake->Eat(food);
    drawer.Redraw(*scene);
    redrawed--;
    if(!snake->IsAlive())
    {
        glfwSetWindowShouldClose(drawer.GetWindow(), 1);
    }
}

void Simulation::OnInput(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action != GLFW_PRESS || keyBindings.find(key) == keyBindings.end() || redrawed > 0)
    {
        return;
    }
    Velocity newVelocity = keyBindings.find(key)->second;
    snake->SetVelocity(newVelocity);
    redrawed = 5;
}
