#pragma once

#include "Buffer.hpp"

class BufferAssembler{
    private:
        Buffer* sceneBuffer[400];
        int count;
    public:
        BufferAssembler();
        void Bind(Buffer* someBuffer);
        Buffer* Retrieve();
        int GetCount();
};