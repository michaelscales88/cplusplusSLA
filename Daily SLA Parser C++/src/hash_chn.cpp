// Programmer: Michael Scales
// Project Number: 7
// Project Desc: Chaining
// Course: Data Structures
// Date: April 18, 2016

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <iomanip>

using namespace std;

#include "hash_chn.h"

Table::Table( ) {
	used = 0;
	for ( int i = 0; i < CAPACITY; i++ )
		table[i] = NULL;
}

void Table::insert( const RecordType & entry ) {
	bool alreadyThere;
	Node* nodePtr;

	assert( entry.key >= 0 );

	findPtr( entry.key, alreadyThere, nodePtr );
	if( !alreadyThere ) {
		int i = hash( entry.key );      // get index of "bucket" where entry belongs
		// insert at beginning of list
		Node* temp = new Node;
		temp->rec = entry;      // copy record
		temp->next = table[i];
		table[i] = temp;
		used++;
	} else {
		// nodePtr points to existing record that should be updated
		nodePtr->rec = entry;
	}
}


int Table::hash( int key ) const {
	return key % CAPACITY;
}

int Table::size( ) const {
	return used;
}

// findPtr function
//     void findPtr( int key, bool& found, Node*& nodePtr ) const;
// Preconditions:  key >= 0
// Postconditions: If a record with the indicated key is in the table,
//    then found is true and nodePtr is set to point to that record.
//    Otherwise, found is false and nodePtr contains garbage.

void Table::findPtr( int key, bool & found, Node* & nodePtr ) const {
	int i;
	Node* ptr;

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

void Table::find( int key, bool& found, RecordType& result ) const {
	Node* nodePtr;

	assert( key >= 0 );

	findPtr( key, found, nodePtr );
	if ( found ) {
		result = nodePtr->rec;
	}
}

void Table::erase( int key ) {
	assert( key >= 0 );
	bool found = false;
	Node* delNode;
	findPtr( key, found, delNode );
	if(found) {
		int index = hash(key);
		Node* firstNode = table[index];
		table[index] = firstNode->next;
		delNode->rec = firstNode->rec;
		delete firstNode;
		used--;
	} else {
		cerr << "Your entry is not found.";
	}

}

void Table::print() const {
	cout << "The hash table is: " << endl;
	cout << setw(5) << "Index  Key/Data" << endl;
	for( int i=0; i < CAPACITY; i++ ) {
		cout << setw(5) << i << "  ";
		Node * dispPtr = table[i];
		while(dispPtr != NULL) {
			cout << dispPtr->rec.key << "/";
			cout << dispPtr->rec.data << "  ";
			dispPtr = dispPtr->next;
		}
		cout << endl;
	}
	cout << endl;
}

