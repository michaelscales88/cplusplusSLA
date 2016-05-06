#include <iostream>
#include <cstring>

#include "Call.h"

using namespace std;

Call::Call()
		:clientName(999), callId(0), intNumber(555), 
		extNumber(666), answered(true), startTime(0), endTime(0) 
{}

Call::Call(int clientName, int newCallId, int intNumber, int extNumber, 
						string startTime, string endTime, bool answered)
		:clientName(clientName), callId(newCallId), intNumber(intNumber), 
		extNumber(extNumber), answered(answered), startTime(0), endTime(0) {
	setTime(startTime, endTime);
}
#if 0
Call::~Call(){
	delete this;
}
#endif

int Call::getClientName() const {
	return clientName;
}

int Call::getCallId() const{
	return callId;	
}

int Call::getIntNumber() const{
	return intNumber;
}

int Call::getExtNumber() const{
	return extNumber;
}

int Call::getStartTime() const{
	return startTime;
}

int Call::getEndTime() const{
	return endTime;
}

bool Call::isAnswered() const{
	return answered;
}	

void Call::setTime(string startTime, string endTime){
	this->startTime = stoi(startTime);
	this->endTime = stoi(endTime);
}

void Call::display( ostream & out ) const {
		out << "clientName: " << clientName << endl;
		out << "callId: " << callId << endl;
		out << "intNumber: " << intNumber << endl;
		out << "extNumber: " << extNumber << endl;
		out << "startTime: " << startTime << endl;
		out << "endTime: " << endTime << endl;
		out << "answered: " << boolalpha << answered << endl;		
}

//--- Definition of output operator
ostream & operator<< (ostream & out, const Call & aCall) {
	aCall.display(out);
	return out;
}

bool Call::operator<(const Call & rightHandSide) {
	int rhs = rightHandSide.callId;
	return callId<rhs;
}

Call Call::operator= (const Call * rightHandSide){
	if (this != rightHandSide) { // check that not self-assignment
		clientName = rightHandSide->clientName;
		callId = rightHandSide->callId;
		intNumber = rightHandSide->intNumber;
		extNumber = rightHandSide->extNumber;
		startTime = rightHandSide->startTime;
		endTime = rightHandSide->endTime;
		answered = rightHandSide->answered;
	}
	return *this;
}
