#ifndef LIST_H
#define LIST_H

#include "County.h"
using namespace std;

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
    typename List<T>::listNode *mergeSort(listNode *start, listNode *end);

public:
    List();
    ~List();
    void print();
    void append(T value);
    void mergeSort();
};

#endif