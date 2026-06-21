// Definition of objPos class
// Represents relevant positions throughout the game board (snake position, food position, etc)

// Preprocessors
#include "objPos.h"

// Constructors
objPos::objPos() 
{
    x = 0;
    y = 0;
    symbol = 0;
}

objPos::objPos(int xPos, int yPos, char sym)  
{
    x = xPos;
    y = yPos;
    symbol = sym;
}

objPos::objPos(const objPos& o) 
{
    x = o.x;
    y = o.y;
    symbol = o.symbol;
}

// Copy Assignment Operator
objPos& objPos::operator=(const objPos& o) 

{
    if (this != &o)
    {
        x = o.x;
        y = o.y;
        symbol = o.symbol;
    }
    return *this;
}

// Destructor
objPos::~objPos() 
{
}

// Setters
void objPos::setObjPos(objPos o)  
{
    x = o.x;
    y = o.y;
    symbol = o.symbol;
}

void objPos::setObjPos(int xPos, int yPos, char sym)  
{
    x = xPos;
    y = yPos;
    symbol = sym;
}

// Getters
objPos objPos::getObjPos() const 
{
    objPos returnPos;
    returnPos.x = x;
    returnPos.y = y;
    returnPos.symbol = symbol;
    return returnPos;
}

char objPos::getSymbol() const  
{
    return symbol;
}

int objPos::getX() const 
{
    return x;
}

int objPos::getY() const  
{
    return y;
}

bool objPos::isPosEqual(const objPos* refPos) const  
{
    if(refPos == nullptr)
    {
        return false;
    }
    return (refPos->x == x && refPos->y == y);
}

char objPos::getSymbolIfPosEqual(const objPos* refPos) const  
{
    if(isPosEqual(refPos))
    {
        return symbol;
    }
    else
        return 0;
}