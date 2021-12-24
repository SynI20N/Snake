#include <cstdlib>
#include <iostream>
#include "openGL/Draw.hpp"
#include "Simulation.hpp"
#include <chrono>
#include <thread>

using namespace std;

const chrono::milliseconds frameDelay = 16ms;

Position screenSettings = Position({1600, 900, 20});
Drawer drawer;
Simulation simulation;

void resizeWindow(GLFWwindow* window, int width, int height){
    drawer.OnResize(window, width, height);
}

void processInput(GLFWwindow* window, int key, int scancode, int action, int mods){
    simulation.OnInput(window, key, scancode, action, mods);
}

int main (int argc, char** argv) {
    drawer = Drawer(screenSettings);
    simulation = Simulation(drawer);
    glfwSetKeyCallback(drawer.GetWindow(), processInput);
    glfwSetFramebufferSizeCallback(drawer.GetWindow(), resizeWindow);
    while(!glfwWindowShouldClose(drawer.GetWindow()))
    {
        for(int i = 0; i < 5; i++)
        {
            simulation.Step();
            this_thread::sleep_for(frameDelay);
        }
        glfwPollEvents();
    }
    while(glfwGetKey(drawer.GetWindow(), GLFW_KEY_ESCAPE) != GLFW_PRESS){
        this_thread::sleep_for(frameDelay);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}