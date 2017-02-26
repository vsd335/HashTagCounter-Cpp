#include <iostream>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include "hashtagcounter.h"

#define sc hashtagcounter

using namespace std;
//using namespace hashtagcounter;

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

	// Always ensure that, hMax is pointing to the appropriate max node in the heap
		

	return;
}

/** IncreaseKey() : Increase the value of a node in the heap **/
void sc::IncreaseKey(HeapEntry *node, int newVal) {

	node->hElem = node->hElem + newVal;		// Change the value at the node to the new larger value

	HeapEntry *cacheParent = node->hParent;		// The Parent of the node is stored
	
	// Check to see if the child node's count value is greater than its parent
	if(cacheParent != NULL && node->hElem > cacheParent->hElem) {
	
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


void sc::NodeCut(HeapEntry *childNode, HeapEntry *parentNode) {


}
 

void sc::NodeCascade(HeapEntry *parentNode) {


}
