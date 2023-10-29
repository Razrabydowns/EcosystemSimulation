#pragma once
#include <iostream>
#include "Creature.h"
#include "Rabbit.h"
using namespace ::std;
class Wolf : public Creature
{
public:
    Wolf() : Creature()
    {
        Creature::step = 1;
        saturation = 1;
        countFeed = 0;
    }
    Wolf(int x, int y) : Wolf()
    {
        this->x = x;
        this->y = y;
    }
    Wolf(const Wolf *&wolf)
    {
        this->x = wolf->x;
        this->y = wolf->y;
        this->step = wolf->step;
        this->saturation = 1;
        this->countFeed = 0;
    }
    int countFeed;
    float saturation; // насыщение

public:
    void increase_saturation() { this->saturation += 0.2; }
    void decrease_saturation() { this->saturation -= 0.2; }
    // геттеры и сеттеры
    int get_x() const { return x; }
    int get_y() const { return y; }
};