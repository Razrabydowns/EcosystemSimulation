#pragma once
#include "Creature.h"
class Carrot : public Creature
{
public:
    Carrot() : Creature()
    {
        deathAge = 5;
        Creature::step = 0;
        age = 0;
    }
    Carrot(int x, int y) : Carrot()
    {
        this->x = x;
        this->y = y;
    }
    ~Carrot(){};
    int age;
    int deathAge;

public:
    int get_x() const { return x; }
    int get_y() const { return y; }
};