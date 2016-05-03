/*-- LReportQueue.h -------------------------------------------------------------

  This header file defines a ReportQueue data type.
  Basic operations:
    constructor:  Constructs an empty ReportQueue
    empty:        Checks if a ReportQueue is empty
    enReportQueue:      Modifies a ReportQueue by adding a value at the back
    front:        Accesses the top ReportQueue value; leaves ReportQueue unchanged
    deReportQueue:      Modifies ReportQueue by removing the value at the front
    display:      Displays all the ReportQueue elements
    Note: Execution terminates if memory isn't available for a ReportQueue element.
---------------------------------------------------------------------------*/

#include <iostream>
#include <new>

using namespace std;

#ifndef QREPORT_H
#define QREPORT_H

template <typename DataType>
class ReportQueue
{
 public:
 /***** Function Members *****/
 /***** Constructors *****/

  ReportQueue();
  /*-----------------------------------------------------------------------
    Construct a ReportQueue object.

    Precondition:  None.
    Postcondition: An empty ReportQueue object has been constructed.
        (myFront and myBack are initialized to null pointers).
  -----------------------------------------------------------------------*/

  ReportQueue(const ReportQueue & original);
  /*-----------------------------------------------------------------------
    Copy Constructor 

    Precondition:  original is the ReportQueue to be copied and is received 
        as a const reference parameter.
    Postcondition: A copy of original has been constructed.
  -----------------------------------------------------------------------*/

 /***** Destructor *****/
  ~ReportQueue(); 
  /*-----------------------------------------------------------------------
    Class destructor 

    Precondition:  None.
    Postcondition: The linked list in the ReportQueue has been deallocated.
  -----------------------------------------------------------------------*/

 /***** Assignment *****/
 const ReportQueue & operator= (const ReportQueue & rightHandSide);
  /*-----------------------------------------------------------------------
    Assignment Operator 

    Precondition:  rightHandSide is the ReportQueue to be assigned and is 
        received as a const reference parameter.
    Postcondition: The current ReportQueue becomes a copy of rightHandSide 
        and a reference to it is returned.
  -----------------------------------------------------------------------*/

  bool empty() const;
  /*-----------------------------------------------------------------------
    Check if ReportQueue is empty.

    Precondition:  None.
    Postcondition: Returns true if ReportQueue is empty and false otherwise.
  -----------------------------------------------------------------------*/

  void enqueue(const DataType & value);
  /*-----------------------------------------------------------------------
    Add a value to a ReportQueue.

    Precondition:  value is to be added to this ReportQueue.
    Postcondition: value is added at back of ReportQueue.               
  -----------------------------------------------------------------------*/

  void display(ostream & out) const;
  /*-----------------------------------------------------------------------
    Display values stored in the ReportQueue.

    Precondition:  ostream out is open.
    Postcondition: ReportQueue's contents, from front to back, have been 
        output to out.
  -----------------------------------------------------------------------*/

  DataType front() const;
  /*-----------------------------------------------------------------------
    Retrieve value at front of ReportQueue (if any).

    Precondition:  ReportQueue is nonempty.
    Postcondition: Value at front of ReportQueue is returned, unless the ReportQueue 
        is empty; in that case, an error message is displayed and a 
        "garbage value" is returned.
  -----------------------------------------------------------------------*/

  void dequeue();
  /*-----------------------------------------------------------------------
    Remove value at front of ReportQueue (if any).

    Precondition:  ReportQueue is nonempty.
    Postcondition: Value at front of ReportQueue has been removed, unless
        ReportQueue is empty; in that case, an error message is displayed 
        and execution allowed to proceed.
  -----------------------------------------------------------------------*/

 private:
   /*** Node class ***/
   class Node
   {
    public:
      DataType data;
      Node * next;
      //--- Node constructor
      Node(DataType value, Node * link = NULL)
      /*-------------------------------------------------------------------
        Precondition:  value and link are received
        Postcondition: A Node has been constructed with value in its 
            data part and its next part set to link (default 0).
       ------------------------------------------------------------------*/
      { data = value; next = link; }

  };

  typedef Node * NodePointer;

  /***** Data Members *****/
  NodePointer myFront,      // pointer to front of ReportQueue
              myBack;       // pointer to back of ReportQueue

}; // end of class declaration


//--- Definition of Queue constructor
template <typename DataType>
ReportQueue<DataType>::ReportQueue()
: myFront(NULL), myBack(NULL)
{}

//--- Definition of Queue copy constructor
template <typename DataType>
ReportQueue<DataType>::ReportQueue(const ReportQueue<DataType> & original)
{
   myFront = myBack = NULL;
   if (!original.empty())
   {
      // Copy first node
      myFront = myBack = new ReportQueue<DataType>::Node(original.front());

      // Set pointer to run through original's linked list
      NodePointer origPtr = original.myFront->next;
      while (origPtr != NULL)
      {
         myBack->next = new ReportQueue<DataType>::Node(origPtr->data);
         myBack = myBack->next;
         origPtr = origPtr->next;
      }
   }
}

//--- Definition of Queue destructor
template <typename DataType>
ReportQueue<DataType>::~ReportQueue()
{ 
  // Set pointer to run through the queue
  NodePointer prev = myFront,
                     ptr;
  while (prev != NULL)
    {
      ptr = prev->next;
      delete prev;
      prev = ptr;
    }
}

//--- Definition of assignment operator
template <typename DataType>
const ReportQueue<DataType> & ReportQueue<DataType>::operator=(const ReportQueue<DataType> & rightHandSide)
{
   if (this != &rightHandSide)         // check that not q = q
   {
      this->~ReportQueue();                  // destroy current linked list
      if (rightHandSide.empty())       // empty queue
         myFront = myBack = NULL;
      else
      {                                // copy rightHandSide's list
         // Copy first node
         myFront = myBack = new ReportQueue<DataType>::Node(rightHandSide.front());

         // Set pointer to run through rightHandSide's linked list
         ReportQueue::NodePointer rhsPtr = rightHandSide.myFront->next;
         while (rhsPtr != NULL)
         {
           myBack->next = new ReportQueue<DataType>::Node(rhsPtr->data);
           myBack = myBack->next;
           rhsPtr = rhsPtr->next;
         }
      }
   }
   return *this;
}

//--- Definition of empty()
template <typename DataType>
bool ReportQueue<DataType>::empty() const
{ 
   return (myFront == NULL); 
}

//--- Definition of enqueue()
template <typename DataType>
void ReportQueue<DataType>::enqueue(const DataType & value)
{
   ReportQueue::NodePointer newptr = new ReportQueue<DataType>::Node(value);
   if (empty())
      myFront = myBack = newptr;
   else
   {
      myBack->next = newptr;
      myBack = newptr;
   }
}

//--- Definition of display()
template <typename DataType>
void ReportQueue<DataType>::display(ostream & out) const
{
   NodePointer ptr;
   int numPasses = 1;
   for (ptr = myFront; ptr != NULL; ptr = ptr->next) {
   		//cout << "numPasses: " << numPasses;
   		ptr->data.inorder(out);
   		numPasses++;
   }
     
   out << endl;

}

//--- Definition of front()
template <typename DataType>
DataType ReportQueue<DataType>::front() const
{
   if (!empty())
      return (myFront->data.inorder(cout));
   else
   {
      cerr << "*** Queue is empty "
              " -- returning garbage ***\n";
      DataType * temp = new(DataType);  
      DataType garbage = *temp;     // "Garbage" value
      delete temp;
      return garbage;
   }
}

//--- Definition of dequeue()
template <typename DataType>
void ReportQueue<DataType>::dequeue()
{
   if (!empty())
   {
      NodePointer ptr = myFront;
      myFront = myFront->next;
      delete ptr;
      if (myFront == NULL)     // queue is now empty
         myBack = NULL;
   }   
   else
      cerr << "*** Queue is empty -- can't remove a value ***\n";
}

#endif
