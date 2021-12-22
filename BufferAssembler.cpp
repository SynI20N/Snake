#include "BufferAssembler.hpp"
#include <cstdlib>
#include <iostream>

BufferAssembler::BufferAssembler(){
    count = 0;
    for(int i = 0; i < 100; i++)
    {
        sceneBuffer[i] = nullptr;
    }
}

void BufferAssembler::Bind(Buffer* someBuffer){
    sceneBuffer[count] = someBuffer;
    count++;
}

Buffer* BufferAssembler::Retrieve(){
    Buffer* result = new Buffer[count];
    for(int i = 0; i < count; i++)
    {
        result[i] = Buffer(*sceneBuffer[i]);
    }
    return result;
}

int BufferAssembler::GetCount(){
    return count;
}