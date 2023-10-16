#include <iostream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <stdlib.h>
#include <fstream>
#include "Wolf.h"
#include "Rabbit.h"
#include "Model.h"
using namespace std;
int main(int argc, char *argv[])
{
    srand(time(NULL));
    int countFoxes, countRabbits, x, y;
    Model model;
    int n = 10;
    int m = 10;
    model.set_n(n);
    model.set_m(m);
    model.set_field();

    cout << "Введите количество зайцев" << endl;
    cin >> countRabbits;
    for (int i = 0; i < countRabbits; i++)
    {
        x = rand() % n;
        y = rand() % m;
        Rabbit *rabbit = new Rabbit(x, y, 0, 2);
        model.set_rabbit(rabbit);
    }

    cout << "Введите количество лисов" << endl;
    cin >> countFoxes;
    for (int i = 0; i < countFoxes; i++)
    {
        x = rand() % n;
        y = rand() % m;
        Wolf *wolf = new Wolf(x, y, 0, 2);
        model.set_wolf(wolf);
    }
    while (true)
    {
        std::cout << "\x1B[2J\x1B[H"; // типа выводит "clear" в bash
        model.printModel();
        cout << "n: " << Model::n << endl;
        cout << "m: " << Model::m << endl;
        cout << "Count foxes: " << model.get_countWolves() << endl;
        cout << "Count rabbits: " << model.get_countRabbits() << endl;
        model.newStep();
        sleep(1);
    }
    return 0;
}