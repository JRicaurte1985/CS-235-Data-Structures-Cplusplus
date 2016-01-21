/***********************************************************************
* Program:
*    Assignment 18 MergeSort  
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary: 
* Natural Mergesort implemented with the STL list. We read numbers from a
* file, store them in a list. We call mergesort on the list. Display the
* sorted list
************************************************************************/

#include <iostream>
#include <list>
#include <fstream>
using namespace std;

void mergeSort(list<int> &f);
int merge(list<int> &f, list<int> &f1, list<int> &f2);
void split(list<int> &f, list<int> &f1, list<int> &f2);

/**********************************************************************
 * main description - Reads in from a file a list of numbers. Store the 
 * numbers in an STL list. Call mergeSort on list. Display list.
 ***********************************************************************/
int main(int argc, char* argv[])
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
 
      list<int>numbers;
      int temp;

      while (fin >> temp)
         numbers.push_front(temp);
      
      mergeSort(numbers);

      for (list<int>::iterator it = numbers.begin(); it != numbers.end(); it++)
      cout << *it << " ";

      cout << endl;
      fin.close();
   }
   return 0;
}

/**********************************************************************
 * split - taken from the textbook pseudoCode. See Nyhoff pg 768.
 * 
 ***********************************************************************/
void split(list<int> &f, list<int> &f1, list<int> &f2)
{ 
   f1.clear();
   f2.clear();
   list<int>::iterator prev = f.begin();
   list<int>::iterator current = f.begin();

   while (current != f.end())
   {  
      //start new sublist in f1, continue adding until currrent < prev or @end
      do 
      {
         prev = current;
         f1.push_back(*current);
         current++;   
      } while (current != f.end() && *current >= *prev);
         
      if (current == f.end())
         break;
      //start new sublist in f2, continue adding until current < prev or @ end
      do
      {
         prev = current;
         f2.push_back(*current);
         current++;
      }  while (current != f.end() && *current >= *prev);
   }
}

/**********************************************************************
 * merge - taken straight from the pseudocode in the book. See Nyhoff
 * pg 768 and read comments in code
 ***********************************************************************/
int merge(list<int> &f, list<int> &f1, list<int> &f2)
{  
   int numSubFiles = 0;
   f.clear();
   list<int>::iterator c1 = f1.begin(); //c stands for current, p is previous  
   list<int>::iterator c2 = f2.begin();
   list<int>::iterator p1 = c1;
   list<int>::iterator p2 = c2;
   
   //Main while loop. Break when end of f1 or f2
   while (c1 != f1.end() && c2 != f2.end())
   {
      p1 = c1;
      p2 = c2;
      //break at end of subfile, when next smaller than prev or at an end()  
      while (c1 != f1.end() && c2 != f2.end() && *c1 >= *p1 && *c2 >= *p2)
      {      
         if (*c1 < *c2)
         {
            f.push_back(*c1);
            p1 = c1;
            c1++;
         }
         else
         {
            f.push_back(*c2);
            p2 = c2;
            c2++;
         }
      }
      numSubFiles++;
     
      //end of subfile in f1. add rest of f2 subfile to f
      while (c2 != f2.end() && *c2 >= *p2)
      {
         p2 = c2;
         f.push_back(*c2);
         c2++;
      }
      // end of subfile in f2. add rest of f1 subfile to f
      while (c1 != f1.end() && *c1 >= *p1)
      {
         p1 = c1;
         f.push_back(*c1);
         c1++;
      }
   } // end of main while loop

   //copy any remianing subfiles. increment numSubFiles when needed
   while (c1 != f1.end())
   {
      if (*c1 < *p1)
         numSubFiles++;
      
      f.push_back(*c1);
      p1 = c1;
      c1++;
   }
   
   while (c2 != f2.end())
   {
      if (*c2 < *p2)
         numSubFiles++;
      
      f.push_back(*c2);
      p2 = c2;
      c2++;
   }
   
   return numSubFiles;
}

/**********************************************************************
 * mergeSort - call split and merge until subfiles = 1. If subfiles = 1
 * that means the list is sorted.
 ***********************************************************************/
void mergeSort(list<int> &f)
{
   if (f.size() <= 1)
      return;
   
   list<int> f1;
   list <int> f2;
   int subfiles = 5;
   
   while (subfiles > 1)
   {
      split(f, f1, f2);
      subfiles = merge(f, f1, f2);
      cerr << "Subfiles: "<< subfiles  << endl;
   }
}


