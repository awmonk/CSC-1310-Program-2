#include "List.h"
using namespace std;

template <class T>
List<T>::listNode::listNode(T value)
    : value(value), next(nullptr), prev(nullptr){};

template <class T>
List<T>::listNode::~listNode() { delete value; };

template <class T>
void List<T>::print(listNode *node)
{
    cout << "\n";
    if (node == nullptr)
        return;
    cout << *(node->value);
    print(node->next);
};

template <class T>
typename List<T>::listNode *List<T>::split(listNode *left, listNode *right)
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

template <class T>
typename List<T>::listNode *List<T>::merge(listNode *left, listNode *right)
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

template <class T>
typename List<T>::listNode *List<T>::mergesort(listNode *start, listNode *end)
{
    if (start == nullptr || start->next == end)
        return start;

    listNode *left = nullptr;
    listNode *right = nullptr;
    listNode *mid = nullptr;

    mid = split(start, end);

    if (mid != nullptr)
    {
        left = mergesort(start, mid->prev);
        right = mergesort(mid, end);
    }

    return merge(left, right);
};

template <class T>
List<T>::List() : head(nullptr), tail(nullptr) {}

template <class T>
List<T>::~List()
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

template <class T>
void List<T>::print()
{
    print(head);
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
void List<T>::mergesort()
{
    head = mergesort(head, tail);
    listNode *current = head;
    while (current != nullptr && current->next != nullptr)
    {
        current->next->prev = current;
        current = current->next;
    }
    tail = current;
};

template <class T>
void List<T>::outfile(const string &filename)
{
    ofstream outfile(filename);
    if (!outfile.is_open())
    {
        cerr << "Error opening the file for writing." << endl;
        return;
    }

    listNode *current = head;
    while (current != nullptr)
    {
        outfile << *(current->value) << endl;
        current = current->next;
    }

    outfile.close();
}