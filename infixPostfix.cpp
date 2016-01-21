/***********************************************************************
* Program:
*    Assignment 03  
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary: This program implements our stack from assignment 2. We read infix
* expressions from a file, convert them to postfix, then use that postfix
* expression to display its assembly language equivalent. Note that I
* changed my Stack class to a template class.
************************************************************************/

using namespace std;
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <string>
#include <cctype>
#include <sstream>
#include <fstream>


/************************************************************
* Stack Class - template class for a stack data structure.
* A Stack is an abstract data type that can hold a collection of
* data and operates on the context of first in last out.
************************************************************/
template <class T>
class Stack
{
   private:
     int myTop;                  // index of top of stack
     int maxSize;                // maximum size of stack  
     T *stackItems;            // pointer for dynamic array
   public:
     Stack(int size = 100);      // default constructor (stack size 100)
     Stack(const Stack &aStack); // copy constructor 
     T top()const;              // returns the value of top item in the stack
     void push(T const &item);        // store item on the stack
     void pop();             // remove/delete top item off stack
     bool empty()const;           // is stack empty
     bool full();            // is stack full
     ~Stack();                   // destructor
     Stack& operator = (const Stack &rtSide); // overloaded assignment operator
};


string postfix(string exp);
string intToStr(int number);
void pfToAssembly (string pf);

/************************************************************
* Default Constructor - default size is 100
************************************************************/
template <class T>
Stack<T>::Stack(int size)
      :maxSize(size), myTop(-1)
{
   stackItems = new T[size];
}

/************************************************************
* Copy Constructor
************************************************************/
template <class T>
Stack<T>::Stack(const Stack<T> &aStack)
{
   stackItems = new T[aStack.maxSize];
   myTop = aStack.myTop;

   for (int i = 0; i < aStack.myTop + 1; i++)
   {
      stackItems[i] = aStack.stackItems[i];
   }
   
}


/************************************************************
* Destructor
************************************************************/
template <class T>
Stack<T>::~Stack()
{
   delete [] stackItems;
}

/************************************************************
* Top - If stack is empty, returns error message. Else,
* returns value of the element indexed by myTop.
************************************************************/
template <class T>
T Stack<T>::top() const
{
   if (empty())
   {
      cout <<"ERROR: Stack Empty\n";
      exit(1);
   }
   else
      return stackItems[myTop];
}
/************************************************************
* Push- If stack is full, displays error message and exits the
* program. If not full, adds the argument 'item' to the top of
* the stack and updates myTop.
************************************************************/
template <class T>
void Stack<T>::push(T const &item)
{
   if (!full())
   {
      stackItems[myTop + 1] = item;
      myTop++;
   }
   else
   {
      cout << "ERROR: Stack Overflow\n";
      exit(1);
   }
}


/************************************************************
* Pop - if stack is empty, displays error message and exits
* program. Otherwise, will 'remove' the top item of the stack
* by decreasing the value of myTop by 1
************************************************************/
template <class T>
void Stack<T>::pop()
{
   if (empty())
   {
      cout << "ERROR: Stack Underflow\n";
      exit(1);
   }
   else
      myTop--;
      
}

/************************************************************
* Empty - If stack is empty, returns true. This is done by
* checking the value of myTop. If myTop is less than 0, then
* we know the stack is empty. If not, returns false.
************************************************************/
template <class T>
bool Stack<T>::empty() const
{
   if (myTop < 0)
      return true;
   else
      return false; 
}

/************************************************************
* Full - If stack is full, returns true. This is done by
* checking to see if myTop + 1 equals the maxSize. If so,
* returns true. If not, returns false.
************************************************************/
template <class T>
bool Stack<T>::full()
{
   if (myTop + 1 == maxSize)
      return true;
   else
      return false;
}

/************************************************************
* Overloaded Assignment Operator 
************************************************************/
template <class T>
Stack<T>& Stack<T>::operator = (const Stack<T> &rhs)
{
   if (this == &rhs)
      return *this;
   else
   {
      if ((rhs.myTop + 1) > maxSize)
      {
         delete[] stackItems;
         stackItems = new T[rhs.maxSize];
         maxSize = rhs.maxSize;
      }
      for (int i = 0; i < rhs.myTop + 1; i++)
      {
         stackItems[i] = rhs.stackItems[i];
      }
      myTop = rhs.myTop;
      return *this;
   }
}

/**********************************************************************
 * postfix - converts infix expression to postfix expression. Returns the
 * postfix expression. Copied straight from the textbook with minor stylistic
 * touches.
 ***********************************************************************/
string postfix(string exp)
{
   char token, topToken;
   Stack<char> opStack;
   string postfixExp;

   for (int i = 0; i < exp.length(); i++)
   {
      token = exp[i];
      switch(token)
      {
         case ' ':
            break;
            
         case '(' :
            opStack.push(token);
            break;
         
         case ')' :
            for (;;)
            {
               assert (!opStack.empty());
               topToken = opStack.top();
               opStack.pop();
               
               if (topToken == '(')
                  break;
               
               postfixExp += topToken;
            }
            break;
         
         case '+' : case '-' : case '*' : case '/' : case '%' :
            for (;;)
            {
               if (opStack.empty() || opStack.top() == '(' ||
                   (token == '*' || token == '/' || token == '%') &&
                   (opStack.top() == '+' || opStack.top() == '-'))
               {
                  opStack.push(token);
                  break;
               }
               else
               {
                  topToken = opStack.top();
                  opStack.pop();
                  postfixExp += topToken;
               }
            }
            break;
         
            
         default : //operand
            postfixExp += token;
            for (;;)
            {
               if ( !isalnum(exp[i+1]) )
                  break;
               i++;
               token = exp[i];
               postfixExp += token;
            }
         
      }
      
   }
   
   for (;;)
   {
      if (opStack.empty())
         break;
      
      topToken = opStack.top();
      opStack.pop();
      
      if (topToken != '(')
      {
         postfixExp += topToken;
      }
      else
      {
         cout << " ***Error in infix expression ***\n";
         break;
      }
   }

   return postfixExp;
}

/**********************************************************************
 * intToStr - converts int to string using stringstream.
 * 
 ***********************************************************************/
string intToStr(int number)
{
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

/**********************************************************************
 * pf - converts postfix expression to assembly language processes.
 * Takes a postfix expression as argument (pf stands for postfix).
 * Cycles through the postfix expression one character at a time and
 * stores the operands in a stack. When it comes across an operator, it
 * displays the proper order of assembly actions. When the entire postfix
 * expression is analyzed, function is complete.
 ***********************************************************************/
void pfToAssembly(string pf)
{
   int tempCount = 1;
   string temp = "TEMP";
   string token;  // token is used to store an element of string pf.
                    
   Stack<string> operands;
   string firstOp; // first operand loaded by register
   string secondOp; // second operand used in computation with first operand
   
   for (int i = 0; i < pf.length(); i++)
   {
      temp = "TEMP";
      token = pf[i]; 

      /* When token is an operator, firstOp and secondOp are assigned
         from operands stack and the proper register actions are displayed*/
      if (token == "*" || token == "/" || token == "+" || token == "-")
      {
         secondOp = operands.top();
         operands.pop();
            
         firstOp = operands.top();
         operands.pop();

         cout << "LD  " << firstOp << endl;

         if (token == "*")
            cout << "ML  " << secondOp << endl;            // these if/elses
         else if (token == "/")                            // check operator
            cout << "DV  " << secondOp << endl;            // for proper display
         else if (token == "+")
            cout << "AD  " << secondOp << endl;
         else
            cout << "SB  " << secondOp << endl;

         temp+= intToStr(tempCount); // "TEMP" is concatenated with tempCount
  
         operands.push(temp); //temp variable ("TEMPn") is pushed onto stack.
         tempCount++;
         cout << "ST  " << operands.top() <<endl;         
      }
            
      else
         operands.push(token);         
      
   }
   cout << endl; 
 }

/**********************************************************************
 * main
 *
 * Command line takes 2 arguments, a.out and the file name. Main will open
 * the file and read each line. Each line is has an infix expression that
 * is converted to postfix. Upon conversion of a single line, the postfix
 * expression is passed to the pfToAssembly function and the assembly
 * language equivalent is displayed. When complete, file is closed.
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
      ifstream fin;
      string infixExp;
      string postfixExp;

      fin.open(argv[1]);
      if (fin.fail())
      {
         cout << "\nFile not found\n";
         return 1;
      }

      while (getline(fin, infixExp))
      {
         postfixExp = postfix(infixExp);
         pfToAssembly(postfixExp);
      }

      fin.close();
   }
          
   return 0;
}
