#ifndef LIST_H
#define LIST_H

/* Include the header for the County class. This also doubles as a general purpose
   header for all the relevant std::c++ libraries */
#include "County.h"
using namespace std;

/* LIST CLASS AND FUNCTION DEFINITIONS */
/* The County object class has multiple variables of different types (ints and strings).
   This template ensures that the functions in the list can handle objects with multiple
   variable types */
template <class T>
class List
{
    /* Private data members. These pointers and functions are available only to the
       other variables and functions in this class. They cannot be accessed by functions
       in other classes or the driver */
private:
    /* A structure to create the individual list nodes */
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

        /* Exit case for when the next node in the sublist is invalid */
        if (!inc->next)
            return nullptr;

        /* Check to see if the incrementing node or its next node is pointing to the
           same node as the decrementing node */
        while (inc != dec && inc->next != dec)
        {
            /* Increment and decrement the respective nodes */
            inc = inc->next;
            dec = dec->prev;
        }

        /* Once the traversal is terminated, set the midpoint of the sublist to the
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
        /* Initalize a pointer to a sorted sublist */
        listNode *sorted;

        /* An exit case for if the lower bound is null */
        if (!left)
            return right;

        /* An exit case for if the upper bound is null */
        if (!right)
            return left;

        /* A comparison operation between the left and right sublist values */
        if (*(left->value) > *(right->value))
        {
            /* If the left value is greater than the right value, set the pointer to
               the sorted sublist to the left node. Then, continue the merge call until
               the next pointer for the sorted sublist reaches the pointer to the right
               sublist */
            sorted = left;
            sorted->next = merge(left->next, right);
            sorted->next->prev = sorted;
        }
        else
        {
            /* If the right value is greater than the left value, set the pointer to
               the sorted sublist to the right node. Then, continue the merge call until
               the next pointer for the sorted sublist reaches the pointer to the tail */
            sorted = right;
            sorted->next = merge(left, right->next);
            sorted->next->prev = sorted;
        }

        /* Once the merge loop is terminated, return the sorted sublists */
        return sorted;
    };

    /* The main body of the mergeSort call */
    typename List<T>::listNode *mergeSort(listNode *start, listNode *end)
    {
        /* Check to see if the list is empty or has only one element */
        if (!start || !start->next)
            return start;

        /* Initialize pointers to the midpoint, a left sublist, and a right sublist.
           Recursively call the mergeSort function to perform a split on both sublists
           until each of them reach a null value. At that point, both sublists are
           sorted */
        listNode *mid = split(start, end);
        listNode *left = mergeSort(start, mid->prev);
        listNode *right = mergeSort(mid, end);

        /* Calls the merge function to combine both sorted sublists */
        return merge(left, right);
    };

    /* Swap function for swapping two nodes in the linked list. This function swaps
       the positions of two nodes in the list. It also updates the next and prev
       pointers of adjacent nodes. */
    void swap(listNode *a, listNode *b)
    {
        /* Check to see if pointers are not consecutive nodes */
        if (a->next != b)
        {
            /* If they aren't, swap the next pointers so that they are pointing to
               each other */
            listNode *tempNext = a->next;
            a->next = b->next;
            b->next = tempNext;
        }
        else
            a->next = b->next;

        /* If b's next node is valid, update the prev node of the node that follows
           b to point back to b */
        if (b->next)
            b->next->prev = b;

        /* If a's next node is valid, update the prev node of the node that follows
           a to point back to a */
        if (a->next)
            a->next->prev = a;

        /* Check to see if pointers are not consecutive nodes */
        if (a->prev != b)
        {
            /* If they aren't swap the prev pointers so that they are pointing to
               each other */
            listNode *tempPrev = a->prev;
            a->prev = b->prev;
            b->prev = tempPrev;
        }
        else
            a->prev = b->prev;

        /* If b's prev node is valid, update the next node of the node that precedes
           b to point forward to b */
        if (b->prev)
            b->prev->next = b;

        /* If a's prev node is valid, update the next node of the node that precedes
           a to point forward to a */
        if (a->prev)
            a->prev->next = a;

        /* Finally, swap the stored values for each node to complete the swap */
        T tempValue = a->value;
        a->value = b->value;
        b->value = tempValue;
    };

    /* Public data members. These can be freely used by other files and functions like
       the main function, for instance */
public:
    /* List constructor. Initializes the head and tail to null addresses */
    List() : head(nullptr), tail(nullptr){};
    /* List destructor */
    ~List()
    {
        /* Initialize a current node pointer set to the head as well as a pointer
           to the next node */
        listNode *node = head;
        listNode *next;

        /* Check to see that the current node is valid and continue the loop until
           the list traversal terminates */
        while (node)
        {
            /* Set the pointer to the next node to the current node's next value.
               Delete the node itself as well as the value of the node to avoid
               memory leaks. Then, set the current node pointer to the next pointer
               to move forward */
            next = node->next;
            delete node->value;
            delete node;
            node = next;
        }

        /* Once the list is destroyed, the program is terminated; this message serves
           as a sign of good faith that the list was properly deallocated */
        cout << "\nGOODBYE!\n";
        cout << endl;
    };

    /* Wrapper function for the print function. The data member for the head is
       inaccessible to main, so this function initializes the private print function
       with the head to begin the list traversal */
    void print() { print(head); };

    /* List append function. Adds a node to the end of the list and accepts a
       templated county value as an argument */
    void append(T value)
    {
        /* Initializes a pointer to to a node that will be used to traverse the list
           and allocates memory for a new node */
        listNode *node = new listNode(value);

        /* Check to see if the list is empty */
        if (!head)
        {
            /* If the list is empty, set the current node to both the head and the
               tail */
            head = node;
            tail = node;
        }
        else
        {
            /* If the list has a valid tail, the next pointer for the tail is set to the
               current node pointer, the prev pointer for the current node is set to the
               tail, and the tail is finally set to the current node. This is similar to
               a swap function but uses recently allocated memory to complete the swap */
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    };

    /* Public mergeSort function for initializing the merge sort. This function serves
       as a wrapper to start the sorting process */
    void mergeSort()
    {
        /* Initialize a pointer to the current node */
        listNode *node;

        /* Call the private mergeSort function to recursively sort the list */
        head = mergeSort(head, tail);

        /* Find the new tail of the sorted list */
        node = head;

        while (node->next)
            node = node->next;

        tail = node;
    };

    /* SelectionSort function for sorting the linked list in-place. This function
       traverses the list and, for each element, finds the minimum element in the
       remaining unsorted portion and swaps them if necessary */
    void selectionSort()
    {
        /* Initialize the current node to the head of the list */
        listNode *node = head;

        while (node)
        {
            listNode *min = node;
            listNode *temp = node->next;

            /* Find the minimum element in the remaining unsorted portion */
            while (temp)
            {
                if (*(temp->value) < *(min->value))
                    min = temp;

                temp = temp->next;
            }

            /* Swap the current element with the minimum element if needed */
            if (min != node)
            {
                T tempValue = node->value;
                node->value = min->value;
                min->value = tempValue;
            }

            /* Continue the traversal until the loop terminates */
            node = node->next;
        }
    };

    /* Outfile function. Writes the elements in the list to a file with the given
       filename */
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

    /* List size function. It accepts a current node as an argument, traverses the
       list from that node, and returns the size of that list expressed as an integer.
       This was very useful for debugging! */
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