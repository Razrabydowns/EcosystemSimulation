#pragma once
#include <cstdlib>
class Animal
{
public:
    Animal() : age(0), changeDir(0), stability(0), x(0), y(0), direction(0) {}
    ~Animal() {}
    // координаты зверя на поле
    int x;
    int y;
    int direction; // направление (направления кодируются 0 (север), 1 (восток), 2 (юг), 3(запад))
    int stability;
    int age;
    int deathAge;
    int changeDir;

protected:
    int step;           // шаг хода, у зайца - 1, у лисы - 2
    void change(int d); // d - direction
    int changeDirection();
};