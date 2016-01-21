/***********************************************************************
* Program: Node Class
*    Assignment 09  
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary: 
*    This program implements a Node class that we defined. A Node contains
* an int called data and a pointer to another Node called next. We open a 
* file and read in 100 integers one at a time. Each time we read in an   
* integer, we use the Node class to create a Node and store the integer,   
* creating a linked list. The insertion of Nodes to the list is done in
* ascending order of the integer values.
************************************************************************/

#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

/*******************************************************************
 *
 *     FILE: node.h
 *
 *  PURPOSE: Contains the class definition of a Node
 *
 *******************************************************************/
class Node
{
   private:
     int data;                 // --- data in each node
     Node* next;               // --- pointer to next node

   public:
     Node()   {data = 0; next = NULL;}            // --- Creates empty node
     Node* getNext()   {return next;} // --- returns next pointer of a node
     int getData()   {return data;}  // --- returns data of a node
     void setData(int item){data = item;}// stores item in data
     void setNext(Node* node){next = node;} // --- sets next to point to node
};

/**********************************************************************
 * main description- Takes command line parameter of file name to read from.
 * Integers are read in and inserted to the linked list in ascending order.
 * The list is then displayed.
 ***********************************************************************/
int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      cerr << "Usage: " << argv[0] << " FILE NAME\n";
      return 1;
   }
   
   else
   {
      ifstream inFile;
      inFile.open (argv[1]);
      if (inFile.fail())
      {
         cout << "\nFile not found\n";
         return 1;
      }
      int num;
      Node *head = NULL;
      Node *tail;
      Node *tempNode; // node creator 
      Node *p1; // traversal pointer
      
      while (inFile >> num)
      {
         tempNode = new Node;
         tempNode->setData(num);
         
         // insert first item to head
         if (head == NULL)
         {
            head = tempNode;
            tail = tempNode;
         }
         // insert at head
         else if (num <= head->getData())
         {
            tempNode->setNext(head);
            head = tempNode;
         }
         // insert at tail
         else if (num >= tail->getData())
         {
            tail->setNext(tempNode);
            tail = tempNode;
         }
         //insert in between 2 nodes. Only runs when at least 2 items in list
         else
         {
            p1 = head;
            //Traverse list until insertion point found 
            while (num > p1->getNext()->getData())
               p1 = p1->getNext();
            
            tempNode->setNext(p1->getNext());
            p1->setNext(tempNode);
         }
      }
      
      p1 = head; // reset p1 to head for display
      int count = 0;
      while (p1 != NULL)
      {
         if (count != 0 && count % 20 == 0)
            cout << endl;
         
         cout << setw(3) << p1->getData();
         p1 = p1->getNext();
         count++;
      }
      
      cout << endl;
      p1 = head; //reset p1 to head for upcoming deletion
      while (head != NULL)
      {
         p1 = p1->getNext();
         delete head;
         head = p1;
      }
         
      inFile.close();
   }
}
