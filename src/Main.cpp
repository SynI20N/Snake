#include "openGL/Draw.hpp"
#include "Simulation.hpp"
#include <chrono>
#include <ctime>
#include <math.h>
#include <thread>
#include "Constants.hpp"

using namespace std;

Drawer drawer;
Simulation simulation;

void resizeWindow(GLFWwindow* window, int width, int height){
    drawer.OnResize(window, width, height);
}

void processInput(GLFWwindow* window, int key, int scancode, int action, int mods){
    simulation.OnInput(window, key, scancode, action, mods);
}

int main (int argc, char** argv) {
    loadConfig("config.txt");
    drawer = Drawer(screenSettings);
    simulation = Simulation(drawer);
    glfwSetKeyCallback(drawer.GetWindow(), processInput);
    glfwSetFramebufferSizeCallback(drawer.GetWindow(), resizeWindow);
    auto start = chrono::steady_clock::now();
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    while(!glfwWindowShouldClose(drawer.GetWindow()))
    {
        start = chrono::steady_clock::now();
        this_thread::sleep_for(frameDelay);
        simulation.Step(chrono::duration_cast<chrono::microseconds>(diff).count() / pow(10, 6));
        end = chrono::steady_clock::now();
        diff = end - start;
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}