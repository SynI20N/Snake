#include "Constants.hpp"
#include <stdio.h>

int tmp;
float speed;
chrono::milliseconds frameDelay;
Position startPosition = Position(2, 0);
Vector2 startDirection;
Position screenSettings = Position(3, 0);
Bindings keyBindings;
std::pair<int, Action> keyAction;

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
    fscanf(f, " %fx%f", &screenSettings[0], &screenSettings[1]);
    fscanf(f, "%s", name);
    fscanf(f, "%f", &screenSettings[2]);
    fscanf(f, "%s", name);
    while(fscanf(f, " {'%d'=%d}", &keyAction.first, &tmp) >  0)
    {
        keyAction.second = (Action)tmp;
        keyBindings.insert(keyAction);
    }
    fclose(f);
}