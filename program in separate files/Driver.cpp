#include "List.h"
using namespace std;

/* DRIVER */
int main()
{
    ifstream infile;
    stringstream temp;
    string line, county, state;
    int index, pop;

    infile.open("counties_list.csv", ios::in);
    // infile.open("counties_ten.csv", ios::in);

    List<County *> list;

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

            County *newCounty = new County(index, county, state, pop);
            list.append(newCounty);
        }
    }
    infile.close();

    cout << "\nCALLING MERGESORT\n";
    list.mergeSort();

    cout << "\nWRITING TO FILE (mergesort.txt)\n";
    list.outfile("mergesort.txt");

    cout << "\nSORTED LIST\n";
    list.print();

    cout << "\nCALLING SELECTION SORT\n";
    list.selectionSort();

    cout << "\nWRITING TO FILE (selectionsort.txt)\n";
    list.outfile("selectionsort.txt");

    cout << "\nREVERSED LIST\n";
    list.print();

    return 0;
};