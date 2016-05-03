#include <iomanip>
#include <cstdlib>
#include "Call.h"

using namespace std;

#ifndef CLIENT_H
#define CLIENT_H

template <typename DataType>
class Client {
	private:
		/***** Node class *****/
		class BinNode {
			public:
				DataType data;
				BinNode * left;
				BinNode * right;

				// BinNode constructors
				// Default -- data part is default DataType value; both links are null.
				BinNode()
					: left(0), right(0) {
				}

				// Explicit Value -- data part contains item; both links are null.
				BinNode(DataType item)
					: data(item), left(0), right(0) {
				}

		};// end of class BinNode declaration

		typedef BinNode * BinNodePointer;

		/***** Private Function Members *****/
		void search2(const DataType & item, bool & found,
		             BinNodePointer & locptr, BinNodePointer & parent) const;
		/*------------------------------------------------------------------------
		  Locate a node containing item and its parent.

		  Precondition:  None.
		  Postcondition: locptr points to node containing item or is null if
		      not found, and parent points to its parent.#include <iostream>
		------------------------------------------------------------------------*/

		void inorderAux(ostream & out,
		                BinNodePointer subtreePtr) const;
		/*------------------------------------------------------------------------
		  Inorder traversal auxiliary function.

		  Precondition:  ostream out is open; subtreePtr points to a subtree
		      of this Client.
		  Postcondition: Subtree with root pointed to by subtreePtr has been
		      output to out.
		------------------------------------------------------------------------*/

		void graphAux(ostream & out, int indent, BinNodePointer subtreeRoot) const;			
		/*------------------------------------------------------------------------
		  Graph auxiliary function.

		  Precondition:  ostream out is open; subtreePtr points to a subtree
		      of this Client.
		  Postcondition: Graphical representation of subtree with root pointed
		      to by subtreePtr has been output to out, indented indent spaces.
		------------------------------------------------------------------------*/
		
		int leafCount2(BinNodePointer subtreeRoot) const;
		/*------------------------------------------------------------------------
		Recursive function to return the number of leaves in a Client

		Precondition: subtreeRoot points to a subtree of this Client.
		Postcondition: Returns the number of leaves in the Client.
		------------------------------------------------------------------------*/
		
		int height2(BinNodePointer subtreeRoot) const;
		/*------------------------------------------------------------------------
		Recursive function which returns the height of a Client.

		Precondition: subtreeRoot points to a subtree of this Client.
		Postcondition: The height of the Client is returned as an int.
		------------------------------------------------------------------------*/

		/***** Data Members *****/
		BinNodePointer myRoot;

	public:
		/***** Function Members *****/
		Client();
		/*------------------------------------------------------------------------
		  Construct a Client object.

		  Precondition:  None.
		  Postcondition: An empty Client has been constructed.
		 -----------------------------------------------------------------------*/

		bool empty() const;
		/*------------------------------------------------------------------------
		  Check if Client is empty.

		  Precondition:  None.
		  Postcondition: Returns true if Client is empty and false otherwise.
		 -----------------------------------------------------------------------*/

		bool search(const DataType & item) const;
		/*------------------------------------------------------------------------
		  Search the Client for item.

		  Precondition:  None.
		  Postcondition: Returns true if item found, and false otherwise.
		 -----------------------------------------------------------------------*/

		void insert(DataType & item);
		/*------------------------------------------------------------------------
		  Insert item into Client.

		  Precondition:  None.
		  Postcondition: Client has been modified with item inserted at proper
		      position (if not present) to maintain Client property. Prints
		      error message if item already exists.
		------------------------------------------------------------------------*/

		void remove(const DataType & item);
		/*------------------------------------------------------------------------
		Remove item from Client.

		Precondition:  None.
		Postcondition: Client has been modified with item removed (if present);
		    Client property is maintained. Prints error message if item does
		    not exist.
		Note: remove uses auxiliary function search2() to locate the node
		      containing item and its parent.
		------------------------------------------------------------------------*/

		void inorder(ostream & out) const;
		/*------------------------------------------------------------------------
		Inorder traversal of Client.

		Precondition:  ostream out is open.
		Postcondition: Client has been inorder traversed and values in nodes
		    have been output to out.
		Note: inorder uses private auxiliary function inorderAux().
		------------------------------------------------------------------------*/

		void graph(ostream & out) const;
		/*------------------------------------------------------------------------
		Graphic output of Client.

		Precondition:  ostream out is open.
		Postcondition: Graphical representation of Client has been output to out.
		Note: graph() uses private auxiliary function graphAux().
		------------------------------------------------------------------------*/
		
		int height() const;
		/*------------------------------------------------------------------------
		Returns the an int value which represents the height of a Client.

		Precondition:  None.
		Postcondition: The height of the Client is returned as an int.
		Note: height() uses private auxiliary function height2().
		------------------------------------------------------------------------*/	
			
		int leafCount() const;
		/*------------------------------------------------------------------------
		Returns the an int value which represents the number of leaves in a Client.

		Precondition:  None.
		Postcondition: The number of leaves in the Client is returned.
		Note: leafCount() uses private auxiliary function leafCount2().
		------------------------------------------------------------------------*/
		
		/***** Assignment *****/
		Client & operator< (const Call & rightHandSide);
		/*------------------------------------------------------------------------
		Assignment Operator 
		Precondition:  rightHandSide is the stack to be assigned and is 
		received as a const reference parameter.
		Postcondition: The current stack becomes a copy of rightHandSide
		and a reference to it is returned.
		------------------------------------------------------------------------*/
		
}; // end of class template declaration

//--- Definition of output operator
/*template <typename DataType>
ostream & Client<DataType>::operator<< (ostream & out, const Client<DataType> & aClient) {
	aClient.inorder(out);
	return out;
}*/

//--- Definition of constructor
template <typename DataType>
inline Client<DataType>::Client()
	: myRoot(0) {
}

//--- Definition of empty()
template <typename DataType>
inline bool Client<DataType>::empty() const {
	return myRoot == 0;
}

//--- Definition of search()
template <typename DataType>
bool Client<DataType>::search(const DataType & item) const {
	BinNodePointer locptr = myRoot;
	bool found = false;
	while (!found && locptr != 0) {
		if (item < locptr->data)       // descend left
			locptr = locptr->left;
		else if (locptr->data < item)  // descend right
			locptr = locptr->right;
		else                           // item found
			found = true;
	}
	return found;
}

//--- Definition of insert()
template <typename DataType>
inline void Client<DataType>::insert( DataType & item) {
	BinNodePointer
	locptr = myRoot,   // search pointer
	parent = 0;        // pointer to parent of current node
	bool found = false;     // indicates if item already in Client
	//cerr << "enter insert";
	while (!found && locptr != 0) {
		//cerr << "inside while";
		parent = locptr;
		if (item < locptr->data)       // descend left
			locptr = locptr->left;
		else if (locptr->data < item)  // descend right
			locptr = locptr->right;
		else                           // item found
			found = true;
	}
	if (!found) {
		// construct node containing item
		locptr = new BinNode(item);
		if (parent == 0)               // empty tree
			myRoot = locptr;
		else if (item < parent->data )  // insert to left of parent
			parent->left = locptr;
		else                           // insert to right of parent
			parent->right = locptr;
	} else
		cerr << "item already in the tree\n";
}

//--- Definition of remove()
template <typename DataType>
void Client<DataType>::remove(const DataType & item) {
	bool found;                      // signals if item is found
	BinNodePointer
	x,                            // points to node to be deleted
	parent;                       //    "    " parent of x and xSucc
	search2(item, found, x, parent);

	if (!found) {
		cerr << "item not in the Client\n";
		return;
	}
	//else
	if (x->left != 0 && x->right != 0) {
		// node has 2 children
		// Find x's inorder successor and its parent
		BinNodePointer xSucc = x->right;
		parent = x;
		while (xSucc->left != 0) {     // descend left
			parent = xSucc;
			xSucc = xSucc->left;
		}

		// Move contents of xSucc to x and change x
		// to point to successor, which will be removed.
		x->data = xSucc->data;
		x = xSucc;
	} // end if node has 2 children

	// Now proceed with case where node has 0 or 2 child
	BinNodePointer
	subtree = x->left;             // pointer to a subtree of x
	if (subtree == 0)
		subtree = x->right;
	if (parent == 0)                  // root being removed
		myRoot = subtree;
	else if (parent->left == x)       // left child of parent
		parent->left = subtree;
	else                              // right child of parent
		parent->right = subtree;
	delete x;
}

//--- Definition of inorder()
template <typename DataType>
inline void Client<DataType>::inorder(ostream & out) const {
	inorderAux(out, myRoot);
}

//--- Definition of graph()
template <typename DataType>
inline void Client<DataType>::graph(ostream & out) const {
	graphAux(out, 0, myRoot);
}

//--- Definition of search2()
template <typename DataType>
void Client<DataType>::search2(const DataType & item, bool & found,
                            BinNodePointer & locptr,
                            BinNodePointer & parent) const {
	locptr = myRoot;
	parent = 0;
	found = false;
	while (!found && locptr != 0) {
		if (item < locptr->data) {     // descend left
			parent = locptr;
			locptr = locptr->left;
		} else if (locptr->data < item) { // descend right
			parent = locptr;
			locptr = locptr->right;
		} else                         // item found
			found = true;
	}
}

//--- Definition of inorderAux()
template <typename DataType>
void Client<DataType>::inorderAux(ostream & out,
                            	BinNodePointer subtreeRoot) const {
	if (subtreeRoot != 0) {
		inorderAux(out, subtreeRoot->left);    // L operation
		out << subtreeRoot->data << "  ";      // V operation
		inorderAux(out, subtreeRoot->right);   // R operation
	}
}

template <typename DataType>
int Client<DataType>::leafCount2(BinNodePointer subtreeRoot) const {
	
	if(subtreeRoot == NULL) {
		return 0;
	}
	
	BinNodePointer leftSubtree = subtreeRoot->left;
	BinNodePointer rightSubtree = subtreeRoot->right;
	
	if((leftSubtree == 0) && (rightSubtree ==  0)) {
		return 1;
	}
	
	return leafCount2(leftSubtree) + leafCount2(rightSubtree);
}

template <typename DataType>
int Client<DataType>::leafCount() const {
	return leafCount2(myRoot);
}

template <typename DataType>
int Client<DataType>::height2(BinNodePointer subtreeRoot) const {
	
	if(subtreeRoot == NULL) {
		return 0;
	}
	
	int leftHeight = height2(subtreeRoot->left);
	int rightHeight = height2(subtreeRoot->right);
	
	if(leftHeight > rightHeight) {
		return 1 + leftHeight;
	} else {
		return 1 + rightHeight;
	}
}

template <typename DataType>
int Client<DataType>::height() const {
	return height2(myRoot);
}


template <typename DataType>
void Client<DataType>::graphAux(ostream & out, int indent,
                             BinNodePointer subtreeRoot) const {
	if (subtreeRoot != 0) {
		graphAux(out, indent + 8, subtreeRoot->right);
		out << setw(indent) << " " << subtreeRoot->data.getCallId() << endl;
		graphAux(out, indent + 8, subtreeRoot->left);
	}
}
/*void Client<DataType>::graphAux(ostream & out, BinNodePointer subtreeRoot,
							int indent) const {
	if (subtreeRoot != 0) {
		if(subtreeRoot->left) {
			graphAux(out, subtreeRoot->left, indent + 8);
		}
		if(subtreeRoot->right) {
			graphAux(out, subtreeRoot->right, indent + 8);
		}
		if(indent) {
			out << setw(indent) << " ";
		}
		cout << subtreeRoot->data.getCallId() << "\n ";
	}
}*/

template <typename DataType>
Client<DataType> & Client<DataType>::operator<(const Call & rightHandSide) {
	//cerr << "entering operator<";
	int lhs = this->data.getCallId();
	int rhs = rightHandSide.getCallId();
	//cerr << "lhs: " << lhs;
	//cerr << "rhs: " << rhs;
	return lhs<rhs;
}

#endif
