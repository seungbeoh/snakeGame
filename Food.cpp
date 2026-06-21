// Definition of Food class
// Handles the generation of food items 

// Preprocessors 
#include "Food.h"
#include "GameMechs.h"
#include <cstdlib>

// Constructor
Food::Food(GameMechs* thisGMRef) 
{
    mainGameMechsRef = thisGMRef;
    foodBucket = new objPosArrayList(); // Allocate heap memory for food bucket, pointer generated during runtime 

    for (int i = 0; i < 5; i++)
    {
        int x, y;
        bool isValid;
        char sym;

        do
        {
            isValid = true;
            
            // Generate a random x & y coordinate for food to spawn 
            x = rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1;
            y = rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1;

            for (int k = 0; k < foodBucket->getSize(); k++)
            {
                objPos placed = foodBucket->getElement(k);
                if (x == placed.getX() && y == placed.getY())
                {
                    isValid = false;
                    break;
                }
            }
        }while (!isValid);

        if (i < 2) // 2/5 items in foodBucket are special food 
        {
            sym = '$';  
        }
        else // 3/5 items in foodBucket are normal food 
        {
            sym = '+';  
        }

        objPos food(x, y, sym); // Instantiate object 

        foodBucket->insertTail(food);
    }
}

// Destructor
Food::~Food() 
{
    delete foodBucket;
}

// Getter
objPosArrayList* Food::getFoodBucket() const 
{
    return foodBucket;
}

// Methods
void Food::generateFood(objPosArrayList* blockOffList)
{
    int boardX = mainGameMechsRef->getBoardSizeX(); 
    int boardY = mainGameMechsRef->getBoardSizeY();

    delete foodBucket;  // Delete the contents in the previous run's bucket 

    foodBucket = new objPosArrayList();  // Allocate heap memory for generating new members 

    // Iterating through the 5 items in foodBucket 
    for (int i = 0; i < 5; i++) 
    {
        int x, y;
        bool isValid;
        char sym;

        do
        {
            isValid = true;

            // Generating random x & y coordinate for the new food item 
            x = rand() % (boardX - 2) + 1;
            y = rand() % (boardY - 2) + 1;

            // Iterate through snake's body members
            for (int j = 0; j < blockOffList->getSize(); j++)
            {
                objPos segment = blockOffList->getElement(j); // Store returned object from getter method into a local variable

                // if x & y coordinates of food item overlap with snake's objPos coordinate, discard item
                if (x == segment.getX() && y == segment.getY())
                {
                    isValid = false;
                    break;
                }
            }

            if (isValid)
            {
                for (int k = 0; k < foodBucket->getSize(); k++)
                {
                    objPos placed = foodBucket->getElement(k);
                    if (x == placed.getX() && y == placed.getY())
                    {
                        isValid = false;
                        break;
                    }
                }
            }
        } while (!isValid);

        if (i < 2)
            sym = '$';

        else
            sym = '+';

        objPos food(x, y, sym); // Instantiate new food item

        foodBucket->insertTail(food); // Append new food item to the end of foodBucket
    }
}

void Food::replaceFoodItem(int index, objPosArrayList* blockOffList)
{
    int boardX = mainGameMechsRef->getBoardSizeX();
    int boardY = mainGameMechsRef->getBoardSizeY();
    int x, y;
    bool isValid;

    objPos oldFood = foodBucket->getElement(index);
    char sym = oldFood.getSymbol();

    objPosArrayList* newBucket = new objPosArrayList();
    for (int i = 0; i < foodBucket->getSize(); i++)
    {
        if (i != index)
            newBucket->insertTail(foodBucket->getElement(i));
    }

    do
    {
        isValid = true;
        x = rand() % (boardX - 2) + 1;
        y = rand() % (boardY - 2) + 1;

        for (int j = 0; j < blockOffList->getSize(); j++)
        {
            objPos segment = blockOffList->getElement(j);
            if (x == segment.getX() && y == segment.getY())
            {
                isValid = false;
                break;
            }
        }

        if (isValid)
        {
            for (int k = 0; k < newBucket->getSize(); k++)
            {
                objPos placed = newBucket->getElement(k);
                if (x == placed.getX() && y == placed.getY())
                {
                    isValid = false;
                    break;
                }
            }
        }
    } while (!isValid);

    objPos newFood(x, y, sym);
    newBucket->insertTail(newFood);

    delete foodBucket;
    foodBucket = newBucket;
}

