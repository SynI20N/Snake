#include "Buffer.hpp"
#include <cstdlib>
#include <algorithm>

Buffer::Buffer(){

}

void Buffer::Push(Position position, Color color){
    Square square = Square(position, color);
    data.push_back(square);
}

void Buffer::PushFront(Position position, Color color){
    Square square = Square(position, color);
    data.insert(data.begin(), square);
}

Square Buffer::RemoveFirst(){
    Square first = data.front();
    data.erase(data.begin());
    return first;
}

Square Buffer::RemoveLast(){
    Square last = data.back();
    data.erase(data.end() - 1);
    return last;
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
    float* array = new float[data.size() * 18 + 1];//(float*)malloc(sizeof(float) * (data.size() * 18 + 1));
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
    GLfloat* arr = new GLfloat[data.size() * 18 + 1];//(float*)malloc(sizeof(float) * (data.size() * 18 + 1));
    int k = 0;
    for(int i = 0; i < data.size(); i++)
    {
        for(int j = 0; j < 18; j++)
        {
            arr[k] = data[i].GetColor()[j];
            k++;
        }
    }
    return arr;
}

int Buffer::GetCount(){
    return data.size() * 18;
}

Square Buffer::Get(int index)
{
    return data[index];
}

Square Buffer::GetLast()
{
    return data[data.size() - 1];
}

void Buffer::ReplaceFirst(Position position, Color color)
{
    data[0] = Square(position, color);
}

void Buffer::ReplaceLast(Position position, Color color)
{
    data[data.size() - 1] = Square(position, color);
}

void Buffer::Replace(int index, Position position, Color color)
{
    data[index] = Square(position, color);
}

Square Buffer::GetFirst()
{
    return data[0];
}

int Buffer::Size()
{
    return data.size();
}
