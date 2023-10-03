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

/* LIST PROTOTYPES AND VARIABLES */
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
    List();
    ~List();
    void print();
    void append(T value);
    void mergeSort();
    void outfile(const string &filename);
};

/* DRIVER */
int main()
{
    ifstream infile;
    stringstream temp;
    string line, county, state;
    int index, pop;

    infile.open("counties_list.csv", ios::in);
    // infile.open("counties_ten.csv", ios::in);

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

    cout << "\nWRITING TO FILE (mergesort.txt)\n";
    list.outfile("mergesort.txt");

    cout << "\nSORTED LIST\n";
    list.print();

    return 0;
}

/* COUNTY DEFINITIONS */
County::County(int i, string n, string s, int p)
    : index(i), name(n), state(s), population(p){};
int County::getIndex() { return index; };
int County::getPopulation() { return population; };
void County::setIndex(int i) { index = i; };
bool County::operator<(const County &c) { return population < c.population; };
bool County::operator>(const County &c) { return population > c.population; };

/* LIST DEFINITIONS */
/* Public definitions */
template <class T>
List<T>::List() : head(nullptr), tail(nullptr){};

template <class T>
List<T>::~List()
{
    listNode *current = head;
    listNode *next;
    while (current != nullptr)
    {
        next = current->next;
        delete current;
        current = next;
    }
    cout << "\nGOODBYE!\n";
    cout << endl;
};

template <class T>
void List<T>::print()
{
    print(head);
};

template <class T>
void List<T>::append(T value)
{
    listNode *newNode = new listNode(value);
    if (head == nullptr)
    {
        head = newNode;
        tail = newNode;
    }
    else
    {
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
};

template <class T>
void List<T>::mergeSort()
{
    head = mergeSort(head, tail);
    listNode *current = head;
    while (current->next != nullptr)
        current = current->next;

    tail = current;
};

template <class T>
void List<T>::outfile(const string &filename)
{
    ofstream outfile(filename);
    if (!outfile.is_open())
    {
        cerr << "Error opening the file for writing.\n";
        return;
    }

    listNode *current = head;
    while (current != nullptr)
    {
        outfile << current->value << "\n";
        current = current->next;
    }

    outfile.close();
}

/* Private definitions */
template <class T>
void List<T>::print(listNode *node)
{
    cout << "\n";
    if (node == nullptr)
        return;

    cout << node->value;
    print(node->next);
};

template <class T>
typename List<T>::listNode *List<T>::split(listNode *left, listNode *right)
{
    if (left == nullptr || left->next == nullptr)
        return left;

    listNode *slow = left;
    listNode *fast = left->next;

    while (fast != nullptr)
    {
        fast = fast->next;
        if (fast != nullptr)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    listNode *mid = slow->next;
    slow->next = nullptr;
    return mid;
};

template <class T>
typename List<T>::listNode *List<T>::merge(listNode *left, listNode *right)
{
    listNode *sorted = nullptr;
    if (left == nullptr)
        return right;
    if (right == nullptr)
        return left;

    if (left->value > right->value)
    {
        sorted = left;
        sorted->next = merge(left->next, right);
        sorted->next->prev = sorted;
    }
    else
    {
        sorted = right;
        sorted->next = merge(left, right->next);
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