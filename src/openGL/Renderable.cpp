#include "Renderable.hpp"

Renderable::Renderable(){
    buffer = Buffer();
}

Buffer* Renderable::GetBuffer(){
    return &buffer;
}