#pragma once

#include <chrono>
#include <vector>
#include <unordered_map>
#include "openGL/Draw.hpp"
#include "gameObjects/Snake.hpp"

using namespace std;

typedef unordered_map<int, Action> Bindings;

extern chrono::milliseconds frameDelay;
extern float speed;
extern Position startPosition;
extern Vector2 startDirection;
extern Position screenSettings;
extern Bindings keyBindings;

void loadConfig(const char*);