#include <cstdlib>
#include <map>
#include <iostream>
#include <vector>
#include <ctime>

using namespace std;

map<int, int> HASH_CLIENT = {{60,50},{40,50}};

template <typename DataType>
struct RecordType {
	int key;
	DataType data;
};

class Records
{
	private:
		int something;
		
	public:
		Records();
};

Records::Records():something(0)
{
}

int main()
{	
	srand(time(NULL));
	vector<int> newVector;
	int userResp;
	Records newRecord;
	RecordType<Records> newRec;
	cout << "which key?";
	cin >>	userResp;
	//cout << HASH_CLIENT[userResp];
	for(int passes = 0; passes < userResp; passes++) {
		newVector.push_back(passes);
	}
	for(int passes2 = 0; passes2 < newVector.size(); passes2++) {
		cout << newVector[passes2] << " ";
	}
	cout << endl;
	
	system("pause");
}
