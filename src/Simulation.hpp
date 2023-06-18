#pragma once

#include "openGL/BufferAssembler.hpp"
#include "openGL/Draw.hpp"
#include "gameObjects/Snake.hpp"
#include "gameObjects/Food.hpp"
#include "gameObjects/Field.hpp"

class Simulation{
    private:
        Drawer drawer;
        Field* field;
        Snake* snake;
        Food* food;
    public:
        Simulation();
        Simulation(Drawer drawer);
        void Step(float deltaTime);
        void OnInput(GLFWwindow* window, int key, int scancode, int action, int mods);
};