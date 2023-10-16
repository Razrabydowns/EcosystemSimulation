#include "Rabbit.h"
#include <iostream>
#include <cstdlib>
using namespace std;

void Rabbit::Move()
{
    change(changeDirection());
}