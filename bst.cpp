/***********************************************************************
* Program:
*    Assignment 14 Binary Search Tree - Class
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary:
* Using the BTree class already made, I've created a new class called
* BST (short for Binary Search Tree). This class implements new functions
* such as search, insert, remove, empty, etc. These tools help create 
* functional Binary Search Tree objects.   
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
      void insertRight(int item);//creates a new node and inserts node to right
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

class BST
{
   private:
      BTree* root;
   
   public:
      BST();
      int empty(void);
      BTree* search(int item);
      void insert(int item);
      void remove(int item);
      void BSTInfix(void);
};

/**********************************************************************
 * BTree::default constructor
 ***********************************************************************/
BTree::BTree(int data)
{
   left = NULL;
   right = NULL;
   parent = NULL;
   this->data = data;
}

/**********************************************************************
 * BTree::destructor 
 ***********************************************************************/
BTree::~BTree()
{
   //Left Blank Intentionally
}

/**********************************************************************
 * BTree::insertLeft
 ***********************************************************************/
void BTree::insertLeft(int item)
{
   left = new BTree(item);
   left->parent = this;
}

/**********************************************************************
 * BTree::insertRight
 ***********************************************************************/
void BTree::insertRight(int item)
{
   right = new BTree(item);
   right->parent = this;
}

/**********************************************************************
 * BTree::getLeftChild
 ***********************************************************************/
BTree* BTree::getLeftChild(void)
{
   return left;
}

/**********************************************************************
 * BTree::getRightChild
 ***********************************************************************/
BTree* BTree::getRightChild(void)
{
   return right;
}

/**********************************************************************
 * BTree::getParent
 ***********************************************************************/
BTree* BTree::getParent(void)
{
   return parent;
}

/**********************************************************************
 * BTree::getData
 ***********************************************************************/
int BTree::getData(void)
{
   return data;
}

/**********************************************************************
 * BTree::setData
 ***********************************************************************/
void BTree::setData(int item)
{
   data = item;
}

/**********************************************************************
 * BTree::setLeft
 ***********************************************************************/
void BTree::setLeft(BTree* tree)
{
   left = tree;
   if (tree != NULL)
      tree->parent = this;
}

/**********************************************************************
 * BTree::setRight
 ***********************************************************************/
void BTree::setRight(BTree* tree)
{
   right = tree;
   if (tree != NULL)
      tree->parent = this;
}

/**********************************************************************
 * BTree::infix
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
 * BTree::prefix
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
 * BTree::postfix
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
 * BTree::level
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

/**********************************************************************
 * BST::default constructor
 ***********************************************************************/
BST::BST()
{
   root == NULL;
}

/**********************************************************************
 * BST::empty
 ***********************************************************************/
int BST::empty()
{
   return (root == NULL);
}

/**********************************************************************
 * BST::search - searches for item in BST. Returns NULL if not found or
 * BTree pointer to correct node containing item
 ***********************************************************************/
BTree* BST::search(int item)
{
   BTree* ptr = root;

   while (ptr != NULL)
   {
      if (item == ptr->getData())
         return ptr;
      else if (item > ptr->getData())
         ptr = ptr->getRightChild();
      else 
         ptr = ptr->getLeftChild();
   }
   return NULL;
}

/**********************************************************************
 * BST::insert - inserts node in proper position of Binary Search Tree
 ***********************************************************************/
void BST::insert(int item)
{
   if (root == NULL)
   {
      root = new BTree(item);
      return;
   }

   BTree* ptr = root;
   BTree* tmp = new BTree(item); // prepare new node to insert

   //traverse tree, go left if item <= data, right if >, insert when next move
   //would point to NULL
   while (true)
   {
      if (item <= ptr->getData())
         if (ptr->getLeftChild() != NULL)
            ptr = ptr->getLeftChild();
         else
         {
            ptr->setLeft(tmp);
            break;
         }
          
      else   // item is > data
         if (ptr->getRightChild() != NULL)
            ptr = ptr->getRightChild();
         else
         {
            ptr->setRight(tmp);
            break;
         }         
   }
}

/**********************************************************************
 * BST::remove - removes a node of the BST
 ***********************************************************************/
void BST::remove(int item)
{
   BTree* ptr = search(item); // get ptr to node that needs to be deleted

   // if item was not found
   if (ptr == NULL)
      cout << "Item " << item << " is not found, cannot delete it!\n";
   else // we are at the correct node to delete. 3 cases to handle
   {
      //delete leaf node with no children
      if (ptr->getRightChild() == NULL && ptr->getLeftChild() == NULL)
      {
         if (ptr->getData() > ptr->getParent()->getData())
            ptr->getParent()->setRight(NULL);
         else
            ptr->getParent()->setLeft(NULL);
         delete ptr;
      }
      
      //delete node with 2 children
      else if (ptr->getRightChild() != NULL && ptr->getLeftChild() != NULL)
      {
         BTree* successor = ptr->getRightChild();
         
         //get successor to point to in-order successor (IOS)
         while (successor->getLeftChild() != NULL)
            successor = successor->getLeftChild();
         
         ptr->setData(successor->getData()); // swap values
         
         //if IOS has 1 child, link ptr to IOS right child
         if (ptr->getRightChild()->getLeftChild() == NULL)
            ptr->setRight(successor->getRightChild()); 
         else // IOS has 0 children
            //set IOS parent's left to NULL before deleting IOS
            successor->getParent()->setLeft(NULL);
         delete successor;
      }
      
      //delete node with 1 child
      else
      {
         BTree* child;
         BTree* parent = ptr->getParent();
         //determine which side is child on
         if (ptr->getLeftChild() != NULL)
            child = ptr->getLeftChild();
         else
            child = ptr->getRightChild();
         //determine which pointer of parent node to link to child
         if (child->getData() > parent->getData())
            parent->setRight(child);
         else
            parent->setLeft(child);
      }
   }  
}

/**********************************************************************
 * BST::BSTInfix - infix traversal
 ***********************************************************************/
void BST::BSTInfix()
{
   root->infix(); 
}
