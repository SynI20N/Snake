#pragma once

#include <vector>
#include "openGL/Draw.hpp"
#include "gameObjects/Snake.hpp"
#include "gameObjects/Food.hpp"

class Simulation{
    private:
        BufferAssembler* scene;
        Drawer drawer;
        Snake* snake;
        Food* food;
        vector<Food*> walls;
    public:
        Simulation();
        Simulation(Drawer drawer);
        void Step();
        void OnInput(GLFWwindow* window, int key, int scancode, int action, int mods);
};