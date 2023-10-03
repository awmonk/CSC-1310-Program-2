#include <iostream>
#include <iomanip>
#include <string>
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
    int getSize();
    void print();
    void append(T value);
    void mergeSort();
    void swap(listNode *node1, listNode *node2);
    void selectionSort();
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
    listNode *node = head;
    listNode *next;

    while (node != nullptr)
    {
        next = node->next;
        delete node;
        node = next;
    }

    cout << "\nGOODBYE!\n";
    cout << endl;
};

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
void List<T>::print() { print(head); };

template <class T>
typename List<T>::listNode *List<T>::split(listNode *start, listNode *end)
{
    listNode *slow = start;
    listNode *fast = start;
    listNode *mid;

    while (fast->next && fast->next->next)
    {
        slow = slow->next;
        fast = fast->next->next;
    }

    mid = slow->next;
    slow->next = nullptr;

    return mid;
}

template <class T>
typename List<T>::listNode *List<T>::merge(listNode *left, listNode *right)
{
    if (!left)
        return right;

    if (!right)
        return left;

    if (left->value > right->value)
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

template <typename T>
void List<T>::selectionSort()
{
    listNode *node = head;
    listNode *min;
    listNode *temp;

    while (node)
    {
        min = node;
        temp = node->next;

        while (temp)
        {
            if (temp->value < min->value)
                min = temp;

            temp = temp->next;
        }

        swap(node, min);
        node = node->next;
    }
}

template <typename T>
void List<T>::swap(listNode *node1, listNode *node2)
{
    listNode *temp;
    listNode *temp1;
    listNode *temp2;

    if (node1 == node2)
        return;

    if (node1->next == node2)
    {
        temp = node2->next;
        node2->next = node1;
        node1->next = temp;
        node2->prev = node1->prev;
        node1->prev = node2;

        if (node2->prev)
            node2->prev->next = node2;

        if (node1->next)
            node1->next->prev = node1;
    }
    else if (node2->next == node1)
    {
        swap(node2, node1);
    }
    else
    {
        temp1 = node1->next;
        temp2 = node1->prev;
        node1->next = node2->next;
        node1->prev = node2->prev;
        node2->next = temp1;
        node2->prev = temp2;

        if (node1->next)
            node1->next->prev = node1;

        if (node1->prev)
            node1->prev->next = node1;

        if (node2->next)
            node2->next->prev = node2;

        if (node2->prev)
            node2->prev->next = node2;
    }
}