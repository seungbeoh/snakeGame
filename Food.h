// Declaration of food class

#ifndef FOOD_H
#define FOOD_H

#include "objPos.h"
#include "objPosArrayList.h"

class GameMechs;

class Food
{
    private:
        objPosArrayList* foodBucket; 
        GameMechs* mainGameMechsRef;

    public:
        // Constructor
        Food(GameMechs* thisGMRef);

        // Destructor
        ~Food();

        // Getter
        objPosArrayList* getFoodBucket() const;  

        // Methods
        void generateFood(objPosArrayList* blockOffList);                       
        void replaceFoodItem(int index, objPosArrayList* blockOffList);          
};

#endif