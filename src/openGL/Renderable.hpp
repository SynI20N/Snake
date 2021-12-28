#pragma once

#include "Buffer.hpp"

class Renderable{
    private:
        Buffer buffer;
    public:
        Renderable();
        Buffer* GetBuffer();
};