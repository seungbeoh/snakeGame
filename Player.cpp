// Definition of Player class

// Preprocessors
#include "Player.h"
#include <cstdlib>

// Overloaded Constructor to construct Player object
// GameMechs* - Pointer to GameMechs object (GameMechs.cpp and GameMechs.h)
// Food* - Pointer to Food object (Food.cpp and Food.h)
Player::Player(GameMechs* thisGMRef, Food* thisFoodRef) 
{
    mainGameMechsRef = thisGMRef;
    mainFoodRef = thisFoodRef;

    // Initialize direction to stopped state
    myDir = STOP; 

    playerPosList = new objPosArrayList(); // Instantiate objPosArrayList object, to be pointed by the pointer "playerPosList"

    // Randomized starting position 
    int startX = rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1;
    int startY = rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1;
            
    // Instantiate "startPos" object with random coordinates and chosen symbol
    objPos startPos(startX, startY, '*');  

    // With the pointer "playerPosList", access "insertHead" function and append "startPos" to the front of the list
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
    // Access getInput() function with the pointer "mainGameMechsRef" (from GameMechs.cpp and GameMechs.h) and store it into input variable 
    char input = mainGameMechsRef->getInput();

    // Set switch cases for WASD player movement control
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

        // Switch cases to handle game exit  
        case 27:
            mainGameMechsRef->setExitTrue();
            break;
        
        default:
            break;
    }

    mainGameMechsRef->clearInput();
}

// Method for wrap-around logic of snake 
// objPos& - Pass "newHead" object by reference (modifiable)
void Player::calcNewHead(objPos& newHead)
{
    int x = newHead.getX();
    int y = newHead.getY();
    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();

    switch(myDir)
    {
        case UP:
            y--;
            if (y <= 0)
            {
                y = boardY - 2; // Wrap to bottom edge
            }
            break;

        case DOWN:
            y++;
            if (y >= boardY - 1)
            {
                y = 1; // Wrap to top edge
            }
            break;

        case LEFT:
            x--;
            if (x <= 0)
            {
                x = boardX - 2; // Wrap to right edge
            }
            break;

        case RIGHT:
            x++;
            if (x >= boardX - 1) 
            {
                x = 1; // Wrap to left edge
            }
            break;

        case STOP:
        default:
            break;
    }

    newHead = objPos(x, y, '*');
}

// Method to move the snake
void Player::movePlayer()  
{
    objPos newHead = playerPosList->getHeadElement();
    calcNewHead(newHead);
    playerPosList->insertHead(newHead);

    bool grew = checkFoodCollision(newHead);
    if (!grew) playerPosList->removeTail();

    checkSelfCollision(newHead);
}

// Method to check for the snake's collision with generated food items 
// const objPos& - Pass "newHead" object by reference (read only)
bool Player::checkFoodCollision(const objPos& newHead)
{
    objPosArrayList* foodBucket = mainFoodRef->getFoodBucket();

    // Run a for-loop to store the location of the food items and verify the snake head's collision with the food item
    // If collision occurs, call incrementScore() function (from GameMechs.cpp and GameMechs.h) 
    for (int i = 0; i < foodBucket->getSize(); i++)
    {
        objPos foodItem = foodBucket->getElement(i);

        if (newHead.isPosEqual(&foodItem))
        {
            char sym = foodItem.getSymbol();

            // If food item is eaten, generate a new "bucket" of food items
            mainFoodRef->generateFood(playerPosList); 

            // Check for the food type that the snake consumed
            if (sym == '$') // Special food type
            {
                mainGameMechsRef->incrementScore(); 
                mainGameMechsRef->incrementScore(); 
                return false; // No snake growth 
            }

            else // Normal food type 
            {
                mainGameMechsRef->incrementScore(); 
                return true; // Growth
            }
        }
    }

    return false; // If no food is eaten
}

// Method for checking if the snake collides with itself
// const objPos& - Pass "newHead" object by reference (read-only)
void Player::checkSelfCollision(const objPos& newHead)
{
    // If the head of the snake shares the same coordinates with any of its other body segments, set setLoseFlag() and setExitTrue() flag to true
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