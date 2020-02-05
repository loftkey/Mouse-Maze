/*
Author: Andrew Price
Description: Mouse Maze
Date: 12/2014

Class: Main
Description: Generates a maze and completes the maze using if statement and stack input
*/

#include <iostream>
#include "Maze.h"

using namespace std;

int main()
{
    Maze lab1;
    lab1.generate();
    lab1.Movement_AI();
    //cout << lab1.COUNT<< endl;
    return 0;
}
