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
	srand(time(NULL));
	bool continueGoing = true;
	char userInput;
	int intInput, intInput2, randomNumber, numClients;
	newRec rec;
	newTable testTable;
	newCallVector newVector;

	cout << "How many clients?";
	cin >> numClients;
	cout << "How many calls?";
	cin >> intInput;
	for(int numClient = 0; numClient < numClients; numClient++) {
		for(int startPt = 0;  startPt < intInput; startPt++) {
			randomNumber = (rand() % 500001);
			Call newCall = Call((numClient) , (randomNumber), (startPt + 2), (startPt + 3), to_string(startPt), to_string(startPt + 3), false);
			rec.key1 = newCall.getClientName();
			rec.key2 = newCall.getCallId();
			rec.data = &newCall;
			newVector.push_back(rec);
		}
	}
	
	for(int v_passes = 0; v_passes < newVector.size(); v_passes++)
	{
		testTable.insert(newVector[v_passes]);
	}
	#if 0
	cout << "vector size: " << newVector.size() << endl;
	cout << testTable.size() << endl;
	#endif
	testTable.print();
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
