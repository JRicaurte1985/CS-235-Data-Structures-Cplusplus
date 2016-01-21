/***********************************************************************
* Program:
*    Assignment 11  
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary: 
*    Reads words from a file, passes them through a hasing function, and
*    creates a hash table. The collision-resolution method used is chaining.
*    Displays the contents of the table.
************************************************************************/

#include <iostream>
#include <list>
#include <fstream>
#include <iomanip>
using namespace std;

int hash (string aWord); // hash function
void display (list<string> aHashTable[], const int size); // display hash table

/**********************************************************************
 * main description - reads words from a file. Passes the words through
 * a hash function and inserts to hash table. Displays table
 ***********************************************************************/
int main()
{
   const int MAX = 67;
   list<string> hashTable[MAX];
   ifstream fin;
   string word;
   
   //open file. Test to see if opened.
   fin.open ("/home/cs235/assign11/assign11.in");
   if (fin.fail())
   {
      cout << "\nFile not found\n";
      return 1;
   }
   //read words from file, pass each through hash function, insert to hash table
   while (fin >> word)
      hashTable[hash(word)].push_back(word);
   
   // display table contents
   display(hashTable, MAX);
   
   fin.close();
   return 0;
}

/**********************************************************************
 * hash - takes a string (aWord) and returns an int (hashIndex).
 *
 * Takes the sum of the ascii values of each char in the string and
 * mods it by 67. Assign that value to hashIndex and return hashIndex.
 ***********************************************************************/
int hash (string aWord)
{
   int hashIndex;
   int sumAscii = 0;
   
   for (int i = 0; i < aWord.length(); i++)
      sumAscii += aWord.c_str()[i];
   
   hashIndex = sumAscii % 67;
   return hashIndex;   
}

/**********************************************************************
 * display - inputs: array of string lists(aHashTable), size of array(size).
 * Displays the contents of the hashTable. If empty, displays "(empty)"
 ***********************************************************************/
void display (list<string> aHashTable[], int size)
{
   int count = 0;
   
   for (int i = 0; i < size; i++)
   {
      cout << "table[" << i <<"]";
      if (i < 10)
         cout << " ";
      cout << "-> "; 
         
      if (aHashTable[i].empty())
         cout << "(empty)";
      else
      {
         count = 0;
         for (list<string>::iterator it = aHashTable[i].begin();
              it != aHashTable[i].end(); ++it)
         {
            if (count > 0)
               cout << ", ";
            cout << *it;
            count++;    
         }
      }     
      cout << endl;
   }
}
