#ifndef MAIN_CPP
#define MAIN_CPP

#include <iostream>
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
        os << c.name << ", " << c.state << ": " << c.population;
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
        listNode(T value) : value(value), next(nullptr), prev(nullptr){};
        ~listNode() { delete value; };
    };
    listNode *head;
    listNode *tail;
    void split(List<T> &left, List<T> &right)
    {
        if (head == nullptr)
            return;

        listNode *mid = head;
        listNode *end = tail;

        while (end != nullptr && end->next != nullptr)
        {
            mid = mid->next;
            end = end->next->next;
        }

        left.head = head;
        left.tail = mid;
        right.head = mid->next;
        right.tail = tail;

        mid->next = nullptr;
    }

    listNode *merge(List<T> &l, List<T> &r)
    {
        listNode temp(nullptr);
        listNode *mergedTail = &temp;

        while (l.head != nullptr && r.head != nullptr)
        {
            if (*(l.head->value) < *(r.head->value))
            {
                mergedTail->next = l.head;
                l.head->prev = mergedTail;
                l.head = l.head->next;
            }
            else
            {
                mergedTail->next = r.head;
                r.head->prev = mergedTail;
                r.head = r.head->next;
            }
            mergedTail->next->prev = mergedTail;
            mergedTail = mergedTail->next;
        }

        if (l.head != nullptr)
        {
            mergedTail->next = l.head;
            l.head->prev = mergedTail;
        }
        else
        {
            mergedTail->next = r.head;
            r.head->prev = mergedTail;
        }

        return temp.next;
    }

public:
    List() : head(nullptr), tail(nullptr){};
    ~List()
    {
        listNode *nodePtr = head;
        while (nodePtr != nullptr)
        {
            listNode *nextNode = nodePtr->next;
            delete nodePtr;
            nodePtr = nextNode;
        }
    };
    void print()
    {
        print(head);
        cout << endl;
    };
    void print(listNode *nodePtr)
    {
        if (nodePtr == nullptr)
            return;
        cout << *(nodePtr->value) << endl;
        print(nodePtr->next);
    };
    void append(T value)
    {
        listNode *nodePtr = new listNode(value);
        if (head == nullptr)
        {
            head = nodePtr;
            tail = nodePtr;
        }
        else
        {
            tail->next = nodePtr;
            nodePtr->prev = tail;
            tail = nodePtr;
        }
    };
    void mergeSort()
    {
        if (head != nullptr && head->next != nullptr)
        {
            List<T> l;
            List<T> r;
            split(l, r);

            l.mergeSort();
            r.mergeSort();

            head = merge(l, r);
        }
    }
};

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
    list.mergeSort();
    // Print the list
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