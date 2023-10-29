#pragma once
#include "Creature.h"
#include <iostream>
class Rabbit : public Creature
{
public:
    Rabbit() : Creature()
    {
        Creature::step = 1;
        saturation = 1;
    }
    Rabbit(int x, int y) : Rabbit()
    {
        this->x = x;
        this->y = y;
    }
    Rabbit(const Rabbit *&rabbit)
    {
        this->x = rabbit->x;
        this->y = rabbit->y;
        this->step = rabbit->step;
        this->saturation = 1;
    }
    ~Rabbit() {}
    float saturation;

public:
    void increase_saturation() { this->saturation += 0.2; }
    void decrease_saturation() { this->saturation -= 0.2; }
    int get_x() const { return x; }
    int get_y() const { return y; }
};