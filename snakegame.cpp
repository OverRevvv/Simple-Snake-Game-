#include <iostream>
#include <conio.h>
#include <windows.h>
using namespace std;

// Gloabal Declaration of all the variables that are gonna be used in the game

bool gameOver;                   // variable responsible for game to run
const int width = 20;            // Width of the map
const int height = 20;           // Height of the map
int x, y, fruitX, fruitY, score; // all elements that gonna be used in the game
int tailX[100], tailY[100];      // all attributes for the tail of the snake
int nTail;

enum eDirection // Declaration for direction of the movement of snake
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir; // Intial Postion variable for snake

void Setup()
{
    gameOver = false;
    dir = STOP; // initial movement of snake

    // Spawning Location of Snake
    x = width / 2;
    y = height / 2;

    // Spawning Location of fruit in game
    fruitX = rand() % width;
    fruitY = rand() % height;

    score = 0; // Intial Score
}

void Draw()
{
    system("cls"); // to clear screen

    // Printing the Map area for the game
    for (int i = 0; i < width + 2; i++)
        cout << "#";
    cout << endl;

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            if (j == 0)
            {
                cout << "#";
            }
            if (i == y && j == x)
            {
                cout << "O";
            }
            else if (i == fruitY && j == fruitX)
            {
                cout << "F";
            }
            else
            {
                // Drawing the tail
                bool print = false;
                for (int k = 0; k < nTail; k++)
                {
                    if (tailX[k] == j && tailY[k] == i)
                    {
                        cout << "o";
                        print = true;
                    }
                }
                if (!print)
                    cout << " ";
            }
            if (j == width - 1)
                cout << "#";
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++)
        cout << "#";

    // Score of the game

    cout << endl;
    cout << "Score: " << score << endl;
}

void Input()
{
    // Declaration of all the necessary attributes for the player control the snakehead

    if (_kbhit()) // checks if keyboard is pressed
    {
        switch (_getch()) // check if console have input
        {
        case 'a': // setting up the controls
            dir = LEFT;
            break;
        case 'd':
            dir = RIGHT;
            break;
        case 'w':
            dir = UP;
            break;
        case 's':
            dir = DOWN;
            break;
        case 'x':            // Exit Button
            gameOver = true; // Exits the game
            break;
        }
    }
}
void Logic()
{
    // Creating all the logics that are necessary for the game to run

    // This switch statement is responsible for movement of the snakehead

    int prevX = tailX[0],
        prevY = tailY[0],
        prev2X, prev2Y;

    tailX[0] = x;
    tailY[0] = y;

    for (int i = 1; i < nTail; i++)
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    // Every is just incermenting or decrementing the value of X and y for the snake to move
    switch (dir)
    {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;

    default:
        break;
    }

    // This conditions are responsible for exit the game if tried to leave map area

    // if (x > width || x < 0 || y > height || y < 0)
    //     gameOver = true;

    // Uncomment this portion to cheat
    if (x > width)
        x = 0;
    else if (x < 0)
        x = width - 1;
    if (y > height)
        y = 0;
    else if (y < 0)
        y = height - 1;
    // End of the Cheat

    // This Loop is reponsible for Game Over When Snake touch it's tail
    for (int i = 0; i < nTail; i++)
    {
        if (tailX[i] == x && tailY[i] == y)
            gameOver = true;
    }

    // These conditions are responsible for output of fruit get eaten by the snake

    if (x == fruitX && y == fruitY)
    {
        // Spawning Location of fruit in game
        fruitX = rand() % width;
        fruitY = rand() % height;
        score += 10;
        nTail++;
    }
}

int main()
{
    Setup();
    while (!gameOver)
    {
        Draw();
        Input();
        Logic();
        Sleep(100); // Add more 0 to to slow down the pace of the game vice versa
    }
    return 0;
}