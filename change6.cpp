/***********************************************************************
* Program:
*    Assignment 08, Polynomials
*    Jose Ricaurte, CS 235
* Author:
*    Modified by Brother Ercanbrack
* Summary: 
*    This program reads two polynomials from a file, displays them,
*    adds them together, evaluates the result for a given value of x and
*    displays the result.
***********************************************************************/
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

/******************************************************************************
*  Author: Brother Cameron, 10/9/2001
*
*  Purpose: Defines classes for a Term and a Polynomial
******************************************************************************/
class Term
{
   private:
      float coeff;
      int expon;
 
   public:
      Term();                  // --- Creates empty Term
      Term(float c, int e);    // --- Creates Term object with coeff. c 
                               //and expon. e
      float getCoeff(void);    // --- returns coeff of term
      int getExpon(void);      // --- returns expon of term
      void setCoeff(float c);  // --- sets term's coeff. to c
      void setExpon(int c);    // --- sets term's expon to c
};

/***********************************************************************
* Class containing an array of Terms and the functions to operate on them
***********************************************************************/
class Poly
{
   private:
      int numTerms;            // number of terms in polynomial
      int maxItems;            // array capacity
      Term *terms;             // dynamically allocated array of terms

   public:
      Poly();                  // creates empty polynomial
      Poly(const Poly &poly);  // copy constructor
      ~Poly();                 // destructor free dynamically allocate ptrs.
      void insertTerm(Term t); // inserts Term t into polynomial
      int getNumTerms(void);   // returns number of terms in array
      Term getTerm(int index); // returns term at index
      int getMaxItems()        {return maxItems;}
      void setMaxItems(int max)   {maxItems = max;}
      Poly& operator = (const Poly& rhs);//overloaded assignment operator
      float operator () (float x);
      friend Poly operator + (Poly& op1, Poly& op2);
      friend ostream& operator << (ostream& outFile, Poly& op1);
      friend istream& operator >> (istream& inFile, Poly& op1);
   void display(){cout << "display " << numTerms << endl;}
         //<< terms[1].getCoeff() << " " << terms[1].getExpon();}
};


/***********************************************************************
* Main reads the file, outputs the polynomials, adds them together and
* displays the results.  Don't modify this function!!!!!
***********************************************************************/
int main(int argc, char* argv[])
{
   ifstream inFile;
   inFile.open(argv[argc - 1]);
   if (inFile.fail())
   {
      cout << "open file error " << argv[argc - 1] << endl;
      exit(1);
   }
   
   Poly f;
   Poly g;
   Poly p;

   int value (0); // value of x for evaluation
    inFile >> f;
    inFile >> g;

   cout << "F(x) =  " << f << endl;
   cout << "G(x) =  " << g << endl;

   // make copies of the polynomials
    Poly temp1(f);
    Poly temp2(g);

   // add polynomials f and g
   p = f + g;
   cout << "\nP(x) = (F + G)(x) = " << p << endl;

   // read in a value for X
   inFile >> value;

   // evaluate the polynomial
   cout << "P(" << value << ") = " << p(value) << endl << endl;

   // swap temp1 and temp2 - shouldn't change f & g
   Poly temp3(temp2);
   temp2 = temp1;
   temp1 = temp3;

   // Insert a new term 8x^6
    f.insertTerm(Term(-8,6));
  
    cout << "temp1(x) is same as 8x^6 + G(x) or " << temp1 << endl;
   cout << "temp2(x) is same as F(x) or " << temp2 << endl;
   cout << "temp3(x) is same as G(x) or " << temp3 << endl << endl;
   
   cout << "Original functions were:" << endl;
   cout << "F(x) =  " << f << endl;
   cout << "G(x) =  " << g << endl;
   // f.display();
   inFile.close();
   return 0;
}

/*****************************************************************************
*
*  Function: Term
*
*  Parameters - none
*  Return Value - none
*
*  Purpose - Constructor function for Term class.  Creates empty Term.
****************************************************************************/
Term::Term(void)
{
   coeff = 0.0;
   expon = -1;  // --- guarantees insert will occur
}

/*****************************************************************************
*
*  Function: Term
*
*  Parameters - a float that is the coefficient and a int that is the expon.
*  Return Value - None
*
*  Purpose: Creates a Term object set to coefficient and expon.
****************************************************************************/
Term::Term(float c, int e)
{
   coeff = c;
   expon = e;
}

/*****************************************************************************
*
*  Function: getCoeff
*
*  Parameters: None
*  Return Value - an integer representing coeff.
*
*  Purpose: Returns the coefficient data member of Term class
****************************************************************************/
float Term::getCoeff(void)
{
   return (coeff);
}

/***************************************************************************
*  Function: getExpon
*  Purpose: Returns the expon data member of Term class
*
*  Parameters - none
*  Return value - integer, representing expon.
***************************************************************************/
int Term::getExpon(void)
{
   return (expon);
}

/***************************************************************************
*  Function: setCoeff
*  Purpose: sets c to data member coeff in Term class
*
*  Parameters - float representing coeff
*  Return value - none
**************************************************************************/
void Term::setCoeff(float c)
{
   coeff = c;
}

/***************************************************************************
*  Function: setExpon
*  Purpose: sets e to data member expon in Term class
*
*  Parameters - int representing expon
*  Return value - none
**************************************************************************/
void Term::setExpon(int e)
{
   expon = e;
}

/***************************************************************************
*
*  Function: Poly
*  Purpose:  Poly class constructor to create an empty Poly object of 50 
*            term.
*
*  Parameters - none
*  Return value - none
**************************************************************************/
Poly::Poly()
{
   numTerms = 0;
   terms = new Term [50];
   maxItems = 50;
}

/********************************************
 * Destructor
 *********************************************/
Poly::~Poly()
{
   delete [] terms;

}

/*******************************************
 * copy constructor
 ********************************************/
Poly::Poly(const Poly &poly)
{
   
   terms = new Term[poly.maxItems];
   maxItems = poly.maxItems;
   numTerms = poly.numTerms;

   for (int i = 0; i < numTerms; i++)
   {
      terms[i] = poly.terms[i];
   }
}
        
/*******************************************
 * overloaded Assignment operator
 ********************************************/
Poly& Poly::operator = (const Poly &rhs)
{
   if (this == &rhs)
      return *this;
   else
   {
      if (rhs.numTerms > numTerms)
      {
         delete [] terms;
         terms = new Term[rhs.maxItems];
      }
      for (int i = 0; i < rhs.numTerms; i++)
      {
         terms[i] = rhs.terms[i];
      }
      
      numTerms = rhs.numTerms;  
   }
   
}

/***********************************************************************
* Inserts a term into a polynomial in the proper location.  If a term
* is inserted with a duplicate exponent, the terms are combined.  If any
* coefficient goes to zero that term is removed from the polynomial.
***********************************************************************/
void Poly::insertTerm(Term t)
{
   if (terms[0].getExpon() == -1) // empty polynomial
   {
      cout << " empty poly" << endl;
      terms[0] = t;
      numTerms++;
   }
   
   else
   {
      int insertionIndex = 0;
      bool combine = false;
      bool eliminate = false;
      bool inserted = false;
      // find where the insertion will be and if combination/elimination occurs
      for (int i = 0; i < numTerms; i++)
      {
          cout << " test" << endl;
         if (terms[i].getExpon() > t.getExpon())
         {
            cout << " insertion++:" << insertionIndex << endl;
            insertionIndex++;
         }
         if (t.getExpon() == terms[i].getExpon())
         {
            combine = true;
            if (t.getCoeff() + terms[i].getCoeff() == 0)
               eliminate = true;
         }
      }
      
      // if new insertion will exceed array bounds, double array size (maxItems)
       if (!combine && numTerms + 1 > maxItems)
         maxItems *= 2;
       Term *temp = new Term[maxItems];
       
      //copy terms elements into temp, inserting new element at insertion
      // accounts for combination and/or elimination of terms
       for (int i = 0; i < numTerms + 1; i++)
        {
          if (i != insertionIndex)
          {
             cout << "\ni != insertionIndex: " << insertionIndex << endl;
            if (i > insertionIndex && eliminate)
            {
               cout << "\nsecond if" << endl;
               temp[i-1] = terms[i];
            }
            else if (inserted)
            {
               cout << "\nthird if" << endl;
               temp[i] = terms[i-1];
            }
            else
            {
               cout << "\nlast else" << endl;
               temp[i] = terms[i];
            }
          }
          else 
          {        
            if (combine)
            {
               temp[i] = t;
               temp[i].setCoeff(terms[i].getCoeff() + t.getCoeff());
            }
            else
            {
               temp[i] = t;
               inserted = true;
               cout << "Inserted!" << endl;
               //numTerms++;
            }
         }
      }

      if (eliminate)
      numTerms--;

      if (inserted)
         numTerms++;
          
       delete [] terms;
        terms = temp;
                          
   }
      
}

/***********************************************************************
* Accessor function that returns the number of Terms in the array
***********************************************************************/
int Poly::getNumTerms()
{
   return (numTerms);
}

/***********************************************************************
* Accessor function that returns the Term at a given index
***********************************************************************/
Term Poly::getTerm(int index)
{
   return (terms[index]);
}

/***********************************************************************
* overloaded () operator that evaluates the polynomial for the value
* within the parentheses
***********************************************************************/
float Poly::operator () (float x)
{

}

/***********************************************************************
* overloaded + operator that combines two polynomials and returns the
* result as a polynomial
***********************************************************************/
Poly operator + (Poly& op1, Poly& op2)
{
   Poly temp;
   //Use insert to insert all terms of op1 and op2. Insert will take care
   // of combining/eliminating terms.

   for (int i = 0; i < op1.getNumTerms(); i++)
      temp.insertTerm(op1.terms[i]);

   for (int i = 0; i < op2.getNumTerms(); i++)
      temp.insertTerm(op2.terms[i]);

   return temp;
}

/***********************************************************************
* overloaded << operator that outputs the polynomial in the proper format
***********************************************************************/
ostream& operator << (ostream& outFile, Poly& op1)
{
   if (op1.numTerms == 0)
      return outFile;
   
   else
   {
      for (int i = 0; i < op1.numTerms; i++)
      {
         if (i == 0)
         {
            if (op1.terms[i].getCoeff() != 1 && op1.terms[i].getCoeff() != -1
                || op1.terms[i].getExpon() == 0)
               outFile << op1.terms[i].getCoeff();
            if (op1.terms[i].getExpon() == 1)
            {
               if (op1.terms[i].getCoeff() == 1)
                  outFile << "x";
               else if (op1.terms[i].getCoeff() == -1)
                  outFile << "-x";
            }
            if (op1.terms[i].getExpon() > 1)
               outFile << "x^" << op1.terms[i].getExpon();
         }
         else
         {
            if (op1.terms[i].getCoeff() < 0)
               outFile << " - ";
            else
               outFile << " + ";
            if (op1.terms[i].getCoeff() != 1 && op1.terms[i].getCoeff() != -1
                || op1.terms[i].getExpon() == 0)
               outFile << abs((int)op1.terms[i].getCoeff());
            
            if (op1.terms[i].getExpon() > 0)
            {
               outFile << "x";
               if (op1.terms[i].getExpon() > 1)
                  outFile << "^" << op1.terms[i].getExpon();
            }
         }
      }
      return outFile;
   }
   
}

/***********************************************************************
* overloaded >> operator that reads an entire polynomial into an array
* of Terms in the proper order.
***********************************************************************/
istream& operator >> (istream& inFile, Poly& op1)
{ 
   float tempCoeff;
   int tempExpon;
   int numPolyTerms;
   Term temp;
   inFile >> numPolyTerms;
   
   
   for (int i = 0; i < numPolyTerms; i++)
   {
       inFile >> tempCoeff >> tempExpon;
       temp.setCoeff(tempCoeff);
       temp.setExpon(tempExpon);
      
       op1.insertTerm(temp);
   }
   return inFile;
}
