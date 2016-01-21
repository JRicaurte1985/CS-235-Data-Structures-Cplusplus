/***********************************************************************
* Program:
*    Assignment 17 Heap Sort  
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary: 
*    Loads numbers from a file into a vector of ints. Calls heapSort to sort
*    vector. Displays the numbers in sorted order.    
************************************************************************/
#include <fstream>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

void heapify(vector<int> &aHeap, int r, int n);
void percolateDown(vector<int> &aHeap, int r, int n);
void heapSort(vector<int> &aHeap);

/**********************************************************************
 * main description - Loads numbers from a file to a vector of ints.
 * calls heapSort to sort vector. Displays the numbers in sorted order
 ***********************************************************************/
int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      cerr << "Usage: " << argv[0] << "FILE NAME\n";
      return 1;
   }
   else
   {      
      ifstream fin(argv[1]);
      if (fin.fail())
      {
         cout << "\nFile not found\n";
         return 1;
      }
      
      vector<int> heap;
      int num;
 
      heap.push_back(-1); //fill index 0 with garbage
      
      // load vector with numbers from file
      while (fin >> num)
         heap.push_back(num);
      
      //sort vector. See comment blocks to learn how helper functions work
      heapSort(heap);

      // display sorted vector
      for (int i = 1; i < heap.size(); i++)
         cout << heap[i] << " ";
      
      cout << endl;
      fin.close();
   }
   return 0;
}

/**********************************************************************
 * percolate Down -
 * inputs: int r: position of last non-leaf node.
 *         int n: number of elements in binary tree
 *         vector<int> &aHeap: the binary tree to be heapified
 *
 * Performs a cascading routine on subtree starting at index r. A
 * Percolate down will compare r with the largest of its children and
 * swap the values if the child is greater. It will then continue on that
 * same subtree path and compare values until a leaf is reached.
 ***********************************************************************/
void percolateDown (vector<int> &aHeap, int r, int n)
 {
    int c = r * 2; // subscript of left child.

    /*since c gets doubled at the end of the while loop to move down
      subtrees, stop while loop when c exceeds the vector size*/
    while (c < n)
    {
    // check 1 or 2 children, compares children, c assigned to greatest child
       if (c < n - 1 && (aHeap[c] < aHeap[c+1]))
          c++;
    //if largest child greater than root: swap, move down subtree. Else break
       if (aHeap[r] < aHeap[c])
       {
          swap(aHeap[r], aHeap[c]);
          r = c;
          c = 2 * c;
       }
       else
          break;
    }
 }

/**********************************************************************
 * heapify - same inputs as percolateDown.
 *
 * This function iterates the percolateDown function from r until the node
 * at index 1.
 ***********************************************************************/
void heapify (vector<int> &aHeap, int r, int n)
{
   while (r != 0) // index 1 is the last time you percolateDown
   {
      percolateDown(aHeap, r, n);
      r--;
   }
}

/**********************************************************************
 * heap sort 
 * inputs: vector<int> &aHeap  - this is the heap to be sorted.
 *
 * aHeap starts as a binary tree (implemented with a vector). It is then
 * heapified. Then, you start with the "first" (index 1, not 0) element and
 * swap it with the last element. percolateDown the heap starting at index 1
 * to i. Repeat this process, comparing the "first" with the element previous
 * to the last, until you have swapped all elements.
 ***********************************************************************/
void heapSort(vector<int> &aHeap)
{
   int n = aHeap.size(); 
   int r = n / 2; // last non-leaf node
   int i = n - 1; // last element in tree.
   
   heapify(aHeap, r, n);
   
   while (i > 1)
   {
      swap(aHeap[1], aHeap[i]);
      percolateDown(aHeap, 1, i);
      i--;
   }
}
      
