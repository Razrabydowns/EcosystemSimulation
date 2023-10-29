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
    for (auto it = masC.begin(); it != masC.end();)
    {
        Carrot *carrot = *it;
        carrot->age++;
        if (carrot->age == carrot->deathAge)
            deathCarrot(carrot);

        it++;
    }
}
void Model::stepRabbit()
{
    for (auto it = masR.begin(); it != masR.end();)
    {
        Rabbit *rabbit = *it;
        rabbit->Move();

        for (auto it2 = masC.begin(); it2 != masC.end();)
        {
            Carrot *carrot = *it2;
            if ((rabbit->x == carrot->x) && (rabbit->y == carrot->y))
            {
                delete carrot;         // освобождение памяти, выделенной для объекта
                it2 = masC.erase(it2); // удаление указателя на объект из вектора
                rabbit->increase_saturation();
            }
            else
            {
                ++it2;
            }
        }
        if (rand() % 25 < 1) // Размножение с 25% шансом
        {
            Rabbit *newRabbit = new Rabbit(*rabbit);
            set_rabbit(newRabbit);
            rabbit->decrease_saturation();
            rabbit->decrease_saturation();
        }
        rabbit->decrease_saturation();
        if (rabbit != NULL && rabbit->saturation < 0)
        {
            delete rabbit;       // освобождение памяти, выделенной для объекта
            it = masR.erase(it); // удаление указателя на объект из вектора
        }
        else
        {
            ++it;
        }
    }
}
void Model::stepWolf()
{
    for (auto it = masW.begin(); it != masW.end();)
    {
        Wolf *wolf = *it;
        if (wolf->saturation < 0.5)
            wolf->step = 2;
        else
            wolf->step = 1;
        while (wolf->step != 0)
        {
            wolf->Move();
            for (auto it2 = masC.begin(); it2 != masC.end();)
            {
                Carrot *carrot = *it2;
                if ((wolf->x == carrot->x) && (wolf->y == carrot->y))
                {
                    delete carrot;         // освобождение памяти, выделенной для объекта
                    it2 = masC.erase(it2); // удаление указателя на объект из вектора
                }
                else
                {
                    ++it2;
                }
            }
            for (auto it2 = masR.begin(); it2 != masR.end();)
            {
                Rabbit *rabbit = *it2;
                if ((wolf->x == rabbit->x) && (wolf->y == rabbit->y))
                {
                    delete rabbit;         // освобождение памяти, выделенной для объекта
                    it2 = masR.erase(it2); // удаление указателя на объект из вектора

                    wolf->increase_saturation();
                    wolf->countFeed++;

                    if (wolf->countFeed >= 2)
                    {
                        wolf->decrease_saturation();
                        wolf->decrease_saturation();

                        Wolf *newWolf = new Wolf(*wolf);
                        set_wolf(newWolf);
                        wolf->countFeed = -1000;
                    }
                }
                else
                {
                    ++it2;
                }
            }
            wolf->step--;
        }
        wolf->decrease_saturation();

        if (wolf != NULL && wolf->saturation < 0)
        {
            delete wolf;         // освобождение памяти, выделенной для объекта
            it = masW.erase(it); // удаление указателя на объект из вектора
        }
        else
        {
            ++it;
        }
    }
}
void Model::deathCarrot(Carrot *carrot)
{
    if (carrot == nullptr)
        return;

    auto indexDeadCarrot = find(masC.begin(), masC.end(), carrot);
    if (indexDeadCarrot != masC.end())
    {
        delete *indexDeadCarrot;     // освобождение памяти, выделенной для объекта
        masC.erase(indexDeadCarrot); // удаление указателя на объект из вектора
    }
}
void Model::deathRabbit(Rabbit *rabbit)
{
    if (rabbit == nullptr)
        return;

    auto indexDeadRabbit = find(masR.begin(), masR.end(), rabbit);
    if (indexDeadRabbit != masR.end())
    {
        delete *indexDeadRabbit;     // освобождение памяти, выделенной для объекта
        masR.erase(indexDeadRabbit); // удаление указателя на объект из вектора
    }
}
void Model::deathWolf(Wolf *wolf)
{
    if (wolf == nullptr)
        return;

    auto indexDeadWolf = find(masW.begin(), masW.end(), wolf);
    if (indexDeadWolf != masW.end())
    {
        delete *indexDeadWolf;     // освобождение памяти, выделенной для объекта
        masW.erase(indexDeadWolf); // удаление указателя на объект из вектора
    }
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
        if (x == 0 || x == n - 1)
        {
            y = rand() % n;
        }
        else
        {
            if ((rand() % 100) < 50)
                y = 0;
            else
                y = m - 1;
        }
        Wolf *wolf = new Wolf(x, y);
        set_wolf(wolf);
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