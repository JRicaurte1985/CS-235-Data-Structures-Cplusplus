/***********************************************************************
* Program:
*    Assignment 15
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary: We perform Huffman encoding on the letters A - Z.
* We read the frequencies from a file, then create a Huffman Tree.
* We encode the Huffman Tree, then print out the letters and their prefix code
* In order to prevent memory leaks, I created a program specific destructor.
* Since in this program 'BTree' does not use any 'remove node' functions,
* the destructor is sufficient to prevent memory leaks in main.
************************************************************************/
#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

class BTree
{
   private:
      int data;          // --- data stored in node of tree (frequency)
      char letter;       // --- letter value for node
      BTree* left;       // --- pointer to left subtree
      BTree* right;      // --- pointer to right subtree
      BTree* parent;     // --- pointer to the parent node;

   public:
      BTree(int data = 0, char letter = NULL);
      ~BTree(void); // destructor wont work with BST, just this program
      void insertLeft(int item, char ltr); //inserts new node to left
      void insertRight(int item, char ltr);//inserts new node to right
      BTree* getLeftChild(void);     // return the ptr to the left child
      BTree* getRightChild(void);    // return the ptr to the right child
      BTree* getParent(void);          // return parent
      char getLetter()   {return letter;}
      int getData(void);
      void setLetter(char l)   {letter = l;}
      void setData(int item);
      void setLeft(BTree* tree);     
      void setRight(BTree* tree);
      void infix(void);              // do infix traversal
      void prefix(void);             // do prefix traversal
      void postfix(void);            // do postfix traversal
      void level(void);              // do level order traversal
};

bool sortByFreq (BTree* lhs, BTree* rhs) // needed for STL sort 3rd parameter
{
   return lhs->getData() <= rhs->getData();
}

struct HuffmanData // basic building block for our table
{
   string prefixCode;
   char letter;
   bool operator < (const HuffmanData &rhs) const {return letter < rhs.letter;}
};
//encodes the Huffman Tree
void encodingHuffman(BTree *tree, string code, vector<HuffmanData> &data);

/**********************************************************************
 * BTree::default constructor
 ***********************************************************************/
BTree::BTree(int data, char letter)
{
   left = NULL;
   right = NULL;
   parent = NULL;
   this->data = data;
   this->letter = letter;
}

/**********************************************************************
 * BTree::destructor 
 ***********************************************************************/
BTree::~BTree()
{
   delete left;
   delete right;
}

/**********************************************************************
 * BTree::insertLeft
 ***********************************************************************/
void BTree::insertLeft(int item, char ltr)
{
   left = new BTree(item, ltr);
   left->parent = this;
}

/**********************************************************************
 * BTree::insertRight
 ***********************************************************************/
void BTree::insertRight(int item, char ltr)
{
   right = new BTree(item, ltr);
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
int BTree::getData (void) 
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
 * main description
 * Reads frequencies from a file. These correspond to the letters A-Z.
 * Creates a Huffman binary tree. Derives a Huffman coding for the letters.
 ***********************************************************************/
int main()
{
   ifstream fin("/home/cs235/assign15/assign15.in");
   if (fin.fail())
   {
      cout << "\nFile not found\n";
      return 1;
   }
   const int SIZE = 26;
   BTree* temp;
   vector<BTree*> nodes; // this list will hold the nodes
   nodes.resize(SIZE);
   int freq;
   char ltr = 'a';
   string hCode;
   vector<HuffmanData> table; //this table will be loaded with the prefix codes
   
   //load vector with nodes
   for (int i = 0; i < SIZE; i++)
   {
      fin >> freq;  
      nodes[i] = new BTree(freq, ltr + i);
   }
   // if vector is SIZE long, total unions is SIZE - 1. 
   for (int i = 0; i < SIZE - 1; i++)
   {
      //sort so smallest and next smallest are at index 0, 1
      sort(nodes.begin(), nodes.end(), sortByFreq);
      //make temp node with freq of smallest + next smallest
      temp = new BTree(nodes[0]->getData() + nodes[1]->getData());
      //set smallest as left child of temp, next smallest as right child
      temp->setLeft(nodes[0]);
      temp->setRight(nodes[1]);
      //pop front element from vector, have next smallest point to temp
      nodes.erase(nodes.begin());
      nodes[0] = temp;
   }
   
   BTree *hTree =  nodes.front(); //first index has the completed Huffman Tree
   encodingHuffman(hTree, hCode, table); // encoding creates the table
   sort(table.begin(), table.end()); 

   //display the table
   for (int i = 0; i < table.size(); i++)
      cout << table[i].letter << " = " << table[i].prefixCode << endl;
      
   fin.close();    
   return 0;
}

/**********************************************************************
 * encodingHuffman - this function traverses a Huffman Tree and
 * adds letters and their prefix code to a vector of structs 
 **********************************************************************/
void encodingHuffman(BTree *tree, string code, vector<HuffmanData> &data)
{
   
   if (tree->getRightChild() == NULL && tree->getLeftChild() == NULL)
   {
      // load table with letter and its corresponding prefix code
      HuffmanData temp;
      temp.prefixCode = code;
      temp.letter = tree->getLetter();
      data.push_back(temp);
   }
      
   else
   {
      encodingHuffman(tree->getRightChild(), code + "0", data);
      encodingHuffman(tree->getLeftChild(), code + "1", data);
   }
}


