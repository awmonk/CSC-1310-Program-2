#ifndef COUNTY_H
#define COUNTY_H

#include <iostream>
#include <iomanip>
#include <string>
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

    /* Replaced the colons and commas in the ostream function with a set width table
       for improved legibility */
    friend ostream &operator<<(ostream &os, const County &c)
    {
        os << setw(50) << left << c.name;
        os << setw(30) << left << c.state;
        os << setw(10) << left << c.population;
        return os;
    };
};

#endif