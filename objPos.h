// Declaration of objPos class

// Preprocessors
#ifndef OBJPOS_H
#define OBJPOS_H


// Declare "objPos" class
class objPos
{
    private:
        int x;
        int y;
        char symbol;

    public:
        // Constructors
        objPos();
        objPos(int xPos, int yPos, char sym);
        objPos(const objPos& o); 

        // Copy Assignment Operator
        objPos& operator=(const objPos& o); 

        // Destructor
        ~objPos(); 
        
        // Setters
        void setObjPos(objPos o);        
        void setObjPos(int xPos, int yPos, char sym);  

        // Getters
        objPos getObjPos() const;
        char getSymbol() const;
        int getX() const;
        int getY() const;
        bool isPosEqual(const objPos* refPos) const;
        char getSymbolIfPosEqual(const objPos* refPos) const;
};

#endif