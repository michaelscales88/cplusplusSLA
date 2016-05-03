// Programmer: Michael Scales
// Project Desc: SLA Call tool in c++
// Date: April 21, 2016

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <ctime>

using namespace std;

#include "Call.h"
#include "Client.h"
#include "Report.h"
#include "ChnReport.h"

typedef Client<Call> newClient;
typedef ReportQueue<newClient> newReport;
typedef RecordType<Call> newRecord;
typedef Table<newRecord> newTable;

/*int main() {
	srand(time(NULL));
	bool continueGoing = true;
	char userInput;
	int intInput, randomNumber, numClients;
	newClient testClient;
	newReport testReport;
	//newTable testTable; // this breaks it
	newRecord rec;
	
	while(continueGoing)
	{
		cout << "How many clients?";
		cin >> numClients;
		cout << "How many calls?";
		cin >> intInput;
		for(int numClient = 0; numClient < numClients; numClient++) {
			for(int startPt = 0;  startPt < intInput; startPt++) {
				randomNumber = (rand() % 500001);
				Call newCall = Call(randomNumber % 10 , (randomNumber), (startPt + 2), (startPt + 3), to_string(startPt), to_string(startPt + 3), (startPt % 2));
				testClient.insert(newCall);
				rec.key = newCall.getClientName();
				rec.data = & newCall;
				cout << rec.key;
				cout << (rec.data)->getCallId;
				//testTable.insert(rec);
			}
			testReport.enqueue(testClient);
			//newTable.insert()
		}
		//testReport.front();
		testReport.display(cout);
		//cout << "height: " << testClient.height() << endl;
		//cout << "leafcount: " << testClient.leafCount() << endl;
		//testClient.inorder(cout);
		//testClient.graph(cout);
		//cout << boolalpha << (newCall2 < newCall1);
		cout << "quit?";
		cin >> userInput;
		if(toupper(userInput) == 'Y')
		{
			break;
		}
	}
	return EXIT_SUCCESS;
}*/
