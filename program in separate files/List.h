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
        listNode(T value) : value(value), next(nullptr), prev(nullptr){};
    };
    listNode *head;
    listNode *tail;

    void print(listNode *node)
    {
        cout << "\n";

        if (!node)
            return;

        cout << *(node->value);

        print(node->next);
    };

    typename List<T>::listNode *split(listNode *left, listNode *right)
    {
        listNode *inc = left;
        listNode *dec = right;
        listNode *mid;

        if (!inc->next)
            return nullptr;

        while (inc != dec && inc->next != dec)
        {
            inc = inc->next;
            dec = dec->prev;
        }

        mid = inc->next;
        inc->next = nullptr;

        return mid;
    };

    typename List<T>::listNode *merge(listNode *left, listNode *right)
    {
        listNode *sorted;

        if (!left)
            return right;

        if (!right)
            return left;

        if (*(left->value) > *(right->value))
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

    typename List<T>::listNode *mergeSort(listNode *start, listNode *end)
    {
        if (!start || !start->next)
            return start;

        listNode *mid = split(start, end);
        listNode *left = mergeSort(start, mid->prev);
        listNode *right = mergeSort(mid, end);

        return merge(left, right);
    };

public:
    List() : head(nullptr), tail(nullptr){};
    ~List()
    {
        listNode *node = head;
        listNode *next;

        while (node)
        {
            next = node->next;
            delete node;
            node = next;
        }

        cout << "\nGOODBYE!\n";
        cout << endl;
    };

    void print() { print(head); };

    void append(T value)
    {
        listNode *node = new listNode(value);

        if (!head)
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
        listNode *node;

        head = mergeSort(head, tail);
        node = head;

        while (node->next)
            node = node->next;

        tail = node;
    };

    void outfile(const string &filename)
    {
        ofstream outfile(filename);
        listNode *node = head;

        while (node)
        {
            outfile << *(node->value) << "\n";
            node = node->next;
        }

        outfile.close();
    };

    int getSize(listNode *node)
    {
        int index = 0;

        while (node)
        {
            node = node->next;
            index++;
        }

        return index;
    };
};

#endif