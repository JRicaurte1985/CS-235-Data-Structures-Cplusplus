/***********************************************************************
* Program:
*    Assignment 256  
*    Brother Ercanbrack, CS235
* Author:
*    Jose Ricaurte
* Summary: Read a GEDCOM file, parse it to build a sorted linked list
* and a Binary Tree. The data structure used has 3 pointers. The next  
* pointer is to build the linked list. The father and mother pointers   
* are used to build the family tree. father is left, mother is right.  
* The program writes the sorted list to a file named 'sorted.dat', then
* the binary tree is displayed in level order on the screen.   
************************************************************************/

#include <iostream>
#include <fstream>
using namespace std;

class GNode
{
   private:
      string firstName;            
      string lastName;
      string day;
      string month;
      string year;
      string iNum;
      GNode* father;
      GNode* mother;
      GNode* next;
            
   public:
      GNode()   {mother = NULL; father = NULL; next = NULL;}                
      string getFName()   {return firstName;}            
      string getLName()   {return lastName;}
      string getDay()   {return day;}
      string getMonth()   {return month;}
      string getYear()   {return year;}
      string getINum()   {return iNum;}
      GNode* getFather()   {return father;}
      GNode* getMother()   {return mother;}
      GNode* getNext()   {return next;}
      void setFName(string aFirst)   {firstName = aFirst;}
      void setLName(string aLast)   {lastName = aLast;}
      void setDay(string aDay)   {day = aDay;}
      void setMonth(string aMonth)   {month = aMonth;}
      void setYear(string aYear)   {year = aYear;}
      void setINum(string aINum)   {iNum = aINum;}
      void setFather(GNode* aFather)   {father = aFather;}
      void setMother(GNode* aMother)   {mother = aMother;}
      void setNext(GNode* aNext)   {next = aNext;}
};

void parseFile(ifstream &inFile, GNode* &aHead);
void insert (GNode* &listHead, GNode* &aPtr);
void displayList(ofstream &outFile, GNode* &aHead);
void displayLevel(GNode* &aHead);
void clear(GNode* &ptr);

/**********************************************************************
 * main description - opens the GEDCOM file, parses the file (this function
 * creates an alphabetically ordered linked list and a binary tree from the
 * GEDCOM file, with 'treeHead' as the head node of this data structure.
 * displayList writes the linked list to a file named "sorted.dat"
 * displayLevel displays the binary tree to the screen.
 ***********************************************************************/
int main(int argc, char* argv[])
{
   if (argc != 2)
   {
      cout << "Usage: " << "a.out fileName" << endl;
      return 1;
   }
   ifstream fin(argv[1]);
   if (fin.fail())
   {
      cout << "\nFile not found\n";
      return 1;
   }
   ofstream fout("sorted.dat");
   GNode* treeHead = NULL;
   parseFile(fin, treeHead);
   displayList(fout, treeHead);
   displayLevel(treeHead);
   clear(treeHead); // delete all nodes
   fin.close();
   fout.close();
   return 0;
}

/**********************************************************************
 * parseFile -
 ***********************************************************************/
void parseFile(ifstream &inFile, GNode* &aHead)
{
   GNode* ptr = NULL; // traversal pointer
   int count = 0;
   string temp1; // assign every word in file to temp1
   string temp2; // helper string in parse logic
   int i = 0;
   while (true)
   {
      getline (inFile, temp1);
      
      if (temp1 == "0 @F1@ FAM")
         break;     

      //We've reached a new node. Insert previous Node, then start new Node.
      if (temp1[0] == '0' && temp1[3] == 'I')
      {
         insert(aHead, ptr);
         temp2.clear();
         temp1.erase(0, 3);
         //create INum string
         while (temp1[0] != '@')
         {
            temp2 += temp1[0];
            temp1.erase(0,1);
         }
         ptr = new GNode;
         ptr->setINum(temp2);
         
      }
      //parse and store first Name
      else if (temp1[0] == '2' && temp1[2] == 'G')
      {
         temp1.erase(0,7);
         ptr->setFName(temp1);
      }
      //parse and store last Name
      else if (temp1[0] == '2' && temp1[2] == 'S' && temp1[3] == 'U')
      {
         temp1.erase(0, 7);
         ptr->setLName(temp1);
      }
      //parse and store Birth Date
      else if (temp1[0] == '1' && temp1[2] == 'B' && temp1[3] == 'I')
      {
         getline(inFile, temp1);
         if (temp1.find("DATE") != std::string::npos) // make sure date exists
         {
            temp1.erase(0,7);
            temp2.clear();
            if (temp1.length() != 0) // do parse only if not blank date
            {
               //extract the month, delete from string
               for (int i = 0; i < temp1.length(); i++)
               {
                  if (isalpha(temp1[i]))
                  {
                     temp2 += temp1[i];
                     temp1.erase(i, 1);
                     i--;
                  }
               }
               ptr->setMonth(temp2); // set month. if no month existed, no harm
               temp2.erase();
               //at this point the string is either **__****, _****, or ****
               //eliminate middle case. Reduces cases to **__**** or ****
               if (temp1[0] == ' ')
                  temp1.erase(0, 1);
               //read in numbers and '/' only. Will stop at space or end
               while (temp1.length() != 0 && (isdigit(temp1[0])
                      || temp1[0] == '/'))
               {
                  temp2 += temp1[0];
                  temp1.erase(0, 1);
               }
               if (temp2.length() > 2) //if true, year was read, no day exists
                  ptr->setYear(temp2); 
               else
                  ptr->setDay(temp2); // else, day was read. set day
               
               if (temp1.length() != 0) // if day was read, still need year
               {
                  temp1.erase(0, 2); // eliminate spaces from __****
                  temp2.clear();
               
                  while (temp1.length() != 0) // read in year
                  {
                     temp2 += temp1[0];
                     temp1.erase(0, 1);  
                  }
                  ptr->setYear(temp2); // set year
               }
            }   
         } 
      }
   }
   insert(aHead, ptr);
 
   // Algorithm to Build Binary Tree:
   /* Parse file, store mother, father, and child INums in temp strings.
      Use 2 pointers to compare node INums to temp INums to find the
      appropriate nodes to link */  
   string fatherINum; 
   string motherINum;
   string childINum;;
  
   ptr = aHead; // reset traversal pointer. Use to traverse children
   GNode* ptr2 = ptr; // another traversal pointer. Use to traverse to parents.
   while (true)
   {
      getline(inFile, temp1);
      if (temp1 == "0 @S1@ SOUR")
         break;
      
      if (temp1[0] == '1' && temp1[2] == 'H') // check for father
      {
         temp1.erase(0,8);
         temp2.clear();
         while (temp1[0] != '@')
         {
            temp2 += temp1[0];
            temp1.erase(0,1);
         }
         fatherINum = temp2;
      }
      else if (temp1[0] == '1' && temp1[2] == 'W') // check for mother
      {
         temp1.erase(0,8);
         temp2.clear();
         while (temp1[0] != '@')
         {
            temp2 += temp1[0];
            temp1.erase(0,1);
         }
         motherINum = temp2;
      }
      else if (temp1[0] == '1' && temp1[2] == 'C')//set mother/father 
      {
         temp1.erase(0,8);
         temp2.clear();
         while (temp1[0] != '@')
         {
            temp2 += temp1[0];
            temp1.erase(0,1);
         }
         childINum = temp2;

         ptr = aHead;
         ptr2 = aHead;
         while (childINum != ptr->getINum())
            ptr = ptr->getNext();
  
         while (fatherINum != "" && fatherINum != ptr2->getINum())
            ptr2 = ptr2->getNext();
      
         if (fatherINum != "")
            ptr->setFather(ptr2);
         
         ptr2 = aHead;
         while (motherINum != "" && motherINum != ptr2->getINum())
            ptr2 = ptr2->getNext();
         
         if (motherINum != "")
            ptr->setMother(ptr2);
         fatherINum.clear();
         motherINum.clear();
      }
   }  
}

/**********************************************************************
 * insert - a sorted insertion
 ***********************************************************************/
void insert(GNode* &listHead, GNode* &aPtr)
{
   //aPtr not rdy to be inserted. Occurs on first individual in parseFile()
   if(aPtr == NULL)
      return;
   //first insertion. set head
   if(listHead == NULL)
   {
      listHead = aPtr;
      return;
   }
   string ptrLName = aPtr->getLName();
   ptrLName[0] = toupper(ptrLName[0]);
  
   string headLName = listHead->getLName();
   headLName[0] = toupper(headLName[0]);
  
   // head insert
   if (ptrLName < headLName)
   {
      aPtr->setNext(listHead);
      listHead = aPtr;
      return;
   }
   else if (ptrLName == headLName && aPtr->getFName() < listHead->getFName())
   {
      aPtr->setNext(listHead);
      listHead = aPtr;
      return;
   }

   GNode* p = listHead; // traversal pointer, 'previous'
   GNode* c = listHead->getNext(); //traversal pointer, 'current'
   string cLName;

   //traverse, comparing last names,then first Name, then date
   while (c != NULL)
   {
      cLName = c->getLName();
      cLName[0] = toupper(cLName[0]);
   
      if (ptrLName > cLName)
      {
         p = c;
         c = c->getNext();
      }
      else if (ptrLName == cLName && aPtr->getFName() > c->getFName())
      {
         p = c;
         c = c->getNext();
      }
      else if (ptrLName == cLName && aPtr->getFName() == c->getFName()
               && aPtr->getYear() > c->getYear())
      {
         p = c;
         c = c->getNext();
      }
      else
         break;    
   }
   p->setNext(aPtr);
   aPtr->setNext(c);
}

/**********************************************************************
 * displayList - displays a linked list, starting with the head argument.
 ***********************************************************************/
void displayList(ofstream &outFile, GNode* &aHead)
{
   GNode* ptr = aHead;
   
   while (ptr != NULL)
   {
      if (ptr->getFName() != "")
         outFile << ptr->getFName();
      if (ptr->getLName() != "" && ptr->getFName() != "")
         outFile << " " << ptr->getLName();
      else
         outFile << ptr->getLName();
      
      if (ptr->getDay() != "" || ptr->getMonth() != "" || ptr->getYear() != "")
         outFile << ", b. ";
      if (ptr->getDay() != "")
         outFile << ptr->getDay() << " ";
      if (ptr->getMonth() != "")
         outFile << ptr->getMonth() << " ";
      if (ptr->getYear() != "")
         outFile << ptr->getYear();
      outFile << endl;
      ptr = ptr->getNext();
   }     
}

/**********************************************************************
 * displayLevel - level order traversal and display
 ***********************************************************************/
void displayLevel(GNode* &aHead)
{
   const int MAX = 150;
   GNode* queue[MAX];
   GNode* temp = aHead;
   int front = 0;
   int back = 0;
   int saveBack = 1;
   int generation = 0;
 
   while (temp->getINum() != "I1")// get temp to the I1 node
      temp = temp->getNext();
   
   queue[back++] = temp;
   cout << "The Ancestors of " << temp->getFName() << " " << temp->getLName()
        << ":" << endl;
   while (front != back)
   {
      temp = queue[front];
      if (front == saveBack)
      {
         generation++;
         saveBack = back;
         if (generation == 1)
            cout << "Parents:" << endl;
         else if (generation == 2)
            cout << "Grandparents:" << endl;
         else if (generation == 3)
            cout << "Great Grandparents:" << endl;
         else if (generation == 4)
            cout << "2nd Great Grandparents:" << endl;
         else if (generation == 5)
            cout << "3rd Great Grandparents:" << endl;
         else if (generation == 6)
            cout << "4th Great Grandparents:" << endl;
         else if (generation == 7)
            cout << "5th Great Grandparents:" << endl;
      }      
      front = (front + 1) % MAX;
      
      if (temp != NULL)
      {
         if (front != 1)
         {
            cout << "        ";
            if (temp->getFName() != "")
               cout << temp->getFName();
            if (temp->getLName() != "" && temp->getFName() != "")
               cout << " " << temp->getLName();
            else
               cout << temp->getLName();
      
            if (temp->getDay() != "" || temp->getMonth() != ""
                || temp->getYear() != "")
               cout<< ", b. ";
            if (temp->getDay() != "")
               cout << temp->getDay() << " ";
            if (temp->getMonth() != "")
               cout << temp->getMonth() << " ";
            if (temp->getYear() != "")
               cout << temp->getYear();
            cout << endl;
         }         
         queue[back] = temp->getFather();
         back = (back + 1) % MAX;
         queue[back] = temp->getMother();
         back = (back + 1) % MAX;
      }
   }
}

/**********************************************************************
 * clear - free all dynamic memory
 ***********************************************************************/
void clear(GNode* &aHead)
{
   GNode* ptr = aHead;
   while (ptr != NULL)
   {
      ptr = ptr->getNext();
      delete aHead;
      aHead = ptr;
   }
}
