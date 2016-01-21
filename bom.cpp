/***********************************************************************
* Program:
*    Assignment 16 
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary: This program reads in the text of the Book of Mormon
* from a file. It stores the words in a map with the key being the
* word and the value being the number of times it occurs. Then the
* values are copied into an array of structs (int and str again) and
* the array is sorted by value. The top 100 words are then displayed.
************************************************************************/
#include <map>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <algorithm>
using namespace std;

struct combo
{
   string mWord;
   int mCount;
};

bool sortByCount(const combo& lhs, const combo& rhs)
{
   return lhs.mCount > rhs.mCount;
}

/**********************************************************************
 * main description -
 * reads in the text of the Book of Mormon from a file. It stores the words
 * in a map with the key being the word and the value being the number of
 * times it occurs. Then the map elements are copied into an array of
 * corresponding structs and the array is sorted by word count. The top 100
 * words are then displayed.
 ***********************************************************************/
int main()
{
   ifstream fin("/home/cs235/assign16/assign16.in");
   if (fin.fail())
   {
      cout << "File not found!\n";
      return 1;
   }
   else
   {
      int count = 0;
      string word;
      map<string, int> bomWords;
      // while loop takes care of inserting properly formatted words into map
      while (fin >> word)
      {   //In for loop, go through each char of the word
         for (int i = 0; i < word.length(); i++)
         {
            // get rid of punctuation but keep hyphen
            if (!isalpha(word[i]) && word[i] != '-')
            {
               word.erase(i,1);
               i--;
            }
            else
               word[i] = tolower(word[i]); // make letter lowercase
         }
         
         bomWords[word]++; // insert word to map and increment word count
         count++; // count to display number of words processed
      }
      // make array to transfer data from map to array 
      combo* data = new combo[bomWords.size()];
      int index = 0;
      map<string, int>::iterator it;
      // copy items from map to array
      for (it = bomWords.begin(); it != bomWords.end(); it++)
      {
         data[index].mWord = it->first;
         data[index].mCount = it->second;
         index++;
      }
      // sort by word count in descending order
      sort(data, data + bomWords.size(), sortByCount);
    
      cout << "\nNumber of words processed: " << count << endl;
      cout << "100 most common words found and their frequencies:\n";
      // display top 100 words and their counts
      for (int i = 0; i < 100; i++)
         cout << setw(23) << data[i].mWord << " - " << data[i].mCount << endl;

      delete [] data; // free memory
   }
   return 0;
}
