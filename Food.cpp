// Definition of Food class
// Handles the generation of food items 

// Preprocessors 
#include "Food.h"
#include "GameMechs.h"
#include <cstdlib>

// Overloaded Constructor to construct food object
// GameMechs* - Pointer to GameMechs object (GameMechs.cpp and GameMechs.h)
// thisGMRef - Local parameter name to hold the pointer GameMechs*
Food::Food(GameMechs* thisGMRef) 
{
    mainGameMechsRef = thisGMRef;
    foodBucket = new objPosArrayList(); // Instantiate objPosArrayList object, to be pointed by the pointer "foodBucket"

    // Run a for-loop to generate 5 random food items 
    for (int i = 0; i < 5; i++)
    {
        int x, y;
        bool isValid;
        char sym;

        // While the coordinates are not valid, keep generating new random coordinates for the food items to spawn at
        do
        {
            isValid = true;
            
            // Generate new coordinates
            x = rand() % (mainGameMechsRef->getBoardSizeX() - 2) + 1;
            y = rand() % (mainGameMechsRef->getBoardSizeY() - 2) + 1;

            // For all items stored with the "foodBucket" pointer, verify if the coordinates overlap with previous food items on the gameboard
            // If overlap occurs, set "isValid" boolean value to false for the do-while loop to recur 
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
        
        // Set 2/5 items in foodBucket as special food, symbol = $
        if (i < 2) 
        {
            sym = '$';  
        }

        // Set 3/5 items in foodBucket as normal food, symbol = +
        else 
        {
            sym = '+';  
        }

        // Instantiate food object with random coordinates and chosen symbol
        objPos food(x, y, sym);  

        // With the pointer "foodBucket", access "insertTail" function and append "food" to the end of the list
        foodBucket->insertTail(food);
    }
}

// Destructor
Food::~Food() 
{
    delete foodBucket;
}

// Getter
// objPosArrayList* - Return type, the function returns a pointer to an objPosArrayList object
objPosArrayList* Food::getFoodBucket() const 
{
    return foodBucket;
}

// Method to place all food items from "foodBucket" pointer onto the gameboard
// objPosArrayList* - Pointer to objPosArrayList object (objPosArrayList.cpp and objPosArrayList.h)
// blockOffList - Local parameter name to hold the pointer objPosArrayList*
void Food::generateFood(objPosArrayList* blockOffList)
{
    int boardX = mainGameMechsRef->getBoardSizeX(); 
    int boardY = mainGameMechsRef->getBoardSizeY();

    // Delete the contents in the previous run's bucket 
    delete foodBucket;  

    // Allocate new heap memory to the "objPosArrayList" object to store under the "foodBucket" pointer 
    foodBucket = new objPosArrayList();  

    // Run a for-loop to generate 5 new food items, checking overlap with snake's body and other food
    for (int i = 0; i < 5; i++) 
    {
        int x, y;
        bool isValid;
        char sym;

        do
        {
            isValid = true;

            // Generate random x & y coordinate for the new food item 
            x = rand() % (boardX - 2) + 1;
            y = rand() % (boardY - 2) + 1;

            for (int j = 0; j < blockOffList->getSize(); j++)
            {
                objPos segment = blockOffList->getElement(j); 

                // Check for if x & y coordinates of food item overlap with the snake's body
                // If overlap occurs, discard item
                if (x == segment.getX() && y == segment.getY())
                {
                    isValid = false;
                    break;
                }
            }

            // If the newly generated coordinates don't overlap with the snake's body, check for overlap with existing food items in "foodBucket"
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

        // Instantiate food object with random coordinates and chosen symbol
        objPos food(x, y, sym); 

        // With the pointer "foodBucket", access "insertTail" function and append "food" to the end of the list
        foodBucket->insertTail(food); 
    }
}
