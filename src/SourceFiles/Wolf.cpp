#include "Wolf.h"
#include "Rabbit.h"
#include <iostream>
#include <cstdlib>

using namespace std;
void Wolf::Move()
{
    change(changeDirection());
}
void Wolf::set_food(int foodCount)
{
    if (foodCount > 0)
    {
        saturation = foodCount;
    }
}
