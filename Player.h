// Declaration of Player class

#ifndef PLAYER_H
#define PLAYER_H

#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"

class Player
{
    public:
        enum Dir {UP, DOWN, LEFT, RIGHT, STOP};

        // Constructor 
        Player(GameMechs* thisGMRef, Food* thisFoodRef);

        // Destructor  
        ~Player();

        // Getters
        objPosArrayList* getPlayerPos() const;

        // Methods
        void updatePlayerDir();
        void movePlayer();

    private:
        enum Dir myDir;    
        objPosArrayList* playerPosList;
        GameMechs* mainGameMechsRef;
        Food* mainFoodRef;
};

#endif