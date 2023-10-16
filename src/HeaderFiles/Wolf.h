#pragma once
#include <iostream>
#include "Animal.h"
#include "Rabbit.h"
using namespace ::std;
class Wolf : public Animal
{
public:
    Wolf() : Animal()
    {
        Animal::deathAge = 15;
        Animal::step = 2;
        saturation = 0;
    }
    Wolf(int x, int y, int direction, int stability) : Wolf()
    {
        this->x = x;
        this->y = y;
        this->direction = direction;
        this->stability = stability;
    }
    Wolf(const Wolf *&wolf)
    {
        this->x = wolf->x;
        this->y = wolf->y;
        this->direction = wolf->direction;
        this->changeDir = 0;
        this->stability = wolf->stability;
        this->age = 0;
        this->deathAge = wolf->deathAge;
        this->step = wolf->step;
        this->saturation = 0;
    }
    void Move();
    int saturation; // насыщение
public:
    // геттеры и сеттеры
    int get_x() const { return x; }
    int get_y() const { return y; }
    int get_stability() const { return stability; }
    int get_direction() const { return direction; }
    void set_food(int foodCount);
};