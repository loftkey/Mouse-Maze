/*
Author: Andrew Price
Description: Mouse Maze
Date: 12/2014

Class: Maze.cpp
Description: Maze class funtions
*/

#include "Maze.h"
/*----------------------------------------------------
Function: Maze()
Description: Default constructor seeds srand
----------------------------------------------------*/
Maze::Maze()
{
    srand((unsigned int)time(NULL));

}

/*----------------------------------------------------
Function: void generate()
Description: Fills the array with walls and the cheese and mouse
-----------------------------------------------------*/
void Maze::generate()
{
    for (int y = 0; y < size - 1; y++)
    {
        for (int x = 0; x < size; x++)
        {
            Grid[y][x] = rand() % 101;
            if (Grid[y][x] % 3 == 0)
                Grid[y][x] = char(219);         // sets boarder
            else
                Grid[y][x] = char(44);            // sets undiscovered

            Grid[0][x] = char(219);            // sets boarder
            Grid[size - 1][x] = char(219);    // sets boarder
        }
        Grid[y][0] = char(219);                // sets boarder
        Grid[y][size - 1] = char(219);        // sets boarder


    }

    // sets mouse
    Mouse.x = 1;
    Mouse.y = size / 2;
    Mouse.B = true;
    Mouse.C = char(2);
    Grid[size / 2][1] = Mouse.C; // Mouse
    Grid[size / 2][2] = char(44); // undiscovered

    // sets cheese
    Cheese.x = size - 1;
    Cheese.y = size / 2;
    Cheese.B = true;
    Cheese.C = char(30); // cheese
    Grid[size / 2][size - 1] = Cheese.C; // cheese
    Grid[size / 2][size - 2] = char(44); // undiscovered
    Grid[size / 2][size - 3] = char(44); // undiscovered
    Grid[size / 2][size - 4] = char(44); // undiscovered

    /*std::this_thread::sleep_for(std::chrono::milliseconds(150));
    system("CLS");
    display();*/

    while (!clear())
    {
        //COUNT++;
        generate();
    }

}

/*----------------------------------------------------------
Function: bool clear()
Description: Checks to see if the maze is clearable returns true if it is
Outputs: bool
-----------------------------------------------------------*/
bool Maze::clear() // takes N (north), S (south), W (west), E (east) if can move returns true
{
    Maze temp = *this;

    Stack<char> path;
    while (temp.Cheese.B)
    {
        //forward
        if (temp.Grid[temp.Mouse.y][temp.Mouse.x + 1] == char(44))
        {
            temp.moveMouse('E');
            path.push('W');
        }
        else if (temp.Grid[temp.Mouse.y + 1][temp.Mouse.x] == char(44))
        {
            temp.moveMouse('S');
            path.push('N');
        }
        else if (temp.Grid[temp.Mouse.y - 1][temp.Mouse.x] == char(44))
        {
            temp.moveMouse('N');
            path.push('S');
        }
        else if (temp.Grid[temp.Mouse.y][temp.Mouse.x - 1] == char(44))
        {
            temp.moveMouse('W');
            path.push('E');
        }
        else if (path.getSize() > 0)
        {
            temp.moveMouse(path.pop());
        }
        else if (path.getSize() == 0)
            return false;
        if (temp.Grid[temp.Mouse.y][temp.Mouse.x + 1] == temp.Cheese.C)
            return true;
    }
    return true;

}

/*---------------------------------------------------------------
Function: moveMouse(char direction)
Description: moves the mouse taking in a car to move it south north west or east returns true if it can move
Inputs: char
Outputs: bool
---------------------------------------------------------------*/
bool Maze::moveMouse(char direction) // takes N (north), S (south), W (west), E (east) if can move returns true
{
    //        Grid[y][x]
    bool canmove = false;
    switch (toupper(direction))
    {
    case 'N': // up so y - 1
        if (Grid[Mouse.y - 1][Mouse.x] != char(219))
        {
            Grid[Mouse.y - 1][Mouse.x] = Grid[Mouse.y][Mouse.x];
            Grid[Mouse.y][Mouse.x] = char(249);
            Mouse.y -= 1;
            canmove = true;
        }
        break;
    case 'S': // down so y + 1
        if (Grid[Mouse.y + 1][Mouse.x] != char(219))
        {
            Grid[Mouse.y + 1][Mouse.x] = Grid[Mouse.y][Mouse.x];
            Grid[Mouse.y][Mouse.x] = char(249);
            Mouse.y += 1;
            canmove = true;
        }
        break;
    case 'E': // right so x + 1
        if (Grid[Mouse.y][Mouse.x + 1] != char(219))
        {
            Grid[Mouse.y][Mouse.x + 1] = Grid[Mouse.y][Mouse.x];
            Grid[Mouse.y][Mouse.x] = char(249);
            Mouse.x += 1;
            canmove = true;
        }
        break;
    case 'W': // left so x - 1
        if (Grid[Mouse.y][Mouse.x - 1] != char(219))
        {
            Grid[Mouse.y][Mouse.x - 1] = Grid[Mouse.y][Mouse.x];
            Grid[Mouse.y][Mouse.x] = char(249);
            Mouse.x -= 1;
            canmove = true;
        }
        break;
    }
    if (Grid[Cheese.y][Cheese.x] != Cheese.C)
        Cheese.B = false;
    return canmove;
}

/*--------------------------------------------------------------------
Function: void Movement_AI()
Description: moves the mouse on its own through the maze
--------------------------------------------------------------------*/
void Maze::Movement_AI()
{
    Stack<char> path;
    display();
    while (Cheese.B)
    {
        //forward
        if (Grid[Mouse.y][Mouse.x + 1] == char(44))
        {
            moveMouse('E');
            path.push('W');
        }
        else if (Grid[Mouse.y + 1][Mouse.x] == char(44))
        {
            moveMouse('S');
            path.push('N');
        }
        else if (Grid[Mouse.y - 1][Mouse.x] == char(44))
        {
            moveMouse('N');
            path.push('S');
        }
        else if (Grid[Mouse.y][Mouse.x - 1] == char(44))
        {
            moveMouse('W');
            path.push('E');
        }
        else if (path.getSize() > 0)
        {
            moveMouse(path.pop());
        }
        if (Grid[Mouse.y][Mouse.x + 1] == Cheese.C)
            Cheese.B = false;
        std::this_thread::sleep_for(std::chrono::milliseconds(150));
        system("CLS");
        display(); // displays the mouse, maze and cheese
    }
    youwin();

}

/*--------------------------------------------------------------------
Function: void Movement_User()
Description: moves the mouse on its own using user input
--------------------------------------------------------------------*/
void Maze::Movement_User()
{
    char input;
    display();
    while (Cheese.B)
    {

        cin >> input;
        switch (tolower(input))
        {
        case 'w':
            moveMouse('N');
            break;
        case 'a':
            moveMouse('W');
            break;
        case 's':
            moveMouse('S');
            break;
        case 'd':
            moveMouse('E');
            break;
        }

        system("CLS");
        display();
        if (Grid[Mouse.y][Mouse.x + 1] == Cheese.C)
            Cheese.B = false;

    }
    youwin();
}

/*---------------------------------------------------------------
Function: void display()
Description: displayes the mouse, cheese, and maze
----------------------------------------------------------------*/
void Maze::display()
{
    cout << "\n";
    for (int y = 0; y < size; y++)
    {
        cout << y << "\t";
        for (int x = 0; x < size; x++)
        {
            cout << Grid[y][x] << " ";
        }
        cout << "\n";
    }

}


/*------------------------------------------------------------
Function: void youwin()
Description: writes "You Win" to screen
-------------------------------------------------------------*/
void Maze::youwin()
{
    //system("CLS");

    cout << "\nCongradulations: \n";
    std::this_thread::sleep_for(std::chrono::seconds(1));
    cout << char(14) << " YOU WIN " << char(14) << "\n";
    //system("Pause");

}
