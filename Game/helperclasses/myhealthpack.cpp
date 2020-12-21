#include "myhealthpack.h"

MyHealthpack::MyHealthpack(int x,int y,float value)
    :x(x),y(y),health(value)
{
}

float MyHealthpack::getHealth() const
{
    return health;
}

void MyHealthpack::setHealth(float value)
{
    health = value;
}

int MyHealthpack::getX() const
{
    return x;
}

int MyHealthpack::getY() const
{
    return y;
}

bool MyHealthpack::getUsed() const
{
    return used;
}

void MyHealthpack::setUsed(bool value)
{
    used = value;
}
