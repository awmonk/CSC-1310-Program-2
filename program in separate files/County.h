#ifndef COUNTY_H
#define COUNTY_H

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
using namespace std;

/* COUNTY PROTOTYPES AND VARIABLES */
class County
{
private:
    string name, state;
    int index, population;

public:
    County(int, string, string, int);
    int getIndex();
    int getPopulation();
    void setIndex(int);

    bool operator<(const County &c);
    bool operator>(const County &c);

    friend ostream &operator<<(ostream &os, const County &c)
    {
        os << setw(40) << left << c.name;
        os << setw(30) << left << c.state;
        os << setw(10) << left << c.population;
        return os;
    };
};

#endif