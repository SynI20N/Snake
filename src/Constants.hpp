#include <chrono>

using namespace std;

const chrono::milliseconds frameDelay = 16ms;
const float frameDelayF = (double)(frameDelay.count()) / 1000.0;