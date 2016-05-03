#include <cstdlib>

using namespace std;

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
	Records newRecord;
	RecordType<Records> newRec;
	
	return EXIT_SUCCESS;
}
