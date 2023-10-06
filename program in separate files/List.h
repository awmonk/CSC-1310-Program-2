#ifndef LIST_H
#define LIST_H

#include "County.h"
using namespace std;

template <class T>
class List
{
private:
    /* Struct class for the list nodes */
    struct listNode
    {
        /* Template variable to hold the value of the nodes */
        T value;
        /* Pointers to the nodes' next and previous node */
        listNode *next;
        listNode *prev;
        /* Constructor for the node with the value set to a placeholder value and the
           next and prev pointers set to null */
        listNode(T value) : value(value), next(nullptr), prev(nullptr){};
    };
    /* Pointers to the head and tail of the list */
    listNode *head;
    listNode *tail;

    /* Private print function with a pointer to the current node as an argument */
    void print(listNode *node)
    {
        cout << "\n";

        /* Exit case for when the node is null */
        if (!node)
            return;

        /* Display the dereferenced value in the terminal */
        cout << *(node->value);

        /* Recursive case to traverse to the next node */
        print(node->next);
    };

    /* Split function for mergeSort with a pointer to the head and tail of the
       sublist as arguments */
    typename List<T>::listNode *split(listNode *left, listNode *right)
    {
        /* Initialize pointers to an incrementing node, a decrementing node, and a
           middle node to return as the output */
        listNode *inc = left;
        listNode *dec = right;
        listNode *mid;

        /* Exit case for when the next node in the sublist is null */
        if (!inc->next)
            return nullptr;

        /* Check to see if the incrementing node or its next node is pointint to the
           same node as the decrementing node */
        while (inc != dec && inc->next != dec)
        {
            /* Increment and decrement the respective nodes */
            inc = inc->next;
            dec = dec->prev;
        }

        /* Once the traversal is complete, set the midpoint of the sublist to the
           next node that the incrementing node is pointing to and sever the sublist */
        mid = inc->next;
        inc->next = nullptr;

        /* Return the midpoint */
        return mid;
    };

    /* Merge function for mergeSort with a pointer to the left and right sublists as
       arguments */
    typename List<T>::listNode *merge(listNode *left, listNode *right)
    {
        /*  */
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

    /*  */
    typename List<T>::listNode *mergeSort(listNode *start, listNode *end)
    {
        if (!start || !start->next)
            return start;

        listNode *mid = split(start, end);
        listNode *left = mergeSort(start, mid->prev);
        listNode *right = mergeSort(mid, end);

        return merge(left, right);
    };

    void swap(listNode *a, listNode *b)
    {
        if (a->next != b)
        {
            listNode *tempNext = a->next;
            a->next = b->next;
            b->next = tempNext;
        }
        else
            a->next = b->next;

        if (b->next)
            b->next->prev = b;

        if (a->next)
            a->next->prev = a;

        if (a->prev != b)
        {
            listNode *tempPrev = a->prev;
            a->prev = b->prev;
            b->prev = tempPrev;
        }
        else
            a->prev = b->prev;

        if (b->prev)
            b->prev->next = b;

        if (a->prev)
            a->prev->next = a;

        T tempValue = a->value;
        a->value = b->value;
        b->value = tempValue;
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

    void selectionSort()
    {
        listNode *node = head;

        while (node)
        {
            listNode *min = node;
            listNode *temp = node->next;

            while (temp)
            {
                if (*(temp->value) < *(min->value))
                    min = temp;

                temp = temp->next;
            }

            if (min != node)
            {
                T tempValue = node->value;
                node->value = min->value;
                min->value = tempValue;
            }

            node = node->next;
        }
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