#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
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
        listNode(T value) : value(value), next(nullptr), prev(nullptr) {}
    };
    listNode *head;
    listNode *tail;

    void print(listNode *node);
    listNode *split(listNode *left, listNode *right);
    listNode *merge(listNode *left, listNode *right);
    listNode *mergeSort(listNode *start, listNode *end);

public:
    List() : head(nullptr), tail(nullptr) {}
    ~List();
    void print();
    void append(T value);
    void mergeSort();
    void swap(listNode *node1, listNode *node2);
    int getSize();
};

int main()
{
    ifstream infile;
    stringstream temp;
    string line, county, state;
    int index, pop;

    infile.open("counties_ten.csv", ios::in);

    List<County> list;

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

            County newCounty(index, county, state, pop);
            list.append(newCounty);
        }
    }
    infile.close();

    cout << "\nCALLING MERGESORT\n";
    list.mergeSort();

    cout << "\nSORTED LIST\n";
    list.print();

    return 0;
};

County::County(int i, string n, string s, int p)
    : index(i), name(n), state(s), population(p) {}
int County::getIndex() { return index; }
int County::getPopulation() { return population; }
void County::setIndex(int i) { index = i; }
bool County::operator<(const County &c) { return population < c.population; }
bool County::operator>(const County &c) { return population > c.population; }

template <class T>
List<T>::~List()
{
    listNode *current = head;
    while (current != nullptr)
    {
        listNode *next = current->next;
        delete current;
        current = next;
    }
};

template <class T>
void List<T>::print(listNode *node)
{
    if (node == nullptr)
        return;

    cout << node->value << "\n";
    print(node->next);
};

template <class T>
void List<T>::print()
{
    print(head);
};

template <class T>
typename List<T>::listNode *List<T>::split(listNode *start, listNode *end)
{
    if (start == nullptr || end == nullptr || start == end)
        return start;

    listNode *inc = start;
    listNode *dec = end;
    listNode *mid = nullptr;

    while (inc != dec->next && dec != inc->prev)
    {
        inc = inc->next;
        dec = dec->prev;
    }

    if (inc == dec->next)
    {
        mid = inc;
        inc = mid->next;
        mid->next = nullptr;

        if (inc)
            inc->prev = nullptr;
    }

    return mid;
}

template <class T>
typename List<T>::listNode *List<T>::merge(listNode *start, listNode *end)
{
    listNode *sorted = nullptr;
    if (start == nullptr)
        return end;

    if (end == nullptr)
        return start;

    if (start->value < end->value)
    {
        sorted = start;
        sorted->next = merge(start->next, end);
        sorted->next->prev = sorted;
    }
    else
    {
        sorted = end;
        sorted->next = merge(start, end->next);
        sorted->next->prev = sorted;
    }
    return sorted;
};

template <class T>
typename List<T>::listNode *List<T>::mergeSort(listNode *start, listNode *end)
{
    if (start == nullptr || start->next == nullptr)
        return start;

    listNode *mid = split(start, end);
    listNode *left = mergeSort(start, mid);
    listNode *right = mergeSort(mid, end);

    return merge(left, right);
};

template <class T>
void List<T>::append(T value)
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

template <class T>
void List<T>::mergeSort()
{
    listNode *node;

    head = mergeSort(head, tail);
    node = head;

    while (node->next != nullptr)
        node = node->next;

    tail = node;
};

template <class T>
int List<T>::getSize()
{
    int index = 0;
    listNode *node = head;
    while (node != nullptr)
    {
        node = node->next;
        index++;
    }
    return index;
};

template <class T>
void List<T>::swap(listNode *node1, listNode *node2)
{
    if (node1 == nullptr || node2 == nullptr || node1 == node2)
        return;

    // Check if the nodes are adjacent
    if (node1->next == node2 || node2->next == node1)
    {
        listNode *prevNode1 = node1->prev;
        listNode *prevNode2 = node2->prev;

        // Swap next pointers
        if (prevNode1 != nullptr)
            prevNode1->next = node2;
        else
            head = node2;

        if (prevNode2 != nullptr)
            prevNode2->next = node1;
        else
            head = node1;

        listNode *temp = node1->next;
        node1->next = node2->next;
        node2->next = temp;

        // Update prev pointers
        if (node1->next != nullptr)
            node1->next->prev = node1;
        if (node2->next != nullptr)
            node2->next->prev = node2;

        // Update prev pointers of swapped nodes
        node1->prev = prevNode2;
        node2->prev = prevNode1;

        // Update tail if necessary
        if (node1 == tail)
            tail = node2;
        else if (node2 == tail)
            tail = node1;
    }
}
