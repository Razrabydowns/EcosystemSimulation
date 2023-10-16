#pragma once
#include <vector>
#include "Wolf.h"
#include "Rabbit.h"
using std::vector;
class Model
{
public:
    ~Model();
    static int n;
    static int m;
    void printModel();
    void newStep();
    void freeMemory();

private:
    vector<Wolf *> MasW;
    vector<Rabbit *> masR;
    int **field;

public:
    // геттеры и сеттеры
    int get_countWolves() const { return MasW.size(); }
    int get_countRabbits() const { return masR.size(); }
    void set_field();
    void set_rabbit(Rabbit *rabbit);
    void set_wolf(Wolf *wolf);
    void set_n(int n) { this->n = n; }
    void set_m(int m) { this->m = m; }
};