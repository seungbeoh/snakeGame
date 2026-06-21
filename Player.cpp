// Definition of Player class

// Preprocessors
#include "Player.h"
#include <cstdlib>

// Constructor
Player::Player(GameMechs* thisGMRef, Food* thisFoodRef) 
{
    // Default state of player object, prior to starting the game
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;
    myDir = STOP; 

    // Allocate heap memory 
    playerPosList = new objPosArrayList();

    // Randomized starting position 
    int startX = rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1;
    int startY = rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1;

    objPos startPos(startX, startY, '*'); // Declare player object with data type of objPos 
    playerPosList->insertHead(startPos);
}

// Destructor
Player::~Player() 
{
    delete playerPosList;
}

// Getter
objPosArrayList* Player::getPlayerPos() const  
{
    return playerPosList;
}

// Methods
void Player::updatePlayerDir()  
{
    char input = mainGameMechsRef->getInput();

    switch(input)
    {
        case 'w':
        case 'W':
            if (myDir != DOWN)
            {
                myDir = UP;
            }
            break;
        case 's':
        case 'S':
            if (myDir != UP)
            {
                myDir = DOWN;
            }
            break;
        case 'a': 
        case 'A':
            if (myDir != RIGHT)
            {
                myDir = LEFT;
            }
            break;
        case 'd':
        case 'D':
            if (myDir != LEFT)
            {
                myDir = RIGHT;
            }
            break;
        case 27:
            mainGameMechsRef->setExitTrue();
            break;
        case 'p': 
        case 'P':
            mainGameMechsRef->incrementScore();
            break;
        case 'l': 
        case 'L':
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            break;
        default:
            break;
    }

    mainGameMechsRef->clearInput();
}

void Player::movePlayer()  
{
    // New head position
    objPos currentHead = playerPosList->getHeadElement();

    // Access x and y coordinates from currentHead (objPos object)
    int x = currentHead.getX(); 
    int y = currentHead.getY();

    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();

    switch(myDir)
    {
        case UP:
            y--;
            if (y <= 0)
            {
                y = boardY - 2;
            }
            break;
        case DOWN:
            y++;
            if (y >= boardY - 1)
            {
                y = 1;
            }
            break;
        case LEFT:
            x--;
            if (x <= 0)
            {
                x = boardX - 2;
            }
            break;
        case RIGHT:
            x++;
            if (x >= boardX - 1)
            {
                x = 1;
            }
            break;
        case STOP:
        default:
            break;
    }

    objPos newHead(x, y, '*'); // Instantiate new object member 

    // Feature 1 - Iteration 3, snake body implementation 
    playerPosList->insertHead(newHead);

    // Feature 2 - Iteration 3, food consumption
    bool foodEaten = false;
    char eatenSym = ' ';

    objPosArrayList* foodBucket = mainFoodRef->getFoodBucket();
    for (int i = 0; i < foodBucket->getSize(); i++)
    {
        objPos foodItem = foodBucket->getElement(i);

        if (newHead.isPosEqual(&foodItem))
        {
            foodEaten = true;
            eatenSym = foodItem.getSymbol();
            mainFoodRef->replaceFoodItem(i, playerPosList); // swap out only the eaten item
            break;
        }
    }

    if (foodEaten)
    {
        if (eatenSym == '$')  // Special food
        {
            mainGameMechsRef->incrementScore(); 
            mainGameMechsRef->incrementScore(); // 2 points

            playerPosList->removeTail(); // No growth
        }
        else  // Normal food
        {
            mainGameMechsRef->incrementScore(); // 1 point
            // No removeTail allows snake to grow 
        }
    }

    else
    {
        playerPosList->removeTail();
    }

    // Feature 3 - Iteration 3, if snake runs into itself
    for (int i = 1; i < playerPosList->getSize(); i++)
    {
        objPos segment = playerPosList->getElement(i);
        if (newHead.isPosEqual(&segment))
        {
            mainGameMechsRef->setLoseFlag();
            mainGameMechsRef->setExitTrue();
            break;
        }
    }
}