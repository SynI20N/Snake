#version 330 core

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

uniform float xMax;
uniform float yMax;

out vec3 fragmentColor;
out vec3 fragmentPos;

void main(){
    gl_Position.x = (2 * vertexPosition_modelspace.x) / xMax - 1;
    gl_Position.y = 1 - (2 * vertexPosition_modelspace.y) / yMax;
    gl_Position.z = vertexPosition_modelspace.z;
    gl_Position.w = 1;
    fragmentColor = vertexColor;
    fragmentPos = vertexPosition_modelspace;
}