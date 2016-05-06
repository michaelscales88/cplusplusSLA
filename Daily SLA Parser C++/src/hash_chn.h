// Programmer: Michael Scales
// Project Number: 7
// Project Desc: Chaining
// Course: Data Structures
// Date: April 18, 2016

// Table class

// Warning: The Table class does not have:
//     a destructor,
//     copy constructor,
//     or overloaded assignment operator.
// Do not depend on any of these working correctly.
// You should be able to do this assignment
// without having to to write these functions.
// Just do not pass a Table by value, assign a Table to another Table, etc.

#include <cassert>
#include <map>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <typeinfo>

using namespace std;

#include "Call.h"

#ifndef hash_chn
#define hash_chn

typedef int ItemType;
const int CAPACITY = 31;
map<int, int> HASH_CLIENT = {{7506,1},{7507,2},{7509,3},{7515,4},{7517,5},{7521,6},
							{7523,7},{7524,8},{7527,9},{7539,10},{7544,11},{7545,12},
							{7548,13},{7549,14},{7551,15},{7553,16},{7557,17},{7558,18},
							{7561,19},{7567,20},{7576,21},{7577,22},{7578,23},{7579,24},
							{7589,25},{7595,26},{7591,27},{7592,28},{7593,29}};

template <typename DataType>
struct RecordType {
	int key1, key2;
	DataType * data;
};

template <typename DataType>
class Table {
	public:
		Table();
		/*------------------------------------------------------------------------
		Construct a Table object.

		Precondition:  None.
		Postcondition: The table is initialized as an empty table.
		-----------------------------------------------------------------------*/

		void insert( DataType * entry );
		/*------------------------------------------------------------------------
		Inserts a record into the table.

		Precondition:  Entry.key >= 0.
		Postcondition: The entry will be added to the table. If a record exists
			additional records will exist as a linked list with the first node at
			the index position.
		Note: insert uses auxiliary function findPtr()
		-----------------------------------------------------------------------*/

		void find( int key, bool& found, DataType & result ) const;
		/*------------------------------------------------------------------------
		Searches the table for the record associated with the provided key.

		Precondition: Key >= 0.
		Postcondition: Returns the record if found. Provides error message if
			not.
		Note: find uses auxiliary function findPtr()
		-----------------------------------------------------------------------*/

		int size() const;
		/*------------------------------------------------------------------------
		Returns the number of records in the table.

		Precondition:  None.
		Postcondition: Returns the number of records in the table as an int.
		-----------------------------------------------------------------------*/
		
		void printRecord(int key1, int key2) const;
		/*------------------------------------------------------------------------
		Displays the contents of the one record.

		Precondition:  None.
		Postcondition: Prints the full contents of the record.
		Note: Uses Call::display()
		-----------------------------------------------------------------------*/
		
		void print() const;
		/*------------------------------------------------------------------------
		Displays the contents of the table.

		Precondition:  None.
		Postcondition: Prints the key/data for every record of every index in
			the table.
		-----------------------------------------------------------------------*/

		void erase( int key1, int key2 );
		/*------------------------------------------------------------------------
		Erases the record associated with the key.

		Precondition: Key >= 0.
		Postcondition: Deletes the node containing the provided key.
		Note: erase uses auxiliary function findPtr()
		-----------------------------------------------------------------------*/
		
		~Table();
		/*------------------------------------------------------------------------
		Erases the record associated with the key.

		Precondition: Key >= 0.
		Postcondition: Deletes the node containing the provided key.
		Note: erase uses auxiliary function findPtr()
		-----------------------------------------------------------------------*/
		
	private:
		/*** Node class ***/
		class Node
		{
		public:
			DataType * data;
			Node * next;
			//--- Node constructor
			Node(DataType * value, Node* link = NULL)
			: data(value), next(link)
			{}
			/*-------------------------------------------------------------------
			Precondition:  None.
			Postcondition: A Node has been constructed with value in its data 
			    part and its next part set to link (default 0).
			-------------------------------------------------------------------*/
			~Node();
		};
		
		typedef Node * NodePointer;
		
		int hash( int key ) const;
		/*------------------------------------------------------------------------
		Hashes the key to provide a unique index for a record.

		Precondition:  None.
		Postcondition: An int index is returned based on f(key)= key % CAPACITY
		-----------------------------------------------------------------------*/

		void findPtr( int key1, int key2, bool& found, NodePointer & nodePtr ) ;
		/*------------------------------------------------------------------------
		Searches the table for the key.

		Precondition:  None.
		Postcondition: If the key is found, bool is set to true and the ptr is
			set	to the location of that key's node.
		-----------------------------------------------------------------------*/
				 
		NodePointer table[CAPACITY];
		int used;


};

template <typename DataType>
Table<DataType>::Table() {
	used = 0;
	for ( int i = 0; i < CAPACITY; i++ )
		table[i] = NULL;
}

template <typename DataType>
Table<DataType>::Node::~Node() {
	delete this->data->data;
}

template <typename DataType>
Table<DataType>::~Table() {
	NodePointer delNode = NULL;
	NodePointer nodePtr = NULL;
	Call * delCall = NULL;
	for(int index = 0; index < CAPACITY; index++) {
		nodePtr = table[index];
		while(nodePtr != NULL){
			delCall = nodePtr->data->data;
			nodePtr = nodePtr->next;
			delete delCall;
		}
		while(nodePtr != NULL){
			delNode = nodePtr;
			nodePtr = nodePtr->next;
			delete delNode;
		}
	}
}

template <typename DataType>
void Table<DataType>::insert( DataType * entry ) {
	bool alreadyThere;
	NodePointer nodePtr;

	assert( entry->key1 >= 0 && entry->key2 >= 0 );

	findPtr( entry->key1, entry->key2, alreadyThere, nodePtr );
	if( !alreadyThere ) {
		int i = hash( entry->key1 );      // get index of "bucket" where entry belongs
		// insert at beginning of list
		NodePointer temp = new(nothrow) Node(entry);
		//temp->data = &entry;      // copy record
		temp->next = table[i];
		table[i] = temp;
		used++;
	} else {
		// nodePtr points to existing record that should be updated
		nodePtr->data = entry;
	}
}

template <typename DataType>
int Table<DataType>::hash( int key ) const {
	return HASH_CLIENT[key];
}

template <typename DataType>
int Table<DataType>::size( ) const {
	return used;
}

// findPtr function
//     void findPtr( int key, bool& found, Node*& nodePtr ) const;
// Preconditions:  key >= 0
// Postconditions: If a record with the indicated key is in the table,
//    then found is true and nodePtr is set to point to that record.
//    Otherwise, found is false and nodePtr contains garbage.

template <typename DataType>
void Table<DataType>::findPtr( int key1, int key2, bool & found, NodePointer & nodePtr ) {
	int i;
	NodePointer ptr;

	i = hash( key1 );
	ptr = table[i];

	found = false;
	while ( !found && ptr != NULL ) {
		if ( key1 == ptr->data->key1 ) {
			if( key2 == ptr->data->key2) {
				found = true;
				nodePtr = ptr;
			}
		}
		ptr = ptr->next;
	}
	if ( !found )
		nodePtr = NULL;
}

template <typename DataType>
void Table<DataType>::find( int key, bool& found, DataType & result ) const {
	NodePointer nodePtr;

	assert( key >= 0 );

	findPtr( key, found, nodePtr );
	if ( found ) {
		result = nodePtr->data;
	}
}

template <typename DataType>
void Table<DataType>::erase( int key1, int key2 ) {
	
	assert( key1 >= 0 && key2 >= 0 );
	
	bool found = false;
	NodePointer delNode;
	findPtr( key1, key2, found, delNode );
	if(found) {
		int index = hash(key1);
		NodePointer firstNode = table[index];
		table[index] = firstNode->next;
		delNode->data->key1 = firstNode->data->key1;
		delNode->data->key2 = firstNode->data->key2;
		delNode->data->data = firstNode->data->data;
		delete firstNode;
		used--;
	} else {
		cerr << "Your entry is not found.";
	}
}

template <typename DataType>
void Table<DataType>::print() const {
	cout << "The hash table is: " << endl;
	cout << setw(5) << "Index  Key/Data" << endl;
	for( int i=0; i < CAPACITY; i++ ) {
		cout << setw(5) << i << ":" << endl;
		NodePointer dispPtr = table[i];
		while(dispPtr != NULL) {
			cout << "k1: " << dispPtr->data->key1 << "/";
			cout << "k2: " << dispPtr->data->key2 << "/";
			cout << dispPtr->data << endl;
			dispPtr = dispPtr->next;
		}
		cout << endl;
	}
	cout << endl;
}

template <typename DataType>
void Table<DataType>::printRecord(int key1, int key2) const {
	int index = hash(key1);
	NodePointer dispPtr = table[index];
	while(dispPtr != NULL) {
		if(dispPtr->data->key2 == key2) {
			break;
		}
		dispPtr = dispPtr->next;
	}
	dispPtr->data->data->display(cout);
}
#endif
