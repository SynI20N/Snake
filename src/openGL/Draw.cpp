#include "Draw.hpp"
#include <cassert>
#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <cstdlib>
#include <string.h>
#include <GL/glew.h>
#include <cmath>
#include <chrono>

using namespace std;

const int maxIndices = 1080000;

GLfloat drawBuf[maxIndices];
GLfloat colorBuf[maxIndices];

int bufferOffset = 0;

Drawer::Drawer(){

}


GLuint loadShaders(const char * vertex_file_path,const char * fragment_file_path){
    GLuint VertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    GLuint FragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

    string VertexShaderCode;
    ifstream VertexShaderStream(vertex_file_path, ios::in);
    if(VertexShaderStream.is_open())
    {
        stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        VertexShaderCode = sstr.str();
        VertexShaderStream.close();
    }

    string FragmentShaderCode;
    ifstream FragmentShaderStream(fragment_file_path, ios::in);
    if(FragmentShaderStream.is_open()){
        stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        FragmentShaderCode = sstr.str();
        FragmentShaderStream.close();
    }

    GLint Result = GL_FALSE;
    int InfoLogLength;

    char const * VertexSourcePointer = VertexShaderCode.c_str();
    glShaderSource(VertexShaderID, 1, &VertexSourcePointer , NULL);
    glCompileShader(VertexShaderID);

    glGetShaderiv(VertexShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(VertexShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      vector<char> VertexShaderErrorMessage(InfoLogLength+1);
      glGetShaderInfoLog(VertexShaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
      fprintf(stdout, "%sn", &VertexShaderErrorMessage[0]);
    }

    char const * FragmentSourcePointer = FragmentShaderCode.c_str();
    glShaderSource(FragmentShaderID, 1, &FragmentSourcePointer , NULL);
    glCompileShader(FragmentShaderID);

    glGetShaderiv(FragmentShaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(FragmentShaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      vector<char> FragmentShaderErrorMessage(InfoLogLength+1);
      glGetShaderInfoLog(FragmentShaderID, InfoLogLength, NULL, &FragmentShaderErrorMessage[0]);
      fprintf(stdout, "%s\n", &FragmentShaderErrorMessage[0]);
    }

    GLuint ProgramID = glCreateProgram();
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);

    glGetProgramiv(ProgramID, GL_LINK_STATUS, &Result);
    glGetProgramiv(ProgramID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    if ( InfoLogLength > 0 ){
      vector<char> ProgramErrorMessage(InfoLogLength+1);
      glGetProgramInfoLog(ProgramID, InfoLogLength, NULL, &ProgramErrorMessage[0]);
      fprintf(stdout, "%s\n", &ProgramErrorMessage[0]);
    }

    glDeleteShader(VertexShaderID);
    glDeleteShader(FragmentShaderID);

    return ProgramID;
}

Drawer::Drawer(Position screenAttributes){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    screenSettings = screenAttributes;
    window = glfwCreateWindow(screenSettings[0], screenSettings[1], "Snake", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();
	glGenVertexArrays(1, &vertexArrayID);
	glBindVertexArray(vertexArrayID);
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);

    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    shaderProgramID = loadShaders( "Shaders/Vertex.glsl", "Shaders/Fragment.glsl" );
}

void Drawer::Redraw(BufferAssembler assembler){
    bufferOffset = 0;
    Buffer* buffer = assembler.Retrieve();
    for(int n = 0; n < assembler.GetCount(); n++) // O(n) this is bad
    {
        GLfloat* info = buffer[n].GetInfo();
        copy(info, info + buffer[n].GetCount(), drawBuf + bufferOffset);
        free(info);

        GLfloat* colorInfo = buffer[n].GetColorInfo();
        copy(colorInfo, colorInfo + buffer[n].GetCount(), colorBuf + bufferOffset);
        free(colorInfo);

        bufferOffset += buffer[n].GetCount();
    }
    delete[] buffer;

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(drawBuf), drawBuf, GL_DYNAMIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colorBuf), colorBuf, GL_DYNAMIC_DRAW);

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(shaderProgramID);
    GLint xMaxLocation = glGetUniformLocation(shaderProgramID, "xMax");
    GLint yMaxLocation = glGetUniformLocation(shaderProgramID, "yMax");
    glUniform1f(xMaxLocation, GetMax(0));
    glUniform1f(yMaxLocation, GetMax(1));
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(1);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glDrawArrays(GL_TRIANGLES, 0, bufferOffset / 3);
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glfwSwapBuffers(window);
}

void Drawer::OnResize(GLFWwindow* window, int width, int height){
    screenSettings[0] = width;
    screenSettings[1] = height;
    glViewport(0, 0, width, height);
}

GLFWwindow* Drawer::GetWindow(){
    return window;
}

Position Drawer::GetScreenSettings(){
    return screenSettings;
}

int Drawer::GetMax(int projection){
    return screenSettings[projection] / screenSettings[2];
}