/***********************************************************************
 * Program:
 *    Assignment 04, Queue Header File
 *    Brother Cameron, CS 235
 * Author:
 *    Greg Cameron
 *    modified by Brother Ercanbrack 5/19/06
 * Summary: 
 *    This is the class definition for queue
 ***********************************************************************/

#ifndef _QUEUE_H
#define _QUEUE_H

using namespace std;
#include <iostream>

template <class T>
class Queue
{
   private:
      int front;                  // --- index of front of queue
      int back;                   // --- index of back of queue
      int maxSize;                // --- max storage capacity of array
      int numItems;               // --- number of items currently in queue
      T *queueItems;            // --- array containing queue items
  
   public:
      Queue(int size = 5);           // --- constructor
      Queue(const Queue &aQueue); //  copy constructor
      ~Queue(void);               // --- destructor
      int getItems()const   {return numItems;}
      int getMax() const   {return maxSize;}
      void insert(T const &item);      // --- insert item into back of queue
      T remove(void);           // --- remove item from front of queue
      int empty(void);            // --- returns 1 if queue is empty, 0 otherwise
      int full(void) const;             // --- returns 1 if queue is full, 0 otherwise
      Queue& operator = (const Queue &rtSide); // overloaded assignment operator
};

#endif
