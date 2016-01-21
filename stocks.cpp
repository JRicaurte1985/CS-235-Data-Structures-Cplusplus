/***********************************************************************
* Program:
*    Assignment 05 Stocks Program  
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary: This program will simulate the buying and selling of Stock. A
* default STL deque is used to store Stock Objects. Program opens and reads
* a transaction file and begins to fill/empty the deque with Stock objects
* based on the commands/info in the file. When finished, displays the total
* transaction history, total profit, and the unsold shares (if any).   
************************************************************************/
#include <cmath>
#include <cstdlib>
#include <deque>
#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
using namespace std;

/**********************************************************************
 * Stock Class - holds share quantity, share price bought at, day bought
 ***********************************************************************/
class Stock
{
public:
   Stock();
   Stock(int aShare, float aPrice, int aDay);
   const int getShares()   {return shares;}
   const float getPrice()   {return price;}
   const int getDay()   {return day;}
   void setShares(int aShare)   {shares = aShare;}
   void setPrice(float aPrice)   {price = aPrice;}
   void setDay(int aDay)   {day = aDay;}
   
private:
   int shares;
   float price;
   int day;
};


/**********************************************************************
 * Default Constructor
 ***********************************************************************/
Stock::Stock()
      : shares(0), price(0), day(0)
{/*Body intentionally empty*/}

/**********************************************************************
 * Secondary Constructor
 ***********************************************************************/
Stock::Stock(int aShare, float aPrice, int aDay)
      : shares(aShare), price(aPrice), day(aDay) 
{/*Body intentionally empty*/}


/**********************************************************************
 * main description
 *
 * Takes command line arguments: first is a.out and second is a file name.
 * Will open a transaction file and read in and perform the actions. Single
 * Stock object is made when BUY is chosen and filled with the values from
 * the file and pushed onto the back of the deque. When SELL is the action,
 * will sell from the front (oldest purchase). When file is finished, displays
 * the BUY/SELL history and shows profits and unsold shares left.
 * 
 ***********************************************************************/
int main(int argc, char *argv[])
{
   if (argc != 2)
   {
      cerr << "Usage: " << argv[0] << " FILE NAME\n";
      return 1;
   }
   
   else
   {
      ifstream inFile;
      inFile.open (argv[1]);
      if (inFile.fail())
      {
         cout << "\nFile not found\n";
         return 1;
      }
      
      string action;
      int numShares;
      float stockPrice;
      int day = 0; // day is not fully implemented in assignment. Can be
      float originalTotal = 0;
      float saleTotal = 0;
      float netProfit = 0;
      float sumProfit = 0;
      float finalProfit = 0;
      int totalShares = 0;
      int tempShares = 0;
      
      deque<Stock> myStock;
      Stock dailyStock;

      while (inFile >> action)
      {
         if (action == "BUY")
         {
            inFile >> numShares;
            inFile >> stockPrice;
            day++;
           
            cout << "Bought " << numShares << " shares at $" << fixed
                 << setprecision(2) << stockPrice << endl;
            
            dailyStock.setPrice(stockPrice);
            dailyStock.setShares(numShares);
            dailyStock.setDay(day);
            myStock.push_back(dailyStock);

         }
         
         else // sell
         {
            inFile >> numShares;
            inFile >> stockPrice;
            day++; // assuming you can only do one action(buy/sell) per day.
            // numShares used for output, use tempShares for calculations.   
            tempShares = numShares; 
            sumProfit = 0;
            /*cascade the sale along deque if shares sold greater than
              total shares in Stock object.*/ 
            while (myStock[0].getShares() - tempShares < 0)
            { 
               saleTotal = myStock[0].getShares() * stockPrice;
               originalTotal = myStock[0].getShares() * myStock[0].getPrice();
               totalShares += myStock[0].getShares();
               netProfit = saleTotal - originalTotal;
               sumProfit += netProfit;
               tempShares -= myStock[0].getShares();
               myStock.pop_front();
               //check to see if any more objects left in deque
               if (myStock.size() == 0)
               {
                  cout << "Tried to sell more shares than available."
                       << "\nExiting Program.";
                  exit(1);
               }
            }
           
            myStock[0].setShares(myStock[0].getShares() - tempShares);
            originalTotal = tempShares * myStock[0].getPrice();
            saleTotal = tempShares * stockPrice;
            netProfit = saleTotal - originalTotal;
            sumProfit += netProfit;
            finalProfit += sumProfit;
            //pop Stock object if all shares of object have just been sold
            if (myStock[0].getShares() == 0)
               myStock.pop_front();
            
            cout << "Sold " << numShares << " shares at $" << fixed
                 << setprecision(2) << stockPrice << " for a profit of $";
               
            if (sumProfit < 0)
            {
               cout << "(" << fixed << setprecision(2) << abs(sumProfit)
                    << ")" << endl;
            }
            else
               cout << fixed << setprecision(2) << sumProfit << endl;
         }
      }

      cout << "\nTotal Profit: $" << fixed << setprecision(2) << finalProfit
           << "\n\n";
      cout << "Unsold Shares" << endl;
      
      if (!myStock.empty())
      {
         for (int i = 0; i < myStock.size(); i++)
         {
            cout << "   " << myStock[i].getShares() << " shares bought for $"
                 << myStock[i].getPrice() << endl;
         }
      }
      
      inFile.close();
      return 0;
   }
}
