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
    Node *slow = head;
    Node *fast = head;
    while (fast != nullptr && fast->next != nullptr &&
           fast->next->next != nullptr)
    {
        fast = fast->next->next;
        slow = slow->next;
    }
    Node *secondHalf = slow->next;

    // Separating the second part.
    slow->next = nullptr;
    return secondHalf;
}

Node *split(Node *head, Node *tail)
{
    Node *first = head;
    Node *second = tail;
    while (head->next != second->prev && head->next != nullptr &&
           second->prev != nullptr)
    {
        first = first->next;
        second = second->prev;
    }
    Node *secondHalf = second->prev;
    second->prev = nullptr;
    return secondHalf;
}

// This function will merge two lists and will return the sorted list.
Node *merge(Node *first, Node *second)
{
    // If the 'first' linked list is empty, then we dont have to merge.
    if (first == nullptr)
        return second;

    // If the 'second' linked list is empty, then don’t have to merge.
    if (second == nullptr)
        return first;

    // Regular merge conditions.
    if (first->data > second->data)
    {
        second->next = merge(first, second->next);
        second->next->prev = second;
        second->prev = nullptr;
        return second;
    }
    else
    {
        first->next = merge(first->next, second);
        first->next->prev = first;
        first->prev = nullptr;
        return first;
    }
}

// It returns the sorted doubly linked list.
Node *mergeSort(Node *head)
{
    if (head == nullptr)
        return head;

    if (head->next == nullptr)
        return head;

    Node *first = nullptr, *second = nullptr;
    // Splitting the list.
    second = split(head);

    // Recursively calling merge sort on both the sublists.
    first = mergeSort(head);
    second = mergeSort(second);

    // Merging the two sorted sub lists.
    Node *sortedList = merge(first, second);
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