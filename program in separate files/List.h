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
        int index;
        T value;
        listNode *next;
        listNode *prev;

        /* Constructor for the listNode. Inline arguments set the object type T to
           the value passed in through input stream, sets the index to a self-
           referencing index value, and initializes the next and prev pointers to
           null pointers. It then displays a message for each node that is created
           as well as their index value */
        listNode(T value, int index)
            : value(value), index(index), next(nullptr), prev(nullptr)
        {
            cout << "Creating node " << index << ".\n";
        }
        /* Destructor. Deletes the value in each node and displays a message for
           each node that is destroyed as well as their index value. */
        ~listNode()
        {
            cout << "Destroying node " << index << ".\n";
            delete value;
        }
    };
    /* Initializing variables for the index of each node, a pointer to the head
       of the list, and a pointer to the tail of the list */
    int index;
    listNode *head;
    listNode *tail;

    /* The strategy you should take for this function is to do a double traversal,
       one from each end, and they will meet at the middle node. This means that
       you’ll have a reference to the middle node that you can return, but first
       you must set the next pointer for that node to null before you return it.
       This will sever the two partitions from each other, which you need for
       checking your base case. Once you have severed these nodes, return the first
       node after where the list was severed (the node that would otherwise have been
       pointed to by the middle node). */
    typename List<T>::listNode *split(listNode *head, listNode *tail){

    };

    /* Overloaded merge function for nodes called in the mergeSort. This is a private
       function as it is only ever called by the mergeSort */
    typename List<T>::listNode *merge(listNode *l, listNode *r){

    };
    /* The base case is when the list partition is either zero or one node, in which
       case the function will return the first parameter (which is either the only
       element or null). In the recursive case, you will need to make two node
       references for a placeholder, which will be the first element of each list
       partition. The first of these two will be the first parameter for the function,
       and the second will be the node that’s returned by the split function. Then
       both of the recursive calls are made, passing the lower and upper bound of both
       list partitions, and sending the node that’s returned to our two placeholder
       nodes. Finally, the function calls merge and returns the node that’s passed
       from the merge function. */
    typename List<T>::listNode *mergeSort(listNode *head, listNode *tail)
    {
        if (head == nullptr)
            return head;
        if (head->next == nullptr)
            return head;
        listNode *first, *second;

        second = split(first, second);
        mergeSort(first, second);
    };

public:
    /* List constructor. Inline arguments initialize the head and tail to null
       pointers and sets the index to 1. */
    List() : head(nullptr), tail(nullptr), index(1)
    {
        cout << "Creating list.\n";
    }
    /* List destructor. The list is traversed using a pointer to point to the
       current node and a pointer to point the the next node in the list. It
       then decrements throught the list, deleting each node along the way and
       impplicitly calling the listNode destructor until it reaches a null pointer.
       At that point it will know that the list is empty and display a final
       message. */
    ~List()
    {
        cout << "Destroying list.\n";
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
    /* A void print function that calls the overloaded pring function using the head
       as the node pointer for its argument */
    void print()
    {
        print(head);
        cout << "\n";
    };
    /* An overloaded print function that recursively iterates through each node in
       the list and returns a message with a dereferenced pointer as the output. The
       final call is made when the node pointer is null */
    void print(listNode *node)
    {
        cout << "\n";
        if (node == nullptr)
            return;
        cout << *(node->value);
        print(node->next);
    };
    /* An append function that adds new nodes to the list each time it is called. */
    void append(T value)
    {
        listNode *node = new listNode(value, index);
        index++;
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
    /* This function calls to other mergeSort function, passing head and tail as
       arguments. Resetting head and tail is tricky to do recursively, so when mergeSort
       is finished this function sets the new head and tail reference. The other merge
       sort function returns the head of its merged list partitions. Since the last
       iteration returns the front, that node needs to be our new head. From the head
       we can traverse the list to find where the new tail is. */
    void mergeSort()
    {
        mergeSort(head, tail);
    };
};

#endif