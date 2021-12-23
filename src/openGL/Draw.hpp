#pragma once

#include <vector>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Buffer.hpp"
#include "BufferAssembler.hpp"


using namespace std;

class Drawer{
    private:
        GLuint vertexBuffer;
        GLuint colorBuffer;
        GLuint vertexArrayID;
        GLuint shaderProgramID;
        GLFWwindow* window;
        Position screenSettings;
    public:
        Drawer();
        Drawer(Position screenAttributes);
        void Redraw(BufferAssembler assembler);
        GLFWwindow* GetWindow();
        Position GetScreenSettings();
        float TransformX(float x);
        float TransformY(float y);
        int GetMax(int i);
        void OnResize(GLFWwindow* window, int width, int height);
};