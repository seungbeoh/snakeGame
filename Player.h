// Declaration of Player class

// Preprocessors
#ifndef PLAYER_H
#define PLAYER_H
#include "GameMechs.h"
#include "objPos.h"
#include "objPosArrayList.h"
#include "Food.h"


// Declare "Player" class
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

        void calcNewHead(objPos& newHead);
        bool checkFoodCollision(const objPos& newHead);
        void checkSelfCollision(const objPos& newHead);
};

#endif