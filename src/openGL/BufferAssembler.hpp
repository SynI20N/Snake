#pragma once

#include "Buffer.hpp"
#define OBJECT_COUNT 400

class BufferAssembler{
    private:
        Buffer* sceneBuffer[OBJECT_COUNT];
        int count;
    public:
        BufferAssembler();
        void Bind(Buffer* someBuffer);
        Buffer* Retrieve();
        int GetCount();
};