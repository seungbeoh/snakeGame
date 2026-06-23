// Definition of objPosArrayList class
// objPosArrayList is a heap allocated list to store the size of the snake and to manage the food bucket
// Heap memory persists for the lifetime of the object, freed when destructor is called

// Preprocessors
#include "objPosArrayList.h"
#include <iostream>
using namespace std;

// Default Constructor
objPosArrayList::objPosArrayList() 
{
    listSize = 0;
    arrayCapacity = ARRAY_MAX_CAP;   
    aList = new objPos[ARRAY_MAX_CAP]; 
}

// Destructor
objPosArrayList::~objPosArrayList() 
{
    delete[] aList;
}

// Getters
int objPosArrayList::getSize() const 
{
    return listSize; 
}

objPos objPosArrayList::getHeadElement() const 
{
    return aList[0]; 
}

objPos objPosArrayList::getTailElement() const 
{
    return aList[listSize-1]; 
}

objPos objPosArrayList::getElement(int index) const 
{
    if(index<0 || index >= listSize)
    {
        return objPos();
    }

    return aList[index];
}

// Mutators 
void objPosArrayList::insertHead(objPos thisPos) 
{
    if(listSize == arrayCapacity)
    {
        return;
    }

    for(int i=listSize; i>0; i--)
    {
        aList[i] = aList[i-1]; 
    }

    aList[0] = thisPos; 
    listSize++;
}

void objPosArrayList::insertTail(objPos thisPos) 
{
    if(listSize == arrayCapacity)
    {
        return;
    }
    
    aList[listSize] = thisPos;  
    listSize++;
}

void objPosArrayList::removeTail() 
{
    if(listSize == 0)
    {
        return;
    }

    listSize--;
}

void objPosArrayList::removeHead() 
{
    if(listSize == 0)
    {
        return;
    }

    for(int i=0; i<listSize-1; i++)
    {
        aList[i] = aList[i+1];  
    }
    
    listSize--;                  
}
