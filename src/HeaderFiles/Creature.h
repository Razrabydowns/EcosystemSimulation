#pragma once
#include <cstdlib>
class Creature
{
public:
    Creature() : age(0), x(0), y(0) {}
    ~Creature() {}
    // координаты зверя на поле
    int x;
    int y;
    int age;
    int deathAge;
    void Move();

protected:
    int step; // шаг хода, у зайца - 1, у лисы - 2
};