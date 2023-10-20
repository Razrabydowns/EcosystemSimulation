#pragma once
#include "Creature.h"
class Rabbit : public Creature
{
public:
    Rabbit() : Creature()
    {
        Creature::step = 1;
        saturation = 1;
    }
    Rabbit(int x, int y, int direction, int stability) : Rabbit()
    {
        this->x = x;
        this->y = y;
        this->direction = direction;
        this->stability = stability;
    }
    Rabbit(const Rabbit *&rabbit)
    {
        this->x = rabbit->x;
        this->y = rabbit->y;
        this->stability = rabbit->stability;
        this->direction = rabbit->direction;
        this->changeDir = 0;
        this->stability = rabbit->stability;
        this->age = 0;
        this->step = rabbit->step;
        this->saturation = 1;
    }
    ~Rabbit(){};
    void Move();
    int saturation;

public:
    void increase_saturation() { this->saturation += 0.2; }
    void decrease_saturation() { this->saturation -= 0.2; }
    int get_x() const { return x; }
    int get_y() const { return y; }
    int get_stability() const { return stability; }
    int get_direction() const { return direction; }
};