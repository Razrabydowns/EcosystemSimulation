#include "Model.h"
#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
int Model::n = 0;
int Model::m = 0;
void Model::printModel()
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            field[i][j] = 0;
        }
    }
    for (int i = 0; i < masC.size(); i++)
    {
        cout << "MasC[i]->y" << masC[i]->y << endl;
        cout << "MasC[i]->x" << masC[i]->x << endl;
        field[masC[i]->y][masC[i]->x] = 10000;
    }
    for (int i = 0; i < masW.size(); i++)
    {
        cout << "MasW[i]->y" << masW[i]->y << endl;
        cout << "MasW[i]->x" << masW[i]->x << endl;
        field[masW[i]->y][masW[i]->x]--;
    }
    for (int i = 0; i < masR.size(); i++)
    {
        cout << "masR[i]->y" << masR[i]->y << endl;
        cout << "masR[i]->x" << masR[i]->x << endl;
        field[masR[i]->y][masR[i]->x]++;
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {

            if (field[i][j] == 0)
            {
                cout << '*';
            }
            else if (field[i][j] == 10000)
            {
                cout << 'c';
            }
            else
            {
                cout << field[i][j];
            }
        }
        cout << endl;
    }
}
void Model::newStep()
{
    spawnCarrots();
    spawnWolves();
    stepCarrot();
    stepRabbit();
    stepWolf();
}
void Model::stepCarrot()
{
    for (Carrot *carrot : masC)
    {
        carrot->age++;
        if (carrot->age == carrot->deathAge)
            deathCarrot(carrot);
    }
}
void Model::stepRabbit()
{
    for (Rabbit *rabbit : masR)
    {
        rabbit->Move();
        for (Carrot *carrot : masC)
        {
            if ((rabbit->x == carrot->x) && (rabbit->y == carrot->y))
            {
                deathCarrot(carrot);
                rabbit->increase_saturation();
            }
        }

        if (rand() % 100 < 1) // Размножение с 25% шансом
        {
            Rabbit *newRabbit = new Rabbit(*rabbit);
            masR.push_back(newRabbit);
            rabbit->decrease_saturation();
            rabbit->decrease_saturation();
        }
        rabbit->age++;
        rabbit->decrease_saturation();
        if (rabbit->saturation < 0)
        {
            deathRabbit(rabbit);
        }
    }
}
void Model::stepWolf()
{
    for (Wolf *wolf : masW)
    {
        if (wolf->saturation < 0.5)
            wolf->step = 2;
        else
            wolf->step = 1;

        while (wolf->step != 0)
        {
            wolf->Move();
            for (Rabbit *rabbit : masR)
            {
                if ((wolf->x == rabbit->x) && (wolf->y == rabbit->y))
                {
                    deathRabbit(rabbit);

                    wolf->increase_saturation();
                    wolf->countFeed++;

                    if (wolf->countFeed >= 2)
                    {
                        wolf->decrease_saturation();
                        wolf->decrease_saturation();

                        Wolf *newWolf = new Wolf(*wolf);
                        masW.push_back(newWolf);
                        wolf->countFeed = -1000;
                    }
                }
            }
            wolf->step--;
        }
        wolf->age++;
        wolf->decrease_saturation();
        if (wolf->saturation < 0)
            deathWolf(wolf);
    }
}
void Model::deathCarrot(Carrot *carrot)
{
    auto indexDeadCarrot = find(masC.begin(), masC.end(), carrot);
    masC.erase(indexDeadCarrot);
    delete carrot;
}
void Model::deathRabbit(Rabbit *rabbit)
{
    auto indexDeadRabbit = find(masR.begin(), masR.end(), rabbit);
    masR.erase(indexDeadRabbit);
    delete rabbit;
}
void Model::deathWolf(Wolf *wolf)
{
    auto indexDeadWolf = find(masW.begin(), masW.end(), wolf);
    masW.erase(indexDeadWolf);
    delete wolf;
}
void Model::spawnCarrots()
{
    int x = 0;
    int y = 0;
    int size = COUNTCARROTS - masC.size();
    for (int i = 0; i < size; i++)
    {
        x = rand() % n;
        y = rand() % m;
        Carrot *carrot = new Carrot(x, y);
        set_carrot(carrot);
    }
}
void Model::spawnWolves()
{
    int x = 0;
    int y = 0;
    int size = COUNTWOLVES - masW.size();
    for (int i = 0; i < size; i++)
    {
        x = rand() % n;
        y = rand() % m;
        Carrot *carrot = new Carrot(x, y);
        set_carrot(carrot);
    }
}
Model::~Model()
{
    for (int i = 0; i < masC.size(); i++)
    {
        delete masC[i];
    }
    for (int i = 0; i < masW.size(); i++)
    {
        delete masW[i];
    }
    for (int i = 0; i < masR.size(); i++)
    {
        delete masR[i];
    }
    for (int i = 0; i < m; i++)
    {
        delete[] field[i];
    }
    delete[] field;
}
void Model::set_field()
{
    if (n > 0 && m > 0)
    {
        field = new int *[m];
        for (int i = 0; i < m; i++)
            field[i] = new int[n];
    }
}
void Model::set_carrot(Carrot *carrot)
{
    masC.push_back(carrot);
}
void Model::set_rabbit(Rabbit *rabbit)
{
    masR.push_back(rabbit);
}
void Model::set_wolf(Wolf *wolf)
{
    masW.push_back(wolf);
}