#include <iostream>
using namespace std;

// Doubly linked list node class.
class Node
{
public:
    int data;
    Node *next, *prev;

    // Constructor.
    Node(int data) : data(data), next(nullptr), prev(nullptr){};
};

// This function divides the linked list into two parts and returns the head of second half.
Node *split(Node *head)
{
    Node *slowPointer = head;
    Node *fastPointer = head;
    while (fastPointer != nullptr && fastPointer->next != nullptr &&
           fastPointer->next->next != nullptr)
    {
        fastPointer = fastPointer->next->next;
        slowPointer = slowPointer->next;
    }
    Node *secondHalf = slowPointer->next;

    // Separating the second part.
    slowPointer->next = nullptr;
    return secondHalf;
}

// This function will merge two lists and will return the sorted list.
Node *merge(Node *firstList, Node *secondList)
{
    // If the 'firstList' linked list is empty, then we dont have to merge.
    if (firstList == nullptr)
        return secondList;

    // If the 'secondList' linked list is empty, then don’t have to merge.
    if (secondList == nullptr)
        return firstList;

    // Regular merge conditions.
    if (firstList->data > secondList->data)
    {
        secondList->next = merge(firstList, secondList->next);
        secondList->next->prev = secondList;
        secondList->prev = nullptr;
        return secondList;
    }
    else
    {
        firstList->next = merge(firstList->next, secondList);
        firstList->next->prev = firstList;
        firstList->prev = nullptr;
        return firstList;
    }
}

// It returns the sorted doubly linked list.
Node *mergeSort(Node *head)
{
    if (head == nullptr)
        return head;

    if (head->next == nullptr)
        return head;

    Node *firstList = nullptr, *secondList = nullptr;
    // Splitting the list.
    secondList = split(head);

    // Recursively calling merge sort on both the sublists.
    firstList = mergeSort(head);
    secondList = mergeSort(secondList);

    // Merging the two sorted sub lists.
    Node *sortedList = merge(firstList, secondList);
    return sortedList;
}

// Print function.
void print(Node *head)
{
    Node *temp = head;
    while (temp != nullptr)
    {
        cout << temp->data << " ";
        temp = temp->next;
    }
}

// Main function.
int main()
{
    int n;
    cout << "Enter the number of elements in the list: ";
    cin >> n;

    cout << "Enter the elements: ";
    Node *head = nullptr, *tail = nullptr;

    for (int i = 0; i < n; i++)
    {
        int data;
        cin >> data;
        Node *newNode = new Node(data);
        if (i == 0)
        {
            head = tail = newNode;
        }
        else
        {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    cout << "Sorted list: ";

    // Calling the 'mergeSort()' function to sort the doubly linked list.
    head = mergeSort(head);

    // Printing the final list.
    print(head);
    return 0;
}