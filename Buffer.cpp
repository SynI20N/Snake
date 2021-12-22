#include "Buffer.hpp"
#include <stdlib.h>
#include <algorithm>

Buffer::Buffer(){

}

void Buffer::Push(Position position, Color color){
    Square square = Square(position, color);
    data.push_back(square);
}

Square Buffer::Pop(){
    Square last = data.front();
    data.erase(data.begin());
    return last;
}

Square Buffer::Erase(){
    Square first = data.back();
    data.erase(data.end());
    return first;
}

bool Buffer::Contains(Position position){
    for(int i = 0; i < data.size(); i++)
    {
        if(data[i].Overlaps(position))
        {
            return true;
        }
    }
    return false;
}

GLfloat* Buffer::GetInfo(){
    float* array = (float*)malloc(sizeof(float) * (data.size() * 18 + 1));
    int k = 0;
    for(int i = 0; i < data.size(); i++)
    {
        for(int j = 0; j < 18; j++)
        {
            array[k] = data[i].GetCoords()[j];
            k++;
        }
    }
    return array;
}

GLfloat* Buffer::GetColorInfo(){
    float* array = (float*)malloc(sizeof(float) * (data.size() * 18 + 1));
    int k = 0;
    for(int i = 0; i < data.size(); i++)
    {
        for(int j = 0; j < 18; j++)
        {
            array[k] = data[i].GetColor()[j];
            k++;
        }
    }
    return array;
}

int Buffer::GetCount(){
    return data.size() * 18;
}