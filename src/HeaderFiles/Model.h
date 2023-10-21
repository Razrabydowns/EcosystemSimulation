#pragma once
#include <vector>
#include "Wolf.h"
#include "Rabbit.h"
#include "Carrot.h"
#define COUNTCARROTS 5
#define COUNTWOLVES 5
using std::vector;
class Model
{
public:
    Model(int n, int m)
    {
        this->n = n;
        this->m = m;
        set_field();
        spawnCarrots();
    }
    ~Model();
    static int n;
    static int m;
    void printModel();
    void newStep();
    void freeMemory();

private:
    void spawnCarrots();
    void deathCarrot(Carrot *carrot);
    void deathRabbit(Rabbit *rabbit);
    void deathWolf(Wolf *wolf);
    void stepCarrot();
    void stepRabbit();
    void stepWolf();
    void spawnWolves();

private:
    vector<Carrot *> masC;
    vector<Rabbit *> masR;
    vector<Wolf *> masW;
    int **field;

public:
    // геттеры и сеттеры
    int get_countWolves() const { return masW.size(); }
    int get_countRabbits() const { return masR.size(); }
    int get_countCarrots() const { return masC.size(); }
    void set_field();
    void set_carrot(Carrot *rabbit);
    void set_rabbit(Rabbit *rabbit);
    void set_wolf(Wolf *wolf);
};