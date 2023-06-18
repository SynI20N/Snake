#pragma once

#include <chrono>
#include <vector>
#include <unordered_map>
#include "openGL/Draw.hpp"
#include "gameObjects/Snake.hpp"

using namespace std;

typedef unordered_map<int, Vector2> Bindings;

extern chrono::milliseconds frameDelay;
extern float speed;
extern Position startPosition;
extern Vector2 startDirection;
extern Position screenSettings;
static const Bindings keyBindings = {
    {GLFW_KEY_A, {-1, 0}},
    {GLFW_KEY_D, {1, 0}},
    {GLFW_KEY_W, {0, -1}},
    {GLFW_KEY_S, {0, 1}},
};

void loadConfig(const char*);