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
    int n = 10;
    int m = 10;
    int countWolfes, countRabbits, x, y;
    Model model(n, m);

    cout << "Введите количество зайцев" << endl;
    cin >> countRabbits;
    for (int i = 0; i < countRabbits; i++)
    {
        x = rand() % n;
        y = rand() % m;
        Rabbit *rabbit = new Rabbit(x, y);
        model.set_rabbit(rabbit);
    }

    cout << "Введите количество волков" << endl;
    cin >> countWolfes;
    for (int i = 0; i < countWolfes; i++)
    {
        x = rand() % n;
        y = rand() % m;
        Wolf *wolf = new Wolf(x, y);
        model.set_wolf(wolf);
    }
    while (true)
    {
        std::cout << "\x1B[2J\x1B[H"; // типа выводит "clear" в bash
        model.printModel();
        cout << "n: " << Model::n << endl;
        cout << "m: " << Model::m << endl;
        cout << "Count wolves: " << model.get_countWolves() << endl;
        cout << "Count rabbits: " << model.get_countRabbits() << endl;
        cout << "Count carrots: " << model.get_countCarrots() << endl;
        model.newStep();
        sleep(2);
    }
    return 0;
}