#include "County.h"
#include "List.h"
using namespace std;

int main()
{
    ifstream infile;
    stringstream temp;
    string line, county, state;
    int index, pop;

    infile.open("counties_list.csv", ios::in);
    // infile.open("counties_ten.csv", ios::in);

    List<County *> list;
    County *newCounty;

    if (infile.good())
    {
        while (getline(infile, line, ','))
        {
            temp.clear();
            temp.str(line);
            temp >> index;

            getline(infile, line, ',');
            county = line;

            getline(infile, line, ',');
            state = line;

            getline(infile, line, '\n');
            temp.clear();
            temp.str(line);
            temp >> pop;

            newCounty = new County(index, county, state, pop);
            list.append(newCounty);
        }
    }
    infile.close();

    // Call mergesort
    cout << "\nCALLING MERGESORT\n";
    list.mergesort();

    // Write to external file
    cout << "\nWRITING TO FILE (sorted_counties.txt)\n";
    list.outfile("sorted_counties.txt");

    // Print the list
    cout << "\nSORTED LIST\n";
    list.print();

    return 0;
};