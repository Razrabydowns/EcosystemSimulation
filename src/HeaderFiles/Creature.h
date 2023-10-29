#pragma once
#include <cstdlib>
class Creature
{
public:
    Creature() : x(0), y(0) {}
    ~Creature() {}
    // координаты зверя на поле
    int x;
    int y;
    void Move();

public:
    int step; // шаг хода, у зайца - 1, у лисы - 2
};