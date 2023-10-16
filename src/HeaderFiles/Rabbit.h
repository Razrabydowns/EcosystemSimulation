#pragma once
#include "Animal.h"
class Rabbit : public Animal
{
public:
    Rabbit() : Animal()
    {
        Animal::deathAge = 10;
        Animal::step = 1;
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
        this->deathAge = rabbit->deathAge;
        this->step = rabbit->step;
    }
    ~Rabbit(){};
    void Move();

public:
    int get_x() const { return x; }
    int get_y() const { return y; }
    int get_stability() const { return stability; }
    int get_direction() const { return direction; }
};