// Declaration of GameMechs class

#ifndef GAMEMECHS_H
#define GAMEMECHS_H

#include <cstdlib>
#include <time.h>
#include "objPos.h"

using namespace std;

class GameMechs
{
    private:
        char input;
        bool exitFlag;
        bool loseFlag;
        int score;
        int boardSizeX;
        int boardSizeY;

    public:
        // Constructors
        GameMechs();
        GameMechs(int boardX, int boardY);

        // Destructor
        ~GameMechs();

        // Setters
        void setInput(char this_input);
        void setExitTrue();
        void setLoseFlag();
        void clearInput();

        // Getters
        bool getExitFlagStatus() const;
        bool getLoseFlagStatus() const; 
        char getInput() const;
        int getBoardSizeX() const;
        int getBoardSizeY() const;
        int getScore() const;

        // Method
        void incrementScore();
};

#endif