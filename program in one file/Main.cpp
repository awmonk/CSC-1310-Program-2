#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

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

template <class T>
class List
{
private:
    struct listNode
    {
        T value;
        listNode *next;
        listNode *prev;

        listNode(T value)
            : value(value), next(nullptr), prev(nullptr) {}
        ~listNode() { delete value; }
    };
    listNode *head;
    listNode *tail;
    void print(listNode *node)
    {
        cout << "\n";
        if (node == nullptr)
            return;
        cout << *(node->value);
        print(node->next);
    };
    typename List<T>::listNode *split(listNode *left, listNode *right)
    {
        if (left == nullptr || right == nullptr)
            return nullptr;

        listNode *inc = left;
        listNode *dec = right;
        listNode *prev = nullptr;

        while (inc != nullptr && inc != dec)
        {
            prev = inc;
            inc = inc->next;
            if (inc == dec)
                break;
            dec = dec->prev;
        }

        if (prev)
        {
            prev->next = nullptr;
            return inc;
        }

        return nullptr;
    };
    typename List<T>::listNode *merge(listNode *left, listNode *right)
    {
        if (left == nullptr)
            return right;
        if (right == nullptr)
            return left;
        if (left->value >= right->value)
        {
            left->next = merge(left->next, right);
            left->next->prev = left;
            left->prev = nullptr;
            return left;
        }
        else
        {
            right->next = merge(left, right->next);
            right->next->prev = right;
            right->prev = nullptr;
            return right;
        }
    };
    typename List<T>::listNode *mergeSort(listNode *start, listNode *end)
    {
        if (start == nullptr || start->next == end)
            return start;

        listNode *left = nullptr;
        listNode *right = nullptr;
        listNode *mid = nullptr;

        mid = split(start, end);

        if (mid != nullptr)
        {
            left = mergeSort(start, mid->prev);
            right = mergeSort(mid, end);
        }

        return merge(left, right);
    };

public:
    List() : head(nullptr), tail(nullptr) {}
    ~List()
    {
        listNode *node;
        listNode *next;
        node = tail;

        while (node != nullptr)
        {
            next = node->prev;
            delete node;
            node = next;
        }
        cout << "\nGOODBYE!\n";
        cout << endl;
    };
    void print()
    {
        print(head);
    };
    void append(T value)
    {
        listNode *node = new listNode(value);
        if (head == nullptr)
        {
            head = node;
            tail = node;
        }
        else
        {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    };
    void mergeSort()
    {
        head = mergeSort(head, tail);
        listNode *current = head;
        while (current != nullptr && current->next != nullptr)
        {
            current->next->prev = current;
            current = current->next;
        }
        tail = current;
    };
};

int main()
{
    ifstream infile;
    stringstream temp;
    string line, county, state;
    int index, pop;

    // infile.open("counties_list.csv", ios::in);
    infile.open("counties_ten.csv", ios::in);

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
            // Append newCounty to your list
            list.append(newCounty);
        }
    }
    infile.close();

    // Call mergesort()
    cout << "\nCALLING MERGESORT\n";
    list.mergeSort();

    // Print the list
    cout << "\nSORTED LIST\n";
    list.print();

    return 0;
};

County::County(int i, string n, string s, int p)
    : index(i), name(n), state(s), population(p){};
int County::getIndex() { return index; };
int County::getPopulation() { return population; };
void County::setIndex(int i) { index = i; };
bool County::operator<(const County &c) { return population < c.population; };
bool County::operator>(const County &c) { return population > c.population; };

#endif