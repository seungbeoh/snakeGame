// Declaration of "Food" class

// Preprocessors
#ifndef FOOD_H
#define FOOD_H
#include "objPos.h"
#include "objPosArrayList.h"

// Include "GameMechs" class
class GameMechs;

// Declare "Food" class
class Food
{
    private:
        // Pointers
        objPosArrayList* foodBucket; 
        GameMechs* mainGameMechsRef;

    public:
        // Constructor
        Food(GameMechs* thisGMRef);

        // Destructor
        ~Food();

        // Getter
        objPosArrayList* getFoodBucket() const;  

        // Method
        void generateFood(objPosArrayList* blockOffList);                       
};

#endif