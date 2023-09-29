#include "County.h"
#include "List.h"
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int main()
{
    ifstream file;
    stringstream temp;
    string line, county, state;
    int index, pop;

    // file.open("counties_list.csv", ios::in);
    file.open("counties_ten.csv", ios::in);

    // Create a new list of county pointers
    List<County *> list;
    County *newCounty;

    if (file.good())
    {
        while (getline(file, line, ','))
        {
            temp.clear();
            temp.str(line);
            temp >> index;

            getline(file, line, ',');
            county = line;

            getline(file, line, ',');
            state = line;

            getline(file, line, '\n');
            temp.clear();
            temp.str(line);
            temp >> pop;

            newCounty = new County(index, county, state, pop);

            // Append newCounty to your list
            list.append(newCounty);
        }
    }

    file.close();

    // Call mergesort()

    // Print the list
    list.print();

    return 0;
};