#include "Constants.hpp"
#include <stdio.h>

float speed;
chrono::milliseconds frameDelay;
Position startPosition = Position(2, 0);
Vector2 startDirection;
Position screenSettings = Position(3, 0);
//Bindings keyBindings;

void loadConfig(const char* fileName)
{
    FILE* f = fopen(fileName, "r");
    if(f == 0)
    {
        exit(1);
    }
    char* name = (char*)malloc(sizeof(char) * 20);
    fscanf(f, "%s", name);
    fscanf(f, "%d", &frameDelay);
    fscanf(f, "%s", name);
    fscanf(f, "%f", &speed);
    fscanf(f, "%s", name);
    fscanf(f, " {%f, %f}", &startDirection.x, &startDirection.y);
    fscanf(f, "%s", name);
    fscanf(f, " {%f, %f}", &startPosition[0], &startPosition[1]);
    fscanf(f, "%s", name);
    fscanf(f, " %fx%fx%f", &screenSettings[0], &screenSettings[1], &screenSettings[2]);
    fclose(f);
}