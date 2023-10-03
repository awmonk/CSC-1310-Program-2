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
        ~listNode() { delete value; };
    };
    listNode *head;
    listNode *tail;

    void print(listNode *node)
    {
        cout << "\n";
        if (node == nullptr)
            return;

        cout << node->value;
        print(node->next);
    };

    listNode *split(listNode *left, listNode *right)
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

    listNode *merge(listNode *left, listNode *right)
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

    listNode *mergeSort(listNode *start, listNode *end)
    {
        if (start == nullptr || start->next == nullptr)
            return start;

        listNode *mid = split(start, end);
        listNode *left = mergeSort(start, mid);
        listNode *right = mergeSort(mid, end);

        return merge(left, right);
    };

public:
    List() : head(nullptr), tail(nullptr){};
    ~List()
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

    void print() { print(head); };

    void append(T value)
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

    void mergeSort()
    {
        listNode *current;
        head = mergeSort(head, tail);
        current = head;

        while (current->next != nullptr)
            current = current->next;

        tail = current;
    };

    void outfile(const string &filename)
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
    };
};

#endif