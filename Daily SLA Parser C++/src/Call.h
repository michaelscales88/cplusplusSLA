#include <iostream>
#include <cstring>

using namespace std;

#ifndef CALL_H
#define CALL_H

class Call {
	private:
		int clientName,
		callId,
		intNumber,
		extNumber,
		startTime,
		endTime;
		bool answered;
			
		/***** Private Function Members *****/
		void setTime(string startTime, string endTime);
		
	public:
		/***** Function Members *****/
		Call();
		Call(int clientName, int newCallId, int intNumber, 
			int extNumber, string startTime, string endTime, bool answered);
		int getClientName() const;
		int getCallId() const;
		int getIntNumber() const;
		int getExtNumber() const;
		int getStartTime() const;
		int getEndTime() const;
		bool isAnswered() const;	
		void display( ostream & out ) const;
		/***** Assignment *****/
		bool operator< (const Call & rightHandSide);
		/*------------------------------------------------------------------------
		Assignment Operator 
		Precondition:  rightHandSide is the stack to be assigned and is 
		received as a const reference parameter.
		Postcondition: The current stack becomes a copy of rightHandSide
		and a reference to it is returned.
		------------------------------------------------------------------------*/
		
		Call operator= (const Call * rightHandSide);
		/*------------------------------------------------------------------------
		Assignment Operator 
		Precondition:  rightHandSide is the stack to be assigned and is 
		received as a const reference parameter.
		Postcondition: The current stack becomes a copy of rightHandSide
		and a reference to it is returned.
		------------------------------------------------------------------------*/		
};

//------ Prototype of output operator
ostream & operator<< (ostream & out, const Call & aCall);
/*----------------------------------------------------------------------
Displays the output of the list using overloaded <<.

Precondition:  None
Postcondition: Calls the display function to display the contents of the
list to the screen.
-----------------------------------------------------------------------*/

#endif
