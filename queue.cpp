/***********************************************************************
* Program:
*    Assignment 04, Queue Library
*    Brother Cameron, CS 235
* Author:
*    Greg Cameron
*    Modified by Brother Ercanbrack 4/27/07 - added copy constructor
*       and overloaded assignment operator
*    Modified 1/25/13 - fixed bug - copy constructor and overloaded assignment
*                       operator  need to loop to maxSize rather than numItems. 
*                        Removed - MAXQUE test from default constructor .  
* Summary: 
*    This is a set of function definitions belonging to the Class
* definition contained in queue.h.  These functions are used to
* perform the various operations of a queue.
***********************************************************************/
using namespace std;
#include <iostream>
#include <cstdlib>
#include "queue.h"

/**********************************************************************
 * default constructor
 **********************************************************************/
template <class T>
Queue<T>::Queue(int size)    
{
   maxSize = size > 0 ? size : 100;    // if s  is negative, set queue size to 100
   numItems = 0;
   back = front = maxSize - 1;
   queueItems = new T[maxSize];
}

/**********************************************************************
 * destructor
 **********************************************************************/
template <class T>
Queue<T>::~Queue(void)
{
   delete [] queueItems;
}

/***********************************************************************
 * Queue Copy Constructor
 ***********************************************************************/
template <class T>
Queue<T>::Queue(const Queue &aQueue)
{
   maxSize = aQueue.maxSize;
   numItems = aQueue.numItems;
   front = aQueue.front;
   back = aQueue.back;
   queueItems = new T[maxSize];
   for (int i = 0; i < maxSize; i++)
   {
      queueItems[i] = aQueue.queueItems[i];
   }
}

/***********************************************************************
 * Overloaded assignment operator.
 ***********************************************************************/
template <class T>
Queue<T>& Queue<T>::operator = (const Queue<T> &rtSide)
{
   if (this != &rtSide)
   {
   
      if( maxSize != rtSide.maxSize)
      {
         delete [] queueItems;
         queueItems = new T[rtSide.maxSize];
      }
   
      for (int i = 0; i < rtSide.maxSize; i++)
      {
         queueItems[i] = rtSide.queueItems[i];
      }
      maxSize = rtSide.maxSize;   //max size of queue
      numItems = rtSide.numItems; //number of items in queue
      back = rtSide.back;
      front = rtSide.front;
   }
   return *this;
}


/**********************************************************************
 * returns true if queue is empty
 **********************************************************************/
template <class T>
int Queue<T>::empty(void)
{
   return (numItems == 0);
}

/**********************************************************************
 * returns true if queue is full
 **********************************************************************/
template <class T>
int Queue<T>::full(void) const
{
   return (numItems == maxSize);
}

/**********************************************************************
 * inserts item into back of queue, then increments number of items
 * in queue
 **********************************************************************/
template <class T>
void Queue<T>::insert(T const &item)
{
   // --- check for overflow
   if (full())
   {
      cout << "Queue overflow" << endl;
      exit(1);
   }
   queueItems[back] = item;
   back = (back + 1) % maxSize;
   numItems++;
}

/**********************************************************************
 * removes item from front of queue, then decrements number of items
 * in queue
 **********************************************************************/
template <class T>
T Queue<T>::remove(void)
{
   T temp;
   
   if (empty())
   {
      cout << "queue underflow" << endl;
      exit(1);
   }
   temp = queueItems[front];
   front = (front + 1) % maxSize;
   numItems--;
   return (temp);
   
}
