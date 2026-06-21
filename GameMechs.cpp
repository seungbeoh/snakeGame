// Definition of GameMechs class
// Stores game state

// Preprocessors
#include "GameMechs.h"

GameMechs::GameMechs() // Default constructor
{
    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = 30;
    boardSizeY = 15;
}

GameMechs::GameMechs(int boardX, int boardY) // Parametrized constructor
{
    input = '\0';
    exitFlag = false;
    loseFlag = false;
    score = 0;
    boardSizeX = boardX;
    boardSizeY = boardY;
}

GameMechs::~GameMechs() // Destructor
{
}

// Getters
bool GameMechs::getExitFlagStatus() const 
{
    return exitFlag;
}
bool GameMechs::getLoseFlagStatus() const 
{
    return loseFlag;
}

char GameMechs::getInput() const 
{
    return input;
}

int GameMechs::getBoardSizeX() const 
{ 
    return boardSizeX;
}

int GameMechs::getBoardSizeY() const 
{
    return boardSizeY;
}

int GameMechs::getScore() const 
{
    return score;
}

// Setters
void GameMechs::setExitTrue()  
{
    exitFlag = true;
}
void GameMechs::setLoseFlag() 
{
    loseFlag = true;
}

void GameMechs::setInput(char this_input)  
{
    input = this_input;
}
void GameMechs::clearInput()  
{
    input = '\0';
}

// Mutator
void GameMechs::incrementScore() 
{
    score++;
}