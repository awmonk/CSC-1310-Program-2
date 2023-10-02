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

        listNode(T value);
        ~listNode();
    };
    listNode *head;
    listNode *tail;

    void print(listNode *node);
    typename List<T>::listNode *split(listNode *left, listNode *right);
    typename List<T>::listNode *merge(listNode *left, listNode *right);
    typename List<T>::listNode *mergesort(listNode *start, listNode *end);

public:
    List();
    ~List();
    void print();
    void append(T value);
    void mergesort();
    void outfile(const string &filename);
};

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
            // Append newCounty to your list
            list.append(newCounty);
        }
    }
    infile.close();

    // Call mergesort
    cout << "\nCALLING MERGESORT\n";
    list.mergesort();

    // Write to external file
    list.outfile("sorted_counties.txt");

    // Print the list
    cout << "\nSORTED LIST\n";
    list.print();

    return 0;
};

/* County functions */
County::County(int i, string n, string s, int p)
    : index(i), name(n), state(s), population(p){};
int County::getIndex() { return index; };
int County::getPopulation() { return population; };
void County::setIndex(int i) { index = i; };
bool County::operator<(const County &c) { return population < c.population; };
bool County::operator>(const County &c) { return population > c.population; };

/* List functions */
/* Private functions */
// Node constructor
template <class T>
List<T>::listNode::listNode(T value)
    : value(value), next(nullptr), prev(nullptr){};

// Node destructor
template <class T>
List<T>::listNode::~listNode() { delete value; };

// Private print
template <class T>
void List<T>::print(listNode *node)
{
    cout << "\n";
    if (node == nullptr)
        return;
    cout << *(node->value);
    print(node->next);
};

// mergesort split
template <class T>
typename List<T>::listNode *List<T>::split(listNode *left, listNode *right)
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

// mergesort merge
template <class T>
typename List<T>::listNode *List<T>::merge(listNode *left, listNode *right)
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

// mergesort private
template <class T>
typename List<T>::listNode *List<T>::mergesort(listNode *start, listNode *end)
{
    if (start == nullptr || start->next == end)
        return start;

    listNode *left = nullptr;
    listNode *right = nullptr;
    listNode *mid = nullptr;

    mid = split(start, end);

    if (mid != nullptr)
    {
        left = mergesort(start, mid->prev);
        right = mergesort(mid, end);
    }

    return merge(left, right);
};

/* Public functions */
// List constructor
template <class T>
List<T>::List() : head(nullptr), tail(nullptr) {}

// List destructor
template <class T>
List<T>::~List()
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

// Public print (wrapper)
template <class T>
void List<T>::print() { print(head); };

// List append
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

// mergesort public (wrapper)
template <class T>
void List<T>::mergesort()
{
    listNode *current;
    head = mergesort(head, tail);
    current = head;
    while (current != nullptr && current->next != nullptr)
    {
        current->next->prev = current;
        current = current->next;
    }
    tail = current;
};

template <class T>
void List<T>::outfile(const string &filename)
{
    ofstream outfile(filename);
    if (!outfile.is_open())
    {
        cerr << "Error opening the file for writing." << endl;
        return;
    }

    listNode *current = head;
    while (current != nullptr)
    {
        outfile << *(current->value) << endl;
        current = current->next;
    }

    outfile.close();
}

#endif