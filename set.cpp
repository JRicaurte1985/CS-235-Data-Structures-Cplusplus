/***********************************************************************
* Program: Set Class
*    Assignment 01  
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary: 
*   Implements a Set Class to read in values from a file and create 2 sets. Set
*   class functions are invoked to compute and display both sets, the union,
*   intersection, and differences. 
************************************************************************/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>

using namespace std;

/*****************************************************************************
 * Class Name: Set
 *
 * Summary: As in mathematics, this class is designed to store a set of numbers.
 * Order does not matter. When displayed, the set will be sorted. The Set object
 * can add elements without worrying about exceeding array bounds, a feature
 * built in to the addElement function. Can also expand array bounds using the
 * setCapacity function.
 * Operators have been overloaded to perform intersection, union, difference, as
 * well as the assignment operator to allow assignments between Set objects.
 * A quick sort function is built in for sorting.
 *****************************************************************************/
class Set
{
public:
   Set();
   Set(int aCapacity);
   Set(const Set &obj); 
   ~Set(); 
   int getSize() const   {return mSize;}
   int getCapacity() const   {return mCapacity;}
   void setCapacity(int aCapacity);
   void addElement(int aElement);
   bool findElement(int aElement) const;
   void display(); // sorts the set before displaying
   Set & operator = (const Set &rhs);
   Set operator - (const Set &rhs);
   Set operator && (const Set &rhs);
   Set operator || (const Set &rhs);
   void qSort(int array[], int left, int right); // used before display()
   
   

private:
   int mCapacity;
   int mSize;
   int *mIntArray;
   int partition (int array[], int left, int right); // needed for quicksort
};



/*****************************************************************************
 * Summary: Default constructor. Used for empty set.
 *****************************************************************************/
Set::Set()
      :mCapacity(0), mSize(0), mIntArray(NULL)
{/*Body intentionally empty*/}

/*****************************************************************************
 * Summary: Secondary constructor. Allows you to set capacity as argument
 *****************************************************************************/
Set::Set(int aCapacity)
      :mCapacity(aCapacity), mSize(0)
{
   mIntArray = new int[mCapacity];
}

/*****************************************************************************
 * Summary: Copy constructor
 *****************************************************************************/
Set::Set(const Set &obj)
{
   mIntArray = new int[obj.mCapacity];
   mCapacity = obj.mCapacity;
 
   for (int i = 0; i < obj.mSize; i++)
   {
      mIntArray[i] = obj.mIntArray[i];
   }
   mSize = obj.mSize;
}

/*****************************************************************************
 * Summary: Destructor
 *****************************************************************************/
Set::~Set()
{
   delete [] mIntArray;
}

/*****************************************************************************
 * Summary: sets the object's capacity to argument value. Expands array bounds
 * by creating  a temp array with the new capacity and copies values of calling
 * object's array into it. Old array is deleted.
 *****************************************************************************/
void Set::setCapacity(int aCapacity)
{
    mCapacity = aCapacity;
    
    if (mIntArray == NULL)   // if array is empty, can easily set new capacity
   {
      mIntArray = new int[mCapacity];
   }
   else
   {
      int *tempArray = new int[mCapacity]; // make temp array with new capacity
      for (int i = 0; i < mSize; i++)
      {
         tempArray[i] = mIntArray[i]; // copy values from old array to temp
      }
      
      delete [] mIntArray;
      mIntArray = tempArray;
   }
}
/*****************************************************************************
 * Summary: Add element to a Set object.
 * First checks if Set's array bounds are sufficient to add an element. Array
 * bounds expanded if array is full or pointer is NULL. Once bounds have been
 * accomodated, we check to see if the element to be added is a duplicate in the
 * Set. If no duplicate is found, the element is added to the set and size
 * increased by 1
 *****************************************************************************/
void Set::addElement(int aElement)
{
   if (mSize == mCapacity) // if set is full (or empty),  need to expand array
   {
      if (mIntArray == NULL) // expand a null array(empty set), default size 1
         setCapacity(1);     
      else
         setCapacity(mCapacity * 2); // double capacity of array
   }
   
   if (!findElement(aElement)) // if no duplicate, element is added
   {
      mIntArray[mSize] = aElement; 
      mSize++;
   } 
}

/*****************************************************************************
 * Summary: Loops through calling object's arrray values and compares to int
 * argument. If equal, will return true. If set is empty or a match is not
 * found, returns false.
 *****************************************************************************/
bool Set::findElement(int aElement) const
{
    for (int i = 0; i < mSize; i++) 
    {
       if (mIntArray[i] == aElement)
          return true;
    }
    return false;  
}

/*****************************************************************************
 * Summary: Displays the set, sorted. If set is empty, the function exits.
 *****************************************************************************/
void Set::display()
{
   if (mSize == 0) // cannot display empty Set (pointer to array is null)
   {
      cout << endl << endl;
      return;
   }
   
   qSort(mIntArray, 0, mSize - 1);
   
   for (int i = 0; i < mSize; i++)
   {
      if (i % 10 == 0) // new line every 10 elements
         cout << "\n";
      cout << setw(4) << mIntArray[i];
   }
   cout << endl;
}
  
/*****************************************************************************
 * Summary: Overloaded assignment operator
 * Allows the assignment of Set Objects to Set Objects. Checks first for self-
 * assignment. If rhs's array size it larger than calling object's array
 * capacity, will create new array with the capacity equal to rhs's size. Copies
 * rhs's array values into the calling object's array. Assigns rhs's size to
 * calling object's size. Returns calling object by reference to allow cascading
 *****************************************************************************/
Set& Set::operator = (const Set &rhs)
{
   if (this == &rhs)
      return *this;
   else
   {
      if (rhs.mSize > mCapacity)
      {
         delete [] mIntArray;
         mIntArray = new int[rhs.mSize];
         mCapacity = rhs.mSize;
      }
      for (int i = 0; i < rhs.mSize; i++)
      {
         mIntArray[i] = rhs.mIntArray[i];
      }
      mSize = rhs.mSize;
      return *this;
   }  
}

/*****************************************************************************
 * Summary: Overloaded operator to compute difference of Sets.
 * Runs through every value of calling object's array and uses it as argument of
 * rhs.findElement. If a duplicate value is not found in rhs, that value is
 * added to difference. Returns difference.
 *****************************************************************************/
Set Set::operator - (const Set &rhs)
{
   Set difference;
   
   for (int i = 0; i < mSize; i++)
   {
      /*Check if calling object's array values can be found in rhs's array.
      If not found, add value to intersection*/
      
      if (!rhs.findElement(mIntArray[i])) 
          difference.addElement(mIntArray[i]);
   }
   return difference;            
}
   
/*****************************************************************************
 * Summary: Overloaded operator to compute intersection of Sets.
 * Runs through every value of calling object's array and uses it as argument of
 * rhs.findElement. If a duplicate value is found in rhs, that value is added to
 * intersection. Returns intersection
 *****************************************************************************/
Set Set::operator && (const Set &rhs)
{
   Set intersection;
 
   for (int i = 0; i < mSize; i++)
   {
      /*Check if calling object's array values can be found in rhs's array.
      If found, add value to intersection*/
      
      if (rhs.findElement(mIntArray[i]))
          intersection.addElement(mIntArray[i]);
   }
   return intersection;
}

/*****************************************************************************
 * Summary: Overloaded operator to compute union of Sets
 * Calling object is lhs and argument is rhs. First a new Set Object named uni
 * is created. I can then run through both lhs and rhs and add every element
 * using my addElement function. The addElement function will not add duplicates
 * Thus, uni will consist of all values of both A and B without repeats.
 *****************************************************************************/
Set Set::operator || (const Set &rhs)
{  
   Set uni;
 
   for (int i = 0; i < mSize; i++)
      uni.addElement(mIntArray[i]);
   
   for (int i = 0; i < rhs.mSize; i++)
      uni.addElement(rhs.mIntArray[i]);   
    
   return uni;      
}

/*****************************************************************************
 * partition - this function is part of the quickSort algorithm and is called
 * every time quickSort recursively calls itself. It's purpose in the algorithm
 * is to divide the array into 2 sub-arrays based on a pivot chosen. In this
 * case the pivot is not random. It is set as the midpoint of the array. Once
 * the pivot is chosen, i and j serve as indices for the beginning and end of
 * the array. i and j move along the array and through a series of comparisons
 * and swaps with the pivot and each other, the values less than the pivot
 * stay on the left and the values greater than pivot move to the right. i is
 * returned and used in the quickSort recursion to determine the starting or
 * end position of the new array to be partitioned.
 ****************************************************************************/
int Set::partition (int array[], int left, int right)
{
   int i = left;
   int j = right;
   int temp;
   int pivot = array[(left + right) / 2];

   while (i <= j)
   {
      while (array[i] < pivot)
         i++;
      while (array[j] > pivot)
         j--;
      if (i <= j)
      {
         temp = array[i];
         array[i] = array[j];
         array[j] = temp;
         i++;
         j--;
      }
    
   }
   return i;
}

/****************************************************************************
 * quickSort - This function is the quicksort algorithm modified to take as 
 * an argument a Set object. The comparisons are done on the array in Set.
 * The algorithm basically chooses a pivot, puts the values less
 * than the pivot to the left of it and the values greater than the pivot to
 * the right. This is done through the partition function. Recursion occurs
 * until the the whole 'less-than' sub-array is sorted and then moves on to
 * the 'greater-than' sub-array. Recursion occurs until the greater-than
 * sub-array is sorted, which finally results in the entire array being sorted.
 * Since Set objects have no repeats, it matters not that this is an unstable
 * sort.
 ****************************************************************************/
void Set::qSort(int array[], int left, int right)
{
   int index = partition(array, left, right);
   if (left < index - 1)
      qSort(array, left, index - 1);
   if (index < right)
      qSort(array, index, right);
}

/**********************************************************************
 * main description
 *
 * Creates 2 set objects a and b based on values read in from a file. Then
 * displays both sets, the intersection, union, and difference (a-b and b-a).
 * Program requires the file name as a command line parameter and will display
 * an error message and exit if this condition fails.
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
      ifstream inFile;
      int setSize;
      int element;
      
      inFile.open (argv[1]);
      if (inFile.fail())
      {
         cout << "\nFile not found\n";
         return 1;
      }
   
      inFile >> setSize; 
      Set a(setSize);

      for (int i = 0; i < setSize; i++)
      {
         inFile >> element;
         a.addElement(element);
      }

      inFile >> setSize;
      Set b(setSize);

      for (int i = 0; i < setSize; i++)
      {
         inFile >> element;
         b.addElement(element);
      }

      cout << "Set A:";
      a.display();
   
      cout << "\nSet B:";
      b.display();
   
      Set c = a && b;
      cout <<"\nIntersection of A and B:";
      c.display();
   
      c = a || b;
      cout <<"\nUnion of A and B:";
      c.display();
   
      c = a - b;
      cout <<"\nDifference of A and B:";
      c.display();

      c = b - a;
      cout <<"\nDifference of B and A:";
      c.display();

      cout << endl;

      inFile.close();
   
      return 0;
   }
}

