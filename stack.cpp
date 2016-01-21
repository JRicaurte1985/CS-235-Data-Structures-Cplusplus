/***********************************************************************
* Program:
*    Assignment 02
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary: Stack class's functions are defined in this file. A Stack
* class is a first in last out data structure. In our Stack class, an
* int array is used to hold the data.
************************************************************************/


#include "stack.h"
#include <iostream>
#include <cstdlib>
using namespace std;



/************************************************************
* Default Constructor - default size is 100
************************************************************/
Stack::Stack(int size)
      :maxSize(size), myTop(-1)
{
   stackItems = new int[size];
}

/************************************************************
* Copy Constructor
************************************************************/
Stack::Stack(const Stack &aStack)
{
   stackItems = new int[aStack.maxSize];
   myTop = aStack.myTop;

   for (int i = 0; i < aStack.myTop + 1; i++)
   {
      stackItems[i] = aStack.stackItems[i];
   }
   
}


/************************************************************
* Destructor
************************************************************/
Stack::~Stack()
{
   delete [] stackItems;
}

/************************************************************
* Top - If stack is empty, returns error message. Else,
* returns value of the element indexed by myTop.
************************************************************/
int Stack::top()
{
   if (empty())
   {
      cout <<"ERROR: Stack Empty\n";
      exit(1);
   }
   else
      return stackItems[myTop];
}
/************************************************************
* Push- If stack is full, displays error message and exits the
* program. If not full, adds the argument 'item' to the top of
* the stack and updates myTop.
************************************************************/
void Stack::push(int item)
{
   if (!full())
   {
      stackItems[myTop + 1] = item;
      myTop++;
   }
   else
   {
      cout << "ERROR: Stack Overflow\n";
      exit(1);
   }
}


/************************************************************
* Pop - if stack is empty, displays error message and exits
* program. Otherwise, will 'remove' the top item of the stack
* by decreasing the value of myTop by 1
************************************************************/
void Stack::pop()
{
   if (empty())
   {
      cout << "Error: Stack Underflow\n";
      exit(1);
   }
   else
      myTop--;
      
}

/************************************************************
* Empty - If stack is empty, returns true. This is done by
* checking the value of myTop. If myTop is less than 0, then
* we know the stack is empty. If not, returns false.
************************************************************/
bool Stack::empty()
{
   if (myTop < 0)
      return true;
   else
      return false; 
}

/************************************************************
* Full - If stack is full, returns true. This is done by
* checking to see if myTop + 1 equals the maxSize. If so,
* returns true. If not, returns false.
************************************************************/
bool Stack::full()
{
   if (myTop + 1 == maxSize)
      return true;
   else
      return false;
}

/************************************************************
* Overloaded Assignment Operator 
************************************************************/
Stack& Stack::operator = (const Stack &rhs)
{
   if (this == &rhs)
      return *this;
   else
   {
      if ((rhs.myTop + 1) > maxSize)
      {
         delete[] stackItems;
         stackItems = new int[rhs.maxSize];
         maxSize = rhs.maxSize;
      }
      for (int i = 0; i < rhs.myTop + 1; i++)
      {
         stackItems[i] = rhs.stackItems[i];
      }
      myTop = rhs.myTop;
      return *this;
   }
}











