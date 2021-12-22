#version 330 core

in vec3 fragmentColor;
in vec3 fragmentPos;

out vec3 color;

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

void main(){
    float finalX = rand(vec2(fragmentPos.x,fragmentPos.y));
    float finalY = rand(vec2(fragmentPos.x,fragmentPos.y));
    float finalZ = rand(vec2(fragmentPos.x,fragmentPos.y));
    color = fragmentColor - vec3(finalX, finalY, finalZ);
}