// Definition of main program, Project class

// Preprocessors
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "MacUILib.h"
#include "objPos.h"
#include "GameMechs.h"
#include "Food.h"
#include "Player.h"

using namespace std;

#define DELAY_CONST 100000

// Global variables
GameMechs* gamePtr;
Food* foodPtr;
Player* playerPtr;

// Function declaration
void Initialize(void);
void GetInput(void);
void RunLogic(void);
void DrawScreen(void);
void LoopDelay(void);
void CleanUp(void);

// Function definitions
int main(void)
{
    Initialize();
    
    // While game is running, call the following functions
    while(gamePtr->getExitFlagStatus() == false) 
    {
        GetInput();
        RunLogic();
        DrawScreen();
        LoopDelay();
    }

    CleanUp();
}


void Initialize(void)
{
    MacUILib_init();
    MacUILib_clearScreen();

    srand(time(NULL));

    // Allocating heap memory for pointers and lists
    gamePtr = new GameMechs();
    foodPtr = new Food(gamePtr);
    playerPtr = new Player(gamePtr, foodPtr);

    foodPtr->generateFood(playerPtr->getPlayerPos());
}

void GetInput(void)
{
    // Asynchronous player input 
    if(MacUILib_hasChar())
    {
        gamePtr->setInput(MacUILib_getChar());
    }
}

void RunLogic(void)
{
    playerPtr->updatePlayerDir();
    playerPtr->movePlayer();
}

void DrawScreen(void)
{
    MacUILib_clearScreen();

    // Store function return values into the following variables
    objPosArrayList* playerPosList = playerPtr->getPlayerPos();
    objPosArrayList* foodBucket = foodPtr->getFoodBucket();

    // Draw game board
    int boardX = gamePtr->getBoardSizeX();
    int boardY = gamePtr->getBoardSizeY();

    for(int row = 0; row < boardY; row++)
    {
        for(int col = 0; col < boardX; col++)
        {
            // Drawing the border 
            if(row == 0 || row == boardY - 1 ||
               col == 0 || col == boardX - 1)
            {
                MacUILib_printf("#");
            }

            // Drawing space in between border
            else
            {
                objPos currPos(col, row, ' ');
                bool drawn = false;

                // Draw snake
                for (int i = 0; i < playerPosList->getSize(); i++)
                {
                    objPos segment = playerPosList->getElement(i);
                    char sym = segment.getSymbolIfPosEqual(&currPos);
                    if (sym != 0)
                    {
                        MacUILib_printf("%c", sym);
                        drawn = true;
                        break;
                    }
                }

                // Draw food
                if (!drawn)
                {
                    bool foodDrawn = false;
                    for (int i = 0; i < foodBucket->getSize(); i++)
                    {
                        objPos foodItem = foodBucket->getElement(i);
                        char foodSym = foodItem.getSymbolIfPosEqual(&currPos);
                        if (foodSym != 0)
                        {
                            MacUILib_printf("%c", foodSym);
                            foodDrawn = true;
                            break;
                        }
                    }
                    if (!foodDrawn)
                        MacUILib_printf(" ");
                }
            }
        }
        MacUILib_printf("\n");
    }

    MacUILib_printf("Score: %d", gamePtr->getScore());
    MacUILib_printf("\n\nUse WASD to move!");
    MacUILib_printf("\nPress ESC to quit");
    MacUILib_printf("\n\n+ = Normal food (+1 score)\n$ = Special food (+2 score, no growth)");
}

void LoopDelay(void)
{
    MacUILib_Delay(DELAY_CONST);
}

void CleanUp(void)
{
    MacUILib_clearScreen();

    if (gamePtr->getLoseFlagStatus())
        MacUILib_printf("Game over! You ran into yourself.\n");

    else
        MacUILib_printf("Thanks for playing! :)\n");

    MacUILib_printf("Final score: %d\n", gamePtr->getScore());

    // Deallocate heap memory 
    delete playerPtr;
    delete foodPtr;
    delete gamePtr;

    MacUILib_uninit();
}