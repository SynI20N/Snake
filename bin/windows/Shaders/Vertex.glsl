#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

out vec3 fragmentColor;
out vec3 fragmentPos;

void main(){
    gl_Position.xyz = vertexPosition_modelspace;
    gl_Position.w = 1;
    fragmentColor = vertexColor;
    fragmentPos = vertexPosition_modelspace;
}