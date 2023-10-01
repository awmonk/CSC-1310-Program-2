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

        /* Constructor for the listNode. Inline arguments set the object type T to
           the value passed in through input stream, sets the index to a self-
           referencing index value, and initializes the next and prev pointers to
           null pointers. It then displays a message for each node that is created
           as well as their index value */
        listNode(T value)
            : value(value), next(nullptr), prev(nullptr) {}
        /* Destructor. Deletes the value in each node and displays a message for
           each node that is destroyed as well as their index value. */
        ~listNode() { delete value; }
        /* Initializing variables for the index of each node, a pointer to the head
           of the list, and a pointer to the tail of the list */
    };
    listNode *head;
    listNode *tail;
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
    /* The strategy you should take for this function is to do a double traversal,
       one from each end, and they will meet at the middle node. This means that
       you’ll have a reference to the middle node that you can return, but first
       you must set the next pointer for that node to null before you return it.
       This will sever the two partitions from each other, which you need for
       checking your base case. Once you have severed these nodes, return the first
       node after where the list was severed (the node that would otherwise have been
       pointed to by the middle node). */
    typename List<T>::listNode *split(listNode *left, listNode *right)
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
    /* Overloaded merge function for nodes called in the mergeSort. This is a private
       function as it is only ever called by the mergeSort */
    typename List<T>::listNode *merge(listNode *left, listNode *right)
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
    typename List<T>::listNode *mergeSort(listNode *start, listNode *end)
    {
        /* Base case: If the list is empty or has only one element, return it. */
        if (start == nullptr || start->next == end)
            return start;

        listNode *left = nullptr;
        listNode *right = nullptr;
        listNode *mid = nullptr;

        mid = split(start, end);

        /* Check if mid is not null before making recursive calls. */
        if (mid != nullptr)
        {
            left = mergeSort(start, mid->prev);
            right = mergeSort(mid, end);
        }

        return merge(left, right);
    };

public:
    /* List constructor. Inline arguments initialize the head and tail to null
       pointers and sets the index to 1. */
    List() : head(nullptr), tail(nullptr) {}
    /* List destructor. The list is traversed using a pointer to point to the
       current node and a pointer to point the the next node in the list. It
       then decrements throught the list, deleting each node along the way and
       impplicitly calling the listNode destructor until it reaches a null pointer.
       At that point it will know that the list is empty and display a final
       message. */
    ~List()
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
    /* A wrapper print function that calls the overloaded pring function using the head
       as the node pointer for its argument */
    void print()
    {
        print(head);
    };
    /* An append function that adds new nodes to the list each time it is called. */
    void append(T value)
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
    /* This function calls to other mergeSort function, passing head and tail as
       arguments. Resetting head and tail is tricky to do recursively, so when mergeSort
       is finished this function sets the new head and tail reference. The other merge
       sort function returns the head of its merged list partitions. Since the last
       iteration returns the front, that node needs to be our new head. From the head
       we can traverse the list to find where the new tail is. */
    void mergeSort()
    {
        head = mergeSort(head, tail);
        listNode *current = head;
        while (current != nullptr && current->next != nullptr)
        {
            current->next->prev = current;
            current = current->next;
        }
        tail = current;
    };
};

#endif