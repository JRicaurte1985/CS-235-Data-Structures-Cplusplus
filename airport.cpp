/***********************************************************************
* Program:
*    Assignment 04, Airport Simulation 
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary:
* Creates an Airport object, which contains two airplane queues and
* several variables containing operations data. Airport object runs through a
* simulation of operations within user* inputted time frame and conditions.

*
* Note that this object was not ideally made using strict OOP principles.
* All variables were made public as to not bloat the code and make it
* overly verbose (setters calling getters, etc). Seeing that this is a hw
* assignment and not real-world code, and that even our Random class took
* this liberty, I did the same.
************************************************************************/

#include <math.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
using namespace std;


class Random
{
   public:
      Random();

      /* --- Get next Poisson random --- */
      int poissonRandom(double expected);

};


Random::Random()
{
   // srand((int)time(NULL));   // variable seed for real simulation
   srand(2500);                 // fixed seed for debug and grading
}

int Random::poissonRandom(double expected)
{
   int n=0;
   double limit;
   double x;
  
   limit = exp(-expected);
   x = rand() / ((double)RAND_MAX + 1);
   while (x > limit)
   {
      n++;
      x *= rand() / ((double)RAND_MAX + 1);
   }
   return n;
}


/**********************************************************************
 Queue Class Header
*********************************************************************/
template <class T>
class Queue
{
   private:
      int front;                  // --- index of front of queue
      int back;                   // --- index of back of queue
      int maxSize;                // --- max storage capacity of array
      int numItems;               // --- number of items currently in queue
      T *queueItems;            // --- array containing queue items
  
   public:
      Queue(int size = 5);           // --- constructor
      Queue(const Queue &aQueue); //  copy constructor
      ~Queue(void);               // --- destructor
      int getItems()const   {return numItems;}
      int getMax() const   {return maxSize;}
      void insert(T const &item);      // --- insert item into back of queue
      T remove(void);           // --- remove item from front of queue
      int empty(void);            // --- returns 1 if queue is empty, 0 otherwise
      int full(void) const;             // --- returns 1 if queue is full, 0 otherwise
      Queue& operator = (const Queue &rtSide); // overloaded assignment operator
};




/**********************************************************************
 * default constructor
 **********************************************************************/
template <class T>
Queue<T>::Queue(int size)    
{
   maxSize = size > 0 ? size : 100;    // if s  is negative, set queue size to 100
   numItems = 0;
   back = front = maxSize - 1;
   queueItems = new T[maxSize];
}

/**********************************************************************
 * destructor
 **********************************************************************/
template <class T>
Queue<T>::~Queue(void)
{
   delete [] queueItems;
}

/***********************************************************************
 * Queue Copy Constructor
 ***********************************************************************/
template <class T>
Queue<T>::Queue(const Queue &aQueue)
{
   maxSize = aQueue.maxSize;
   numItems = aQueue.numItems;
   front = aQueue.front;
   back = aQueue.back;
   queueItems = new T[maxSize];
   for (int i = 0; i < maxSize; i++)
   {
      queueItems[i] = aQueue.queueItems[i];
   }
}

/***********************************************************************
 * Overloaded assignment operator.
 ***********************************************************************/
template <class T>
Queue<T>& Queue<T>::operator = (const Queue<T> &rtSide)
{
   if (this != &rtSide)
   {
   
      if( maxSize != rtSide.maxSize)
      {
         delete [] queueItems;
         queueItems = new T[rtSide.maxSize];
      }
   
      for (int i = 0; i < rtSide.maxSize; i++)
      {
         queueItems[i] = rtSide.queueItems[i];
      }
      maxSize = rtSide.maxSize;   //max size of queue
      numItems = rtSide.numItems; //number of items in queue
      back = rtSide.back;
      front = rtSide.front;
   }
   return *this;
}


/**********************************************************************
 * returns true if queue is empty
 **********************************************************************/
template <class T>
int Queue<T>::empty(void)
{
   return (numItems == 0);
}

/**********************************************************************
 * returns true if queue is full
 **********************************************************************/
template <class T>
int Queue<T>::full(void) const
{
   return (numItems == maxSize);
}

/**********************************************************************
 * inserts item into back of queue, then increments number of items
 * in queue
 **********************************************************************/
template <class T>
void Queue<T>::insert(T const &item)
{
   // --- check for overflow
   if (full())
   {
      cout << "Queue overflow" << endl;
      exit(1);
   }
   queueItems[back] = item;
   back = (back + 1) % maxSize;
   numItems++;
}

/**********************************************************************
 * removes item from front of queue, then decrements number of items
 * in queue
 **********************************************************************/
template <class T>
T Queue<T>::remove(void)
{
   T temp;
   
   if (empty())
   {
      cout << "queue underflow" << endl;
      exit(1);
   }
   temp = queueItems[front];
   front = (front + 1) % maxSize;
   numItems--;
   return (temp);
   
}

/**********************************************************************
 * Airplane Class header - Airplane made up of 2 string member variables
 * make and model
 ***********************************************************************/
class Airplane
{
   public:
      Airplane();
      Airplane(string theMake, string theModel);
      void setMake(string theMake)   {make = theMake;}
      void setModel(string theModel)   {model = theModel;}
      string getMake() const   {return make;}
      string getModel() const   {return model;}

   private:
      string make;
      string model;
};

/**********************************************************************
 * Airplane default constructor
 ***********************************************************************/
Airplane::Airplane()
{
   make = "Boeing";
   model = "747";
}

/**********************************************************************
 * Airplane secondary constructor
 ***********************************************************************/
Airplane::Airplane(string theMake, string theModel)
      :make(theMake), model(theModel)
{/*body intentionall empty*/}



/**********************************************************************
 * Airport Class header -
 * Main component are the 2 Airplane queues.
 * Also consists of various member variables used to calculate operations.
 * Variables were made public as to not bloat the this assignment. If made
 * private I would have to write getters and setters for every single
 * variable. While doable, it would make the code extremely long and
 * verbose. I took the liberty this time to make them public.
 ***********************************************************************/
class Airport
{
  public:
     Airport();
     int runwayIdleTime;
     int planesProcessed;
     int planesLanded;
     int planesTakenOff;
     int rdyLand;
     int rdyTakeOff;
     int planesRefused;
     float percentIdle;
     int sumLandWaitTime;
     int sumTakeOffWaitTime;
     float avgWaitLand;
     float avgWaitTakeOff;
     void displayOperations();
     Queue<Airplane> landing;
     Queue<Airplane> takeOff;
  
  private:
    
};

/**********************************************************************
 * Airport Constructor - variables zeroed out 
 ***********************************************************************/
Airport::Airport()
{
   runwayIdleTime = 0;
   planesProcessed = 0;
   planesLanded = 0;
   planesTakenOff = 0;
   rdyLand = 0;
   rdyTakeOff = 0;
   planesRefused = 0;
   percentIdle = 0;
   sumLandWaitTime = 0;
   sumTakeOffWaitTime = 0;
   avgWaitLand = 0;
   avgWaitTakeOff = 0;

}

/**********************************************************************
 * displayOperations - displays the necessary variables to conform to
 * assignment 4 requirements.
 ***********************************************************************/
void Airport::displayOperations()
{
   cout << "Total number of planes processed: " << planesProcessed << endl;
   cout << "Number of planes landed: " << planesLanded << endl;
   cout << "Number of planes taken off: " << planesTakenOff << endl;
   cout << "Number left ready to land: " << rdyLand << endl;
   cout << "Number left ready to take off: " << rdyTakeOff << endl;
   cout << "Number of planes refused use: " << planesRefused << endl;
   cout << "Percentage of time runway idle: " << setprecision(2)
        << showpoint << fixed << percentIdle << "%" << endl;
   cout << "Average wait time to land: " << avgWaitLand << endl;
   cout << "Average wait time to take off: " << avgWaitTakeOff
        << noshowpoint << endl;
}

/**********************************************************************
 * main description
 * Creates an Airport object. Prompts user for length of simulation and
 * arrivals/takeoffs per time unit. Uses a "random" number to cycle through
 * the time units and simulate airports landing and taking off. Results
 * are then displayed. 
 ***********************************************************************/
int main()
{
   int simLength;
   float arrivalPerTime;
   float takeOffPerTime;
   Random RandomGenerator;
   int random1;
   int random2;
   Airport laGuardia;


   //User prompts with validation
   cout << "Units of time the simulation will run: ";
   cin >> simLength;

   while (cin.fail())
   {
      cin.clear();
      cin.ignore(80,'\n');
      cout << "Invalid Input. Re Enter: ";
      cin >> simLength;
   }

   cout << "Expected number of arrivals per time unit: ";
   cin >> arrivalPerTime;

   while (cin.fail() || arrivalPerTime > 1)
   {
      cin.clear();
      cin.ignore(80,'\n');
      cout << "Invalid Input. Value must be between 0 and 1. Re Enter: ";
      cin >> arrivalPerTime;
   }
   
      
   cout << "Expected number of take offs per time unit: ";
   cin >> takeOffPerTime;

   while (cin.fail() || 1 - arrivalPerTime < takeOffPerTime)
   {
      cin.clear();
      cin.ignore(80,'\n');
      cout << "Invalid Input. Value must complement previous value. "
           <<"Re Enter: ";
      cin >> takeOffPerTime;
   }


   // Airport Operations
   for (int i = 0; i < simLength; i++)
   {
      random1 = RandomGenerator.poissonRandom(arrivalPerTime);
      for (int j = 0; j < random1; j++)
      {
         Airplane *plane = new Airplane;
         if (laGuardia.landing.full())
         {
            laGuardia.planesRefused++;
            laGuardia.planesProcessed++;
         }
         else
         {
            laGuardia.landing.insert(*plane);
            laGuardia.planesProcessed++;
         }
        
         delete plane;
      }
      
      random2 = RandomGenerator.poissonRandom(takeOffPerTime);
      for (int k = 0; k < random2; k++)
      {    
         Airplane *plane2 = new Airplane;
         if (laGuardia.takeOff.full())
         {
            laGuardia.planesRefused++;
            laGuardia.planesProcessed++;
         }
         else
         {
            laGuardia.takeOff.insert(*plane2);
            laGuardia.planesProcessed++;
         }
         delete plane2;
      }

      if (!laGuardia.landing.empty())
      {
         laGuardia.landing.remove();
         laGuardia.planesLanded++;
       
         if (!laGuardia.landing.empty())
            laGuardia.sumLandWaitTime += laGuardia.landing.getItems();
         if (!laGuardia.takeOff.empty())
            laGuardia.sumTakeOffWaitTime += laGuardia.takeOff.getItems();
             
      }
      else if (!laGuardia.takeOff.empty())
      {
         laGuardia.takeOff.remove();
         laGuardia.planesTakenOff++;

         if (!laGuardia.takeOff.empty())
            laGuardia.sumTakeOffWaitTime += laGuardia.takeOff.getItems();
      }
      else
         laGuardia.runwayIdleTime++;
   }

   //calculations
   laGuardia.rdyLand = laGuardia.landing.getItems();
   laGuardia.rdyTakeOff = laGuardia.takeOff.getItems();
   
   
   laGuardia.avgWaitLand = (float)(laGuardia.sumLandWaitTime -
   laGuardia.rdyLand)  / (float)laGuardia.planesLanded;
   
   laGuardia.avgWaitTakeOff = (float)(laGuardia.sumTakeOffWaitTime -
   laGuardia.rdyTakeOff) / (float)laGuardia.planesTakenOff;
   
   laGuardia.percentIdle = (float)laGuardia.runwayIdleTime / (float)simLength
   * 100;
   
   cout << endl;
   
   //display
   laGuardia.displayOperations();
   
   return 0;
}

