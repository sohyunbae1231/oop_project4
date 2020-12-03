#include "Object.h"

Object::Object(int x, int y, char shape)
{
    this->SetX(x);
    this->SetY(y);
    this->SetShape(shape);
}

int Object::GetX() const
{
    return this->x;
}

void Object::SetX(int x)
{
    this->x = x;
}

int Object::GetY() const
{
    return this->y;
}

void Object::SetY(int y)
{
    this->y = y;
}

char Object::GetShape() const
{
    return this->shape;
}

void Object::SetShape(char shape)
{
    this->shape = shape;
}