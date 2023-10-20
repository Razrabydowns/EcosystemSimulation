#pragma once
#include "Creature.h"
class Carrot : public Creature
{
public:
    Carrot() : Creature()
    {
        Creature::deathAge = 5;
        Creature::step = 0;
    }
    Carrot(int x, int y) : Carrot()
    {
        this->x = x;
        this->y = y;
    }
    ~Carrot(){};

public:
    int get_x() const { return x; }
    int get_y() const { return y; }
    int get_stability() const { return stability; }
    int get_direction() const { return direction; }
};