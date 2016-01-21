/***********************************************************************
* Program:
*    Assignment 12 Fibonacci Program
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary: Node class altered to be a template class. List class modified
* to be a Doubly Linked List class that is also a template class. Fib class 
* created to make Fibonacci numbers. Fib object consists of a DLList object
* called fibNumber to hold the Fibonacci number and an int called fibSubScript
* to hold the subscript. setFibNumber() is used to calculate the n-th
* Fibonacci number.
************************************************************************/
#include <iomanip>
#include <cstdlib>
#include <iostream>
#include <time.h>
#include <fstream>
using namespace std;

template <class T>
class Node
{
   private:
      T data;                 // --- data in each node
      Node<T>* next;          // --- pointer to next node
      Node<T>* previous;      // --- pointer to previous node
   public:
      Node();                 // --- Creates empty node
      Node<T>* getNext();     // --- returns next pointer of a node
      Node<T>* getPrevious(); // --- returns previous pointer of a node
      T getData();            // --- returns data of a node
      void setData(T item);   // ---stores item in data member of current node
      void setNext(Node<T>* node); // --- sets next to point to node
      void setPrevious(Node<T>* node); // --- sets previous to point to node
};

template <class T>
class DLList
{
   private:
      int numItems;
      Node<T>* firstNode;
  
   public:
      DLList();
      ~DLList();
      DLList(const DLList &listToCopy);  
      DLList& operator = (const DLList &rightSide);
      void insert(T item, int pos);
      void remove(int pos);
      int lookup(T item) const;
      T getData(int pos) const;
      int empty(void) const;
      int getNumItems(void) const;
      Node<T>* getFirstNode()   {return firstNode;}
      void clear(); // used to erase list(delete nodes), reset numItems to 0
};

class Fib
{
private:
   int fibSubscript;
   DLList<int> fibNumber;
public:
   Fib();
   Fib(int n);
   Fib(const Fib &rhs);
   Fib& operator = (const Fib &rhs);
   void setFibNumber(int n);
   void display();
   int getFibSubscript() {return fibSubscript;}
   void clear();
};
   
/**********************************************************************
 * Node constructor
 ***********************************************************************/
template <class T>
Node<T>::Node()
{
   next = NULL;
   previous = NULL;
}

/**********************************************************************
 * Node - getNext
 ***********************************************************************/
template <class T>
Node<T>* Node<T>::getNext()
{
   return next;
}

/**********************************************************************
 * Node - getPrevious
 ***********************************************************************/
template <class T>
Node<T>* Node<T>::getPrevious()
{
   return previous;
}
/**********************************************************************
 * Node - getData
 ***********************************************************************/
template <class T>
T Node<T>::getData()
{
   return data;
}

/**********************************************************************
 * Node - setData
 ***********************************************************************/
template <class T>
void Node<T>::setData(T item)
{
   data = item;
}

/**********************************************************************
 * Node setNext
 ***********************************************************************/
template <class T>
void Node<T>::setNext(Node<T>* node)
{
   next = node;
}

/**********************************************************************
 * Node setPrevious
 ***********************************************************************/
template <class T>
void Node<T>::setPrevious(Node<T>* node)
{
   previous = node;
}

/**********************************************************************
 * DLList - default constructor
 ***********************************************************************/
template <class T>
DLList<T>::DLList()
{
   numItems = 0;
   firstNode = NULL;
}

/**********************************************************************
 * DLList - destructor
 ***********************************************************************/
template <class T>
DLList<T>::~DLList()
{
   Node<T>* p1 = firstNode;
   while (firstNode != NULL)
   {
      p1 = p1->getNext();
      delete firstNode;
      firstNode = p1;
   }
}

/**********************************************************************
 * DLList- copy constructor
 ***********************************************************************/
template <class T>
DLList<T>::DLList(const DLList<T> &listToCopy)
{
   numItems = listToCopy.numItems;
   //if empty list
   if (listToCopy.firstNode == NULL)
   {
      firstNode = NULL;
      return;
   }
   
   Node<T>* rhs = listToCopy.firstNode;
   Node<T>* trav = new Node<T>;
   trav->setData(rhs->getData());
   firstNode = trav;
   rhs = rhs->getNext();
   
   while (rhs != NULL)
   {
      trav->setNext(new Node<T>);
      trav->getNext()->setPrevious(trav);
      trav = trav->getNext();
      trav->setData(rhs->getData());
      rhs = rhs->getNext();
   }
}

/**********************************************************************
 * DLList - assignment operator overload
 ***********************************************************************/
template <class T>
DLList<T>& DLList<T>::operator = (const DLList<T> &rightSide)
{
   if (this == &rightSide)
      return *this;
   else
   {
      numItems = rightSide.numItems;
      this->~DLList<T>(); // delete old list
     
      if (rightSide.firstNode == NULL) // if rightSide is empty, done here.
         return *this;
      
      else    // traverse rightSide and copy its Nodes to calling object. 
      {
         Node<T>* rhs = rightSide.firstNode;
         Node<T>* trav = new Node<T>; 
         trav->setData(rhs->getData()); // assign first node data
         firstNode = trav; // firstNode is now set. Doesnt change after this
         rhs = rhs->getNext();
   
         while (rhs != NULL) 
         {
            trav->setNext(new Node<T>);
            trav->getNext()->setPrevious(trav);
            trav = trav->getNext();
            trav->setData(rhs->getData());
            rhs = rhs->getNext();
         }
      }
      return *this;
   }
}

/**********************************************************************
 * DLList::insert - insert item at pos
 ***********************************************************************/
template <class T>
void DLList<T>::insert(T item, int pos) 
{
   // Check pos to see if it is negative
   if (pos < 0)
   {
      cout << "Invalid position. List cannot have negative index.";
      exit(1);
   }
   else 
   {
      Node<T>* trav = firstNode; // traversal pointer
      Node<T>* temp = new Node<T>;     //create node and fill with item
      temp->setData(item);
      
      if (pos > numItems) // if pos > list size, set pos for tail insert
         pos = numItems;

      if (pos == 0) // head insert
      {
         if (firstNode != NULL) // make sure list not empty 
         {
            temp->setNext(firstNode);
            firstNode->setPrevious(temp);
         }
         firstNode = temp;
      }
      else if (pos == numItems) // tail insert
      {
         for (int i = 0; i < pos - 1; i++)
            trav = trav->getNext();
         
         trav->setNext(temp);
         temp->setPrevious(trav);
      }
      else //any inserts in between nodes
      {
         for (int i = 0; i < pos - 1; i++)
            trav = trav->getNext();
         
         temp->setNext(trav->getNext());
         temp->setPrevious(trav);
         trav->setNext(temp);
         temp->getNext()->setPrevious(temp);
      }
      numItems++;
   }
}

/**********************************************************************
 * DLList::remove - remove item at pos
 ***********************************************************************/
template <class T>
void DLList<T>::remove(int pos)
{
   if (pos < 0)
      cout << "Index cannot be negative\n";
   else if (empty())
      cout << "Could not remove: Empty list!\n";
   else
   {
      // If pos argument exceeds list size, set pos to last item in list
      if (pos >= numItems)
         pos = numItems - 1;
      
      Node<T>* trav = firstNode;
      if (pos == 0) // delete head
      { 
         firstNode = firstNode->getNext();
         delete trav;
         if (firstNode != NULL)
            firstNode->setPrevious(NULL);  
      }
      else
      {
         // traverse list and assign trav to remove index.
         for (int i = 0; i < pos; i++)
            trav = trav->getNext();
         
         trav->getPrevious()->setNext(trav->getNext());
         
         if (trav->getNext() != NULL)
            trav->getNext()->setPrevious(trav->getPrevious());
        
         delete trav;
      }
      numItems--;
   }
}

/**********************************************************************
 * DLList::lookup - returns index of T. If not found, returns -1
 ***********************************************************************/
template <class T>
int DLList<T>::lookup(T item) const
{
  
   Node<T>* trav = firstNode;
   int index = 0;
   for (int i = 0; i < numItems; i++)
   {
      if (trav->getData() == item)
         return index;
      else
      {
         trav = trav->getNext();
         index++;
      }
   }
   return -1;  
}

/**********************************************************************
 * DLList::getData - returns data at pos
 ***********************************************************************/
template <class T>
T DLList<T>::getData(int pos) const
{
   if (pos < 0 || pos >= numItems)
   {
      cout << "Could not retrieve data: List does not contain that index";
   }
   else if (empty())
      cout << "Could not retrieve data: Empty list\n";
   else
   {
      Node<T>* trav = firstNode;
      for (int i = 0; i < pos; i++)
         trav = trav->getNext();
      return trav->getData();
   }     
}

/**********************************************************************
 * DLList::empty - check if DLList is empty.  
 ***********************************************************************/
template <class T>
int DLList<T>::empty() const
{
   if (firstNode == NULL)
      return 1;
   else
      return 0;
}

/**********************************************************************
 * DLList::getNumItems
 ***********************************************************************/
template <class T>
int DLList<T>::getNumItems() const
{
   return numItems;
}

/**********************************************************************
 * DLList::clear -  calls destructor to delete entire list. Resets variables
 ***********************************************************************/
template <class T>
void DLList<T>::clear()
{
   this->~DLList<T>();
   firstNode = NULL;
   numItems  = 0;
}

/**********************************************************************
 * Fib - default constructor
 ***********************************************************************/
Fib::Fib()
{
   fibSubscript = 0;
}

/**********************************************************************
 * Fib - secondary constructor - allows you to initialize an n-th Fibonacci #
 ***********************************************************************/
Fib::Fib(int n)
{
   setFibNumber(n);
}
/**********************************************************************
 * Fib - copy constructor
 ***********************************************************************/
Fib::Fib(const Fib &rhs)
{
   fibSubscript = rhs.fibSubscript;
   fibNumber = rhs.fibNumber;
}

/**********************************************************************
 * Fib - overloaded assignment operator
 ***********************************************************************/
Fib& Fib::operator = (const Fib &rhs)
{
   fibSubscript = rhs.fibSubscript;
   fibNumber = rhs.fibNumber;
   return *this;
}

/**********************************************************************
 * Fib - setFibNumber
 * Inputs: n (int)
 * Calculates the n-th Fibonacci number 
 ***********************************************************************/
void Fib::setFibNumber(int n)
{
   if (n < 1)
   {
      cout << "Fibonacci subscript cannot be less than 1\n";
      return;
   }
    /*need to clear fibNumber. setFibNumber() may be called several times on an     object and you would have problems if you didn't erase all previous data*/
   fibNumber.clear();
   fibNumber.insert(1,0); // fibNumber will start as f1. f1 = 1;
   fibSubscript = n;
   
   if (n < 3) // can return here if n is 1 or 2. 
      return;
   
   DLList<int> f2;
   f2.insert(1,0); // fibNumber(aka f1) = 1 and f2 = 1. We are rdy to start.
   Node<int>* p1;// traversal pointers for DLList objects fibNumber(f1) and f2
   Node<int>* p2;
   int temp = 0; // used as f1's node value placeholder. 
   int carry = 0;

   for (int i = 0; i < n - 2; i++) //run n - 2 times. f1 and f2 done already
   {
      //reset pointers to respective beginnings of lists. reset carry to 0
      p1 = fibNumber.getFirstNode();
      p2 = f2.getFirstNode();
      carry = 0;
      //Add both lists. fibNumber becomes sum, f2 becomes what fibNumber was
      while (p1 != NULL) 
      {
         temp = p1->getData();
         p1->setData((p1->getData() + p2->getData() + carry) % 1000000000); 
         carry = (temp + p2->getData()) / 1000000000;
         p2->setData(temp);
         p1 = p1->getNext();
         p2 = p2->getNext();
      }
      if (carry == 1) // Account for carry on addition of final nodes.
      {
         fibNumber.insert(1, fibNumber.getNumItems());
         f2.insert(0, f2.getNumItems());
      }
   }      
}

/**********************************************************************
 * Fib::display() - Displays the Fibonacci number.
 ***********************************************************************/
void Fib::display()
{   
   if (fibSubscript == 0)
   {
      cout << "Use setFibNumber() to initialize object\n";
      return;
   }
   Node<int>* trav = fibNumber.getFirstNode();
   
   while (trav->getNext() != NULL) // traverse to the end of the list
      trav = trav->getNext();
   
   cout << trav->getData();//display most significant node without setw/setfill
   trav = trav->getPrevious();
   
   while (trav != NULL) //traverse list in reverse and display w/ setw/setfill
   {
      cout << setw(9) << setfill('0') << trav->getData();
      trav = trav->getPrevious();
   }
   
}
/**********************************************************************
 * main -Displays the n-th Fibonacci number based on the command line parameter
 ***********************************************************************/
int main(int argc, char *argv[])
{
    if (argc != 2)
   {
      cerr << "Usage: " << argv[0] << " Fibonacci Subscript\n";
      return 1;
   }
   else
   {   
      //clock_t tStart = clock();
      Fib num(atoi(argv[1]));
      num.display();
      cout << endl << endl;
      //cout << "Elapsed Time: " << (double)(clock() - tStart)/CLOCKS_PER_SEC
      //     << " seconds\n";
      return 0;
   }
}





