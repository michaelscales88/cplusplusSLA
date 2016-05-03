#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

#include "ChnReport.h"
#include "Call.h"

template <typename DataType>
Table<DataType>::Table() {
	used = 0;
	for ( int i = 0; i < CAPACITY; i++ )
		table[i] = NULL;
}

template <typename DataType>
void Table<DataType>::insert( const DataType & entry ) {
	bool alreadyThere;
	DataType * nodePtr;

	assert( entry.key >= 0 );

	findPtr( entry.key, alreadyThere, nodePtr );
	if( !alreadyThere ) {
		int i = hash( entry.key );      // get index of "bucket" where entry belongs
		// insert at beginning of list
		DataType * temp = new DataType;
		temp->rec = entry;      // copy record
		temp->next = table[i];
		table[i] = temp;
		used++;
	} else {
		// nodePtr points to existing record that should be updated
		nodePtr->rec = entry;
	}
}

template <typename DataType>
int Table<DataType>::hash( int key ) const {
	return key % CAPACITY;
}

template <typename DataType>
int Table<DataType>::size( ) const {
	return used;
}

template <typename DataType>
void Table<DataType>::findPtr( int key, bool & found, DataType * & nodePtr ) const {
	int i;
	DataType * ptr;

	i = hash( key );
	ptr = table[i];
	found = false;
	while ( !found && ptr != NULL ) {
		if ( key == ptr->rec.key ) {
			found = true;
			nodePtr = ptr;
		}
		ptr = ptr->next;
	}
	if ( !found )
		nodePtr = NULL;
}

template <typename DataType>
void Table<DataType>::find( int key, bool& found, RecordType<DataType> & result ) const {
	DataType * nodePtr;

	assert( key >= 0 );

	findPtr( key, found, nodePtr );
	if ( found ) {
		result = nodePtr->rec;
	}
}

template <typename DataType>
void Table<DataType>::erase( int key ) {
	assert( key >= 0 );
	bool found = false;
	DataType * delNode;
	findPtr( key, found, delNode );
	if(found) {
		int index = hash(key);
		DataType * firstNode = table[index];
		table[index] = firstNode->next;
		delNode->rec.data = firstNode->rec.data;
		delNode->rec.key = firstNode->rec.key;
		delete firstNode;
		used--;
	} else {
		cerr << "Your entry is not found.";
	}

}

template <typename DataType>
void Table<DataType>::print() const {
	cout << "The hash table is: " << endl;
	for( int i=0; i < CAPACITY; i++ ) {
		cout << setw(5) << "Index: " << i << " ";
		DataType * dispPtr = table[i];
		if(dispPtr != NULL) {
			cout << endl;
			while(dispPtr != NULL) {
				cout << "Key: " << dispPtr->rec.key << " ";
				cout << "Data: " << dispPtr->rec.data << " -> ";
				dispPtr = dispPtr->next;
			}
		}
		cout << "NULL";
		cout << endl;
	}
	cout << endl;
}

