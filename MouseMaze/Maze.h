/*
Author: Andrew Price
Description: Mouse Maze
Date: 12/2014

Class: Maze.h
Description: Maze class funtion definitions
*/
#pragma once

#include <iostream>
#include <stdlib.h>        /* srand, rand */
#include <time.h>        /* time */
#include <thread>        // std::this_thread::sleep_for
#include <chrono>        // std::chrono::seconds
#include "Stack.h"
using std::cout;
using std::cin;

struct Block
{
    char C;
    bool B; // found cheese
    int x, y; //coordinates
};

class Maze
{
private:
    /*-----------------------------------
        | ascii 219 = wall
        | ascii 2 = mouse
        | ascii 30 = cheese
        | ascii 44 = undiscovered path
        | ascii 249 = Discovered path
    -----------------------------------*/
    // data
    static const int size = 20; // change size to > than 4
    char Grid[size][size];  // Grid[y][x]
    Block Mouse;
    Block Cheese;

    //functions
    bool moveMouse(char direction); // takes N (north), S (south), W (west),
// E (east) if can move returns true
    bool clear();
public:
    Maze();

    void generate();
    void Movement_AI();
    void Movement_User();

    void display();
    void youwin();
    //int COUNT = 0;
};
