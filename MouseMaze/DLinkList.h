/*
Author: Andrew Price
Description: Mouse Maze
Date: 12/2014

Class: DLinkList
Description: Template class that holds a doubly linked list
*/
#pragma once
#include <string>
using std::string;

template <class T>
struct Node
{
    T Data;
    Node<T>* Prev;
    Node<T>* Next;
};

template <class T>
class DLinkList
{
private:
    Node<T>* Head;

public:
    DLinkList();
    DLinkList(T data);

    void addFront(T data);
    void addRear(T data);
    void insertAfter(T search, T value);
    void insertAt(int index, T value);
    void replaceAt(int index, T value);
    void deleteNode(T search);
    void deleteAt(int index);
    void switchData(int index1, int index2);

    int getSize();
    T getValue(int index);
    Node<T>* getNode(int index);
    Node<T>* getHead();
    Node<T>* getEnd();

    //void printList();
};


/*
Function: DLinkList()
Description: DLinkList constructor sets head to Null
*/
template <class T>
DLinkList<T>::DLinkList()
{
    this->Head = NULL;
}

/*
Function: DLinkList(T data)
Description: Overloaded DLinkList constructor stores arguments to Head->Data
Inputs: Takes Type T data
*/
template <class T>
DLinkList<T>::DLinkList(T data)
{
    this->Head = NULL;
    this->addFront(data);        // takes advantage of addFront function
}

/*
Function: addFront(T data)
Description: function that adds a new item to the front of the list
Inputs: Takes Type T data
*/
template <class T>
void DLinkList<T>::addFront(T data)
{
    if (Head == NULL)
    {
        Head = new Node<T>();
        Head->Data = data;
        Head->Prev = NULL;
        Head->Next = NULL;
    }
    else
    {
        Node<T>* n = new Node<T>;
        n->Data = Head->Data;
        n->Next = Head->Next;
        n->Prev = Head;
        if (Head->Next != NULL)
        {
            Head->Next->Prev = n;
        }
        Head->Data = data;
        Head->Next = n;

    }
}

/*
Function: addRear(T data)
Description: function that adds a new item to the end of the list
Inputs: Takes Type T data
*/
template <class T>
void DLinkList<T>::addRear(T data)
{
    if (Head == NULL)
    {
        Head = new Node<T>();
        Head->Prev = NULL;
        Head->Data = data;
        Head->Next = NULL;
    }
    else
    {
        Node<T>* p = Head;
        while (p->Next != NULL)
        {
            p = p->Next;
        }

        Node<T>* n = new Node<T>;
        n->Prev = p;
        n->Data = data;
        n->Next = NULL;

        p->Next = n;
    }
}

/*
Function: insertAfter(T search, T value)
Description: function that adds a new item after a searched item the list
Inputs: Takes in two Type T data
*/
template <class T>
void DLinkList<T>::insertAfter(T search, T value)
{

    if (Head == NULL)
    {
        Head = new Node<T>();
        Head->Prev = NULL;
        Head->Data = value;
        Head->Next = NULL;
    }
    else
    {
        Node<T>* p = Head;
        while (p->Data != search)
        {
            p = p->Next;
        }

        Node<T>* n = new Node<T>;
        n->Data = value;
        n->Prev = p;
        p->Next->Prev = n;
        n->Next = p->Next;

        p->Next = n;
    }
}

/*
Function: insertAt(int index, T value)
Description: function that adds a new item at specified location in the list
Inputs: Takes Type T data and Int
*/
template <class T>
void DLinkList<T>::insertAt(int index, T value)
{

    if (Head == NULL)
    {
        Head = new Node<T>();
        Head->Data = value;
        Head->Next = NULL;
        Head->Prev = NULL;
    }
    else
    {
        Node<T>* p = getNode(index), * n = new Node<T>;
        n->Data = p->Data;
        n->Next = p->Next;
        p->Next->Prev = n;
        p->Next = n;
        n->Prev = p;
        p->Data = value;

    }
}

/*
Function: replaceAt(int index, T value)
Description: function that replaces data at specified location in the list
Inputs: Takes Type T data and Int
*/
template <class T>
void DLinkList<T>::replaceAt(int index, T value)
{
    if (Head == NULL)
    {
        // nothing to replace
    }
    else
    {
        if (0 < index && index < getSize() + 1)
        {
            getNode(index)->Data = value;
        }
    }

}

/*
Function: deleteNode(T search)
Description: function that deletes an item in the list of the same specified value
Inputs: Type T value
*/
template <class T>
void DLinkList<T>::deleteNode(T search)
{
    if (Head == NULL)
    {
        //Nothing to delete
    }
    else
    {
        Node<T>* p = Head;
        while (p->Data != search)
        {
            p = p->Next;
        }
        if (p->Prev == NULL)
        {
            Head = Head->Next;
            Head->Next->Prev = Head;
            Head->Prev = NULL;
            delete p;
        }
        else
        {
            p->Prev->Next = p->Next;
            p->Next->Prev = p->Prev;
            delete p;
        }
    }
}

/*
Function: deleteAt(int index)
Description: function that deletes an item in the list at specified location
Inputs: int
*/
template <class T>
void DLinkList<T>::deleteAt(int index)
{

    if (Head == NULL)
    {
        // Nothing to delete
    }
    else
    {
        if (index > 0)
        {
            int i = 1;
            Node<T>* p = Head;
            while (i != index)
            {
                p = p->Next;
                if (p == NULL)
                    return;
                else
                    i++;
            }
            if (p->Prev == NULL && p->Next != NULL)
            {
                Head = Head->Next;
                Head->Prev = NULL;
                delete p;
            }
            else if (p->Prev == NULL && p->Next == NULL)
            {
                Head = NULL;
                delete p;
            }
            else
            {
                p->Prev->Next = p->Next;
                delete p;
            }
        }
    }
}

/*
Function: switchData(int index1, int index2)
Description: function that switches two data values in the list at specified locations
Inputs: two ints
*/
template <class T>
void DLinkList<T>::switchData(int index1, int index2)
{
    if (1 < getSize())
    {
        if (0 < index1 && index1 < getSize() + 1 && 0 < index2 && index2 < getSize() + 1)
        {
            T x = getValue(index1), y = getValue(index2);
            getNode(index2)->Data = x;
            getNode(index1)->Data = y;
        }
    }
    else
    {
        // nothing to swap
    }

}

/*
Function: getSize()
Description: function that returns the size of the list as an int
Outputs: int
*/
template <class T>
int DLinkList<T>::getSize()
{
    int i = 0;
    if (Head == NULL)
    {
        // size is 0
    }
    else
    {
        Node<T>* p = Head;
        while (p != NULL)
        {
            i++;
            p = p->Next;
        }
    }
    return i;
}

/*
Function: getValue(int index)
Description: function that returns type T item in the list at specified location
Inputs: int
Outputs: Type T value
*/
template <class T>
T DLinkList<T>::getValue(int index)
{
    T t = T();
    if (0 < index && index < getSize() + 1)
    {
        t = getNode(index)->Data;
    }
    return t;
}

/*
Function: getNode(int index)
Description: function that returns a pointer to the node in the list at specified location
Inputs: int
Outputs: Node<T>*
*/
template <class T>
Node<T>* DLinkList<T>::getNode(int index)
{
    Node<T>* p = Head;
    int i = 1;
    if (0 < index && index < (getSize() + 1))
    {
        while (i != index)
        {
            p = p->Next;
            if (p == NULL)
                return p;
            else
                i++;
        }
    }
    else if (index == 0)
    {
        p = NULL;
    }
    return p;
}

/*
Function: getHead()
Description: function that returns a pointer to the Head node in the list
Outputs: Node<T>*
*/
template <class T>
Node<T>* DLinkList<T>::getHead()
{
    return this->Head;
}

///*
//Function: printList()
//Description: function that prints the list [FOR TEST PURPOSES ONLY]
//Outputs: cout's List
//*/
//template <class T>
//void DLinkList<T>::printList()
//{
//    Node<T> *p = Head;
//    while(p != NULL)
//    {
//        cout << p->Data << endl;
//        p = p->Next;
//    }
//
//    cout << endl;
//    if(getSize() > 0)
//    {
//        Node<T> *z = getEnd();
//        while(z != NULL)
//        {
//            cout << z->Data << endl;
//            z = z->Prev;
//        }
//    }
//}

/*
Function: getEnd()
Description: function that returns a pointer to the end node in the list
THIS can be used to start at the last node and traverse through the list backwards until ->Prev == NULL

Example:
//    if(getSize() > 0)
//    {
//        Node<T> *z = getEnd();
//        while(z != NULL)
//        {
//            //DO STUFF HERE
//            z = z->Prev;
//        }
//    }

Outputs: Node<T>*
*/
template <class T>
Node<T>* DLinkList<T>::getEnd()
{
    Node<T>* p = Head;
    while (p->Next != NULL)
    {
        p = p->Next;
    }
    return p;
    //getNode(getSize()); // alternatively
}