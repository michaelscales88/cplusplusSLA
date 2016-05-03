// Programmer: Michael Scales
// Project Desc: SLA Call tool in c++
// Date: April 21, 2016

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

#include "hash_chn.h"
#include "Call.h"

//Table<RecordType<Call>> newTable;
RecordType<Call> newRec;

int main() {
	bool continueGoing = true;
	char userInput;
	int intInput, randomNumber, numClients;
	//newTable testTable;
	
	while(continueGoing)
	{
		cout << "How many clients?";
		cin >> numClients;
		cout << "How many calls?";
		cin >> intInput;
		for(int numClient = 0; numClient < numClients; numClient++) {
			for(int startPt = 0;  startPt < intInput; startPt++) {
				randomNumber = (rand() % 500001);
				Call newCall = Call(randomNumber % 10 , (randomNumber), (startPt + 2), (startPt + 3), to_string(startPt), to_string(startPt + 3), true);
				//testTable.insert()
				//RecordType<Call> newRec = {((randomNumber % 10) , (randomNumber), (startPt + 2), (startPt + 3), to_string(startPt), to_string(startPt + 3), true)};
			}
		}

		cout << "quit?";
		cin >> userInput;
		if(toupper(userInput) == 'Y')
		{
			break;
		}
	}
	return EXIT_SUCCESS;
}
