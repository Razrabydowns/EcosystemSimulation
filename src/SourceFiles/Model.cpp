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
    for (int i = 0; i < MasW.size(); i++)
    {
        cout << "MasW[i]->y" << MasW[i]->y << endl;
        cout << "MasW[i]->x" << MasW[i]->x << endl;
        field[MasW[i]->y][MasW[i]->x]--;
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
            else
            {
                cout << field[i][j];
            }
        }
        cout << endl;
    }
}
void Model::set_rabbit(Rabbit *rabbit)
{
    masR.push_back(rabbit);
}
void Model::set_wolf(Wolf *wolf)
{
    MasW.push_back(wolf);
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
void Model::newStep()
{
    for (Rabbit *rabbit : masR)
    {
        cout << "rabbit direction" << rabbit->direction << endl;
        rabbit->Move();
        rabbit->age++;
        if (rabbit->age == 5)
        {
            Rabbit *newRabbit = new Rabbit(*rabbit);
            masR.push_back(newRabbit);
        }

        if (rabbit->age == rabbit->deathAge)
        {
            auto indexDeadRabbit = find(masR.begin(), masR.end(), rabbit);
            masR.erase(indexDeadRabbit);
            delete rabbit;
            Rabbit *newRabbit = new Rabbit(*rabbit);
            masR.push_back(newRabbit);
        }
    }
    for (Wolf *wolf : MasW)
    {
        wolf->Move();
        wolf->age++;
        for (Rabbit *rabbit : masR)
        {
            if ((wolf->x == rabbit->x) && (wolf->y == rabbit->y))
            {
                auto indexDeadRabbit = find(masR.begin(), masR.end(), rabbit);
                masR.erase(indexDeadRabbit);
                delete rabbit;
                wolf->saturation++;

                if (wolf->saturation == 2)
                {
                    Wolf *newWolf = new Wolf(*wolf);
                    MasW.push_back(newWolf);
                    wolf->saturation = 0;
                }
            }
        }
        if (wolf->age == wolf->deathAge)
        {
            auto indexDeadWolf = find(MasW.begin(), MasW.end(), wolf);
            MasW.erase(indexDeadWolf);
            delete wolf;
        }
    }
}
Model::~Model()
{
    for (int i = 0; i < MasW.size(); i++)
    {
        delete MasW[i];
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