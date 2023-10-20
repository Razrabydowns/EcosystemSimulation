#include "Creature.h"
#include "Model.h"
#include <iostream>
using namespace std;
void Creature::Move()
{
    int newX = x;
    int newY = y;
    newX += (rand() % 3 - 1); // от -1 до 1
    newY += (rand() % 3 - 1); // от -1 до 1

    if (newY < 0)
        newY = Model::m - 1;

    if (newX > Model::n - 1)
        newX = 0;

    if (newY > Model::m - 1)
        newY = 0;

    if (newX < 0)
        newX = Model::n - 1;

    x = newX;
    y = newY;
}