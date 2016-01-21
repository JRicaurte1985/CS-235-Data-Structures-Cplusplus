/***********************************************************************
* Program:
*    Assignment 13
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary: 
*   BTree Class header and definitions
*       
************************************************************************/

using namespace std;
#include <iostream>

class BTree
{
   private:
      int data;          // --- data stored in node of tree
      BTree* left;       // --- pointer to left subtree
      BTree* right;      // --- pointer to right subtree
      BTree* parent;     // --- pointer to the parent node;

   public:
      BTree(int data = 0);  
      ~BTree(void);
      void insertLeft(int item); // creates a new node and inserts node to left
      void insertRight(int item);// creates a new node and inserts node to right
      BTree* getLeftChild(void);     // return the ptr to the left child
      BTree* getRightChild(void);    // return the ptr to the right child
      BTree* getParent(void);        // return parent
      int getData(void);
      void setData(int item);
      void setLeft(BTree* tree);     
      void setRight(BTree* tree);
      void infix(void);              // do infix traversal
      void prefix(void);             // do prefix traversal
      void postfix(void);            // do postfix traversal
      void level(void);              // do level order traversal
};


/**********************************************************************
 * default constructor
 ***********************************************************************/
BTree::BTree(int data)
{
   left = NULL;
   right = NULL;
   parent = NULL;
   this->data = data;
}

/**********************************************************************
 * insertLeft
 ***********************************************************************/
void BTree::insertLeft(int item)
{
   left = new BTree(item);
   left->parent = this;
}

/**********************************************************************
 * insertRight
 ***********************************************************************/
void BTree::insertRight(int item)
{
   right = new BTree(item);
   right->parent = this;
}

/**********************************************************************
 * getLeftChild
 ***********************************************************************/
BTree* BTree::getLeftChild(void)
{
   return left;
}

/**********************************************************************
 * getRightChild
 ***********************************************************************/
BTree* BTree::getRightChild(void)
{
   return right;
}

/**********************************************************************
 * getParent
 ***********************************************************************/
BTree* BTree::getParent(void)
{
   return parent;
}

/**********************************************************************
 * getData
 ***********************************************************************/
int BTree::getData(void)
{
   return data;
}

/**********************************************************************
 * setData
 ***********************************************************************/
void BTree::setData(int item)
{
   data = item;
}

/**********************************************************************
 * setLeft
 ***********************************************************************/
void BTree::setLeft(BTree* tree)
{
   left = tree;
   if (tree != NULL)
      tree->parent = this;
}

/**********************************************************************
 * setRight
 ***********************************************************************/
void BTree::setRight(BTree* tree)
{
   right = tree;
   if (tree != NULL)
      tree->parent = this;
}

/**********************************************************************
 * infix
 ***********************************************************************/
void BTree::infix(void)
{
   if (left != NULL)
      left->infix();
   
   cout << data << " ";
   
   if (right != NULL)
      right->infix();
}

/**********************************************************************
 * prefix
 ***********************************************************************/
void BTree::prefix(void)
{
   cout << data << " ";
   
   if (left != NULL)
      left->prefix();   
   if (right != NULL)
      right->prefix();
}

/**********************************************************************
 * postfix
 ***********************************************************************/
void BTree::postfix(void)
{
   if (left != NULL)
      left->postfix(); 
   if (right != NULL)
      right->postfix();

   cout << data << " ";
}

/**********************************************************************
 * level
 ***********************************************************************/
void BTree::level(void)
{
   const int MAX = 50;
   BTree *queue[MAX];
   BTree *temp;
   int front = 0;
   int back = 0;

   queue[back++] = this;

   while (front != back)
   {
      temp = queue[front];
      front = (front + 1) % MAX;
      if (temp != NULL)
      {
         // visit
         cout.width(4);
         cout << temp->data << " ";
         if (temp->parent == NULL)
            cout << " Parent = NULL! " << endl;
         else
            cout << " Parent = " << temp->parent->data << "   " << endl;
         // end Visit        
         queue[back] = temp->left;
         back = (back + 1) % MAX;
         queue[back] = temp->right;
         back = (back + 1) % MAX;
      }
   }
}
