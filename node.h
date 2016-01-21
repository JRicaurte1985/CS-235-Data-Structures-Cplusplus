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


