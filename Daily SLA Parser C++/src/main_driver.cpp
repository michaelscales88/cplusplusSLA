#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <typeinfo>
#include <vector>

using namespace std;

#include "hash_chn.h"
#include "Call.h"

typedef RecordType<Call> newRec;
typedef Table<newRec> newTable;
typedef vector<newRec> newCallVector;

void mainMenu();

int main() {
	int testArray[29] = {7506, 7507, 7509, 7515, 7517, 7521, 7523, 7524, 7527, 7539, 7544, 7545, 7548, 
						7549, 7551, 7553, 7557, 7558, 7561, 7567, 7576, 7577, 7578, 7579, 7589, 7595, 
						7591, 7592, 7593};
	srand(time(NULL));
	bool continueGoing = true;
	char userInput;
	int intInput, intInput2, randomNumber, numClients;
	newRec rec;
	newTable testTable;
	newCallVector newVector;
	Call * newCall = NULL;
	
	cout << "How many calls?";
	cin >> intInput;
	for(int startPt = 0; startPt < intInput; startPt++) {
		randomNumber = (rand() % 50000 + 1);
		newCall = new Call(testArray[randomNumber % 30] , (randomNumber), (startPt + 2), (startPt + 3), to_string(startPt), to_string(startPt + 3), false);
		
		rec.key1 = newCall->getClientName();
		rec.key2 = newCall->getCallId();
		rec.data = newCall;
		
		newVector.push_back(rec);	
	}

	while(!newVector.empty())
	{	
		cout << typeid(newVector.back().data).name() << endl;
		cout << *newVector.back().data;
		
		testTable.insert(&newVector.back());
		newVector.pop_back();
	}

	//testTable.print();
	while(continueGoing)
	{	
		mainMenu();
		cin >> userInput;
		userInput = toupper(userInput);
		switch(userInput) {
			case 'P': {
				testTable.print();
				break;
			}
			case 'E': {
				cout << "Which key?";
				cin >> intInput;
				cout << "Which key2?";
				cin >> intInput2;
				testTable.erase(intInput, intInput2);
				break;
			}
			case 'Q': {
				continueGoing = false;
				break;
			}
			case 'V': {
				cout << "Which key?";
				cin >> intInput;
				cout << "Which key2?";
				cin >> intInput2;
				testTable.printRecord(intInput, intInput2);
				break;
			}
			default:
				break;
		}
	}
	return EXIT_SUCCESS;
}

void mainMenu(){
	cout << "Menu: " << endl;
	cout << "Print table: P" << endl;
	cout << "Erase entry: E" << endl;
	cout << "Quit: Q" << endl;
}
