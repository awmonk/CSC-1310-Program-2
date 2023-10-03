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
    int listSize(listNode *node);
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
typename List<T>::listNode *List<T>::split(listNode *left, listNode *right)
{
    cout << "\n==================================================\n\n";

    listNode *inc = left;
    listNode *dec = right;
    listNode *mid = nullptr;

    if (left == nullptr || right == nullptr)
        return nullptr;

    int headIndex = listSize(right);
    int tailIndex = listSize(left);

    cout << "Starting from: " << headIndex << " to " << tailIndex << "\n\n";

    print(dec);
    cout << "\n--------------------------------------------------\n";

    cout << "\nHead value: " << headIndex;
    cout << "\nTail value: " << tailIndex << "\n\n";

    while (inc != nullptr && inc != dec)
    {
        inc = inc->next;
        headIndex++;
        cout << "Incrementing head: ";
        cout << headIndex << "\n";

        dec = dec->prev;
        tailIndex--;
        cout << "Decrementing tail: ";
        cout << tailIndex << "\n\n";

        if (inc->next == dec)
            break;
    }

    mid = dec;
    inc = nullptr;

    cout << "Midpoint value: " << tailIndex << "\n";

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

    if (left->value < right->value)
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
    listNode *node;
    head = mergeSort(head, tail);
    node = head;
    while (node->next != nullptr)
        node = node->next;

    tail = node;
};

template <class T>
int List<T>::listSize(listNode *node)
{
    int index = 0;
    while (node != nullptr)
    {
        node = node->next;
        index++;
    }
    return index;
};