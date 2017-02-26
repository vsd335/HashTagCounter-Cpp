#include <iostream>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include "hashtagcounter.h"

#define sc hashtagcounter

using namespace std;

// Set the initial left and right sibling of a new node to itself
HeapEntry* sc::HeapInit(int elem, string hHashTag) {
  
  HeapEntry *node = new HeapEntry;
  node->hRightSib = node;
  node->hLeftSib = node; 
  node->hHashTag = hHashTag;
  node->hElem = elem;
 
  return node;  

}

/** Insert() : Insert a new node into the heap **/ 
void sc::InsertNode(HeapEntry *newNode) {
	 
	cout << "InsertNode()" << endl;
	// For the very first node
	if(hMax == NULL) { 
	    
	    hMax = newNode;
	    hMax->hParent = NULL;
	    hMax->hLeftSib = hMax;
	    hMax->hRightSib = hMax;
	    hMax->hChildCut = false;

	}
	else
		
	    hMax = InsertIntoRootList(hMax, newNode);		

	return;
}

/** IncreaseKey() : Increase the value of a node in the heap **/
void sc::IncreaseKey(HeapEntry *node, int newVal) {

	node->hElem = node->hElem + newVal;		// Change the value at the node to the new larger value	
	HeapEntry *cacheParent = node->hParent;		// The Parent of the node is stored
		
	// Check to see if the child node's count value is greater than its parent
	if(cacheParent != NULL && node->hElem > cacheParent->hElem) {
	    cout << "if" << endl;	
	    // Cut() & CascadeCut() : Cut the node from its parent node and cascade into root node
	    NodeCut(node, cacheParent);
	    NodeCascade(cacheParent);

	}
	
	if(node->hElem > hMax->hElem)
	    hMax = node;				// New node with larger count value becomes hMax		

}


HeapEntry* sc::RemoveMax() {

	cout << "Inside Remove Max" << endl;


}


void sc::AddChildren2Root(HeapEntry *firstChild) {


}


void sc::RecursiveMerge(HeapEntry *pairNode1) {


}


HeapEntry* sc::CombineThePairs(HeapEntry *pairNode1, HeapEntry *pairNode2) {


}


/** Merge new node with the List of nodes already present in the heap **/
HeapEntry* sc::InsertIntoRootList(HeapEntry *oldNode, HeapEntry *newNode) {
	
	if(oldNode == NULL && newNode == NULL) {		// Both nodes are null & the resulting node is null.
		return NULL;
	}
	
	else if(oldNode != NULL && newNode == NULL) {		// new node is null, result is old node.
		return oldNode;
	}
	
	else if(oldNode == NULL && newNode != NULL) {		// old node is null, result is new node.
		newNode->hParent = NULL;
		newNode->hChildCut = false;
		if(newNode->hDegree == 0)
			newNode->hChild = NULL;

		return newNode;
	}
	else {
		HeapEntry *valNext = oldNode->hRightSib;		// Store this since we are going to insert new node in between
		oldNode->hRightSib = newNode->hRightSib;
		oldNode->hRightSib->hLeftSib = oldNode;
		newNode->hRightSib = valNext;
		newNode->hRightSib->hLeftSib = newNode;
		newNode->hParent = NULL;
		newNode->hChildCut = false;
		if(newNode->hDegree == 0) 
			newNode->hChild = NULL;

		/* Return a pointer to the Larger node */
		return oldNode->hElem >/*=*/ newNode->hElem? oldNode : newNode;
	}
}


/** Separates the Child node from its parent node, as the key of Child is larger than its Parent **/
void sc::NodeCut(HeapEntry *childNode, HeapEntry *parentNode) {
	
	// Set the parent of the node to removed to null
	childNode->hParent = NULL;

	// When the childNode has siblings, set right sibling as new child of parent
	if(parentNode->hChild == childNode && childNode->hRightSib != childNode) {

		parentNode->hChild = childNode->hRightSib;
		childNode->hLeftSib->hRightSib = childNode->hRightSib;
		childNode->hRightSib->hLeftSib = childNode->hLeftSib;

	}
	else if(parentNode->hChild != childNode && childNode->hRightSib != childNode) {

		childNode->hLeftSib->hRightSib = childNode->hRightSib;
                childNode->hRightSib->hLeftSib = childNode->hLeftSib;

	}
	else { 

		parentNode.hChild = NULL;
	}


	childNode->hRightSib = childNode->hLeftSib = childNode;
	childNode.hChildCut = false;		// ChildCut is set to false 
	parentNode->hDegree-- ;			// Decrease the degree of the parent node
	InsertNode(childNode);			// Remove the node and insert into the root list	
	
	return;
	
}
 

/** Inserts the Separated Child into the root node List **/
void sc::NodeCascade(HeapEntry *parentNode) {
	
	HeapEntry *grandParentNode = parentNode->hParent;	// Store the parent of parentNode
	
	if(grandParentNode != NULL) {

		if(parentNode->hChildCut == false) { 		// If the node has not lost a child before

			parentNode->hChildCut = true;		// Set its childCut to true

		}
		else {
			
			// Cut() & CascadeCut() : Cut the node from its parent node and cascade into root node
			NodeCut(parentNode, grandParentNode);
			NodeCascade(grandParentNode);			

		}
			
	}
	
	return;
}
