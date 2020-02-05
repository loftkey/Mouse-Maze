/*
Author: Andrew Price
Description: Mouse Maze
Date: 12/2014

Class: Stack
Description: Template class Derived from DLinkList to act as a stack
*/

#pragma once
#include <cstdio> 
#include <stdio.h>
#include "DLinkList.h"

template <class T>
class Stack : public DLinkList<T>
{
public:
    void push(T t);
    T pop();
    T peek();

};

/*
Function: push(T t)
Description: push function adds new item to front of list
Inputs: T t
*/
template <class T>
void Stack<T>::push(T t)
{
    this->addFront(t);
}

/*
Function: pop()
Description: pop function returns the next item in the list and removes it from the list
Outputs: T r
*/
template <class T>
T Stack<T>::pop()
{
    T r = DLinkList<T>::getValue(1);
    DLinkList<T>::deleteAt(1);
    return r;
}

/*
Function: peek()
Description: peek function returns the next item in the list
Output: Type T
*/
template <class T>
T Stack<T>::peek()
{
    return DLinkList<T>::getValue(1);
}