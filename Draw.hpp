#pragma once

#include <vector>
#include <GL/glew.h>
#include <glfw3.h>
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
        float TransformX(int x);
        float TransformY(int y);
        int GetMax(int i);
        void OnResize(GLFWwindow* window, int width, int height);
};