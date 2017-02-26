#include <iostream>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include "hashtagcounter.h"

#define sc hashtagcounter

using namespace std;


/** To keep track of degree of nodes to combine in pairs **/
unordered_map<int, HeapEntry*> degreeMap;

/** Constructor to set intial heap pointer (hMax) **/
sc::hashtagcounter() {
	
	hMax = NULL;		
}

/** Set the initial left and right sibling of a new node to itself **/
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
	cout << "Entering InsertNode " <<endl;

	// For the very first node
	if(hMax == NULL) { 
	 
	    hMax = newNode;
	    hMax->hParent = NULL;
	    hMax->hLeftSib = hMax;
	    hMax->hRightSib = hMax;
	    hMax->hChildCut = false;		
	}
	else {
	   
	    hMax = InsertIntoRootList(hMax, newNode);		
	}

	// Always ensure that, hMax is pointing to the appropriate max node in the heap
	HeapEntry *maxNodeTemp = hMax->hLeftSib;
    	HeapEntry *currNode = hMax;
	do {
		if(currNode->hRightSib->hElem > hMax->hElem) {
					
			hMax = currNode->hRightSib;
			
		}
		currNode= currNode->hRightSib;
	}while(currNode != maxNodeTemp);	
	cout << "Exiting InsertNode " <<endl;

	return;
}

/** IncreaseKey() : Increase the value of a node in the heap **/
void sc::IncreaseKey(HeapEntry *node, int newVal) {
	cout << "Entering IncreaseKey " <<endl;

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
	cout << "Exiting IncreaseKey " <<endl;

}


/** RemoveMax() : Remove the max node from the heap **/
HeapEntry* sc::RemoveMax() {
	cout << "Entering RemoveMax " <<endl;
	HeapEntry *cacheMaxNode = hMax;			// Need to return this to calling function  

	if(hMax->hRightSib == hMax) {			// For A single node at root
	
		hMax = NULL;				// Set the max pointer to null & the heap becomes empty
		AddChildren2Root(cacheMaxNode);		// Add the children (if any) of max node to root list
	
	}
	else {						// For more than one node at root

		// Max Nodes Siblings must be joined
		hMax->hRightSib->hLeftSib = hMax->hLeftSib;
		hMax->hLeftSib->hRightSib = hMax->hRightSib;	

		HeapEntry *rightChild = cacheMaxNode->hRightSib;
		
		hMax = NULL;				// Set the max pointer to null, may be not required (CHECK later)
		hMax = rightChild;			
		
		AddChildren2Root(cacheMaxNode);		// Insert the children of Max node into the root of the heap

		HeapEntry *currPointer = hMax;

		// This loop is to find out the new max node
		do {

			if(currPointer->hRightSib->hElem > hMax->hElem) {
				
				hMax = currPointer->hRightSib;
			}
			
			currPointer = currPointer->hRightSib;
		}
		while(currPointer != rightChild);
	
	}

	/** Pairwise combine starts here **/    	
	/** This function will combine nodes with same degree until no two nodes in the root have same degree **/
	RecursiveMerge(hMax);
	
	degreeMap.clear();	
	cacheMaxNode->hLeftSib = cacheMaxNode;
	cacheMaxNode->hRightSib = cacheMaxNode;
	cacheMaxNode->hParent = NULL;
	cacheMaxNode->hChild = NULL;
	cacheMaxNode->hDegree = 0;
	cout << "Exiting RemoveMax " <<endl;

	// Return the max node to main function to write to the output file
	return cacheMaxNode;
}


/** This method adds the children of a removed node to root node list of the heap **/
void sc::AddChildren2Root(HeapEntry *removedChild) {
	cout << "Entering AddChildren2Root " <<endl;
	HeapEntry *tempNode = removedChild->hChild;
	
	if(removedChild->hDegree == 0) 		// Max node has no children		
		return;	
		
	else if(removedChild->hDegree == 1) 	// Max node has only one child		
		InsertNode(tempNode);		// Insert the only child to root of heap

	else {					// Max node has more than one child
		cout << "Inside else with degree: " << removedChild->hDegree << endl;
		for(int i=0; i<removedChild->hDegree; i++) {
			cout << "Inside for" << endl;
			HeapEntry *currChild = removedChild->hChild;
			cout << "after first statement" << endl;			
			removedChild->hChild = currChild->hRightSib;
			currChild->hRightSib = currChild;
			currChild->hLeftSib = currChild;
			InsertNode(currChild);					

		}			
	}

	removedChild->hChild = NULL;
	cout << "Exiting AddChildren2Root " <<endl;
	return;
}


/** This method recursively combines nodes until no two nodes have same degree **/
void sc::RecursiveMerge(HeapEntry *pairNode1) {

	cout << "Entered Recursive Merge " <<endl;
	do {
		int degree = pairNode1->hDegree;		// Degree of the node
		
		if(degreeMap.find(degree) != degreeMap.end()) { // Same degree node is present in hash map
			
			if(pairNode1 != degreeMap[degree]) {

				HeapEntry *pairNode2 = degreeMap[degree];

				// Remove same degree node entry from degree map 
				degreeMap.erase(degree);				
					
				// Returns the parent node (Node with larger count value)
				HeapEntry *parentNode = CombineThePairs(pairNode1, pairNode2);
				pairNode1 = parentNode;
				RecursiveMerge(pairNode1);
				return;
				
			}
						
		} 
		else
			degreeMap[degree] = pairNode1;		// Update degree table with this degree and node	

		pairNode1 = pairNode1->hRightSib;
	}
	while(pairNode1 != hMax);
	cout << "Exiting Recursive Merge " <<endl;
	return;
}


/** This method combines two nodes such that, one of the nodes becomes child of another node **/
HeapEntry* sc::CombineThePairs(HeapEntry *pairNode1, HeapEntry *pairNode2) {
	cout << "Entering Combine the Pairs " <<endl;

	HeapEntry *parentNode, *childNode;
	
	// This is to handle similar count hashTags, 
	// need to make sure, the max node always stays at the root
	if(pairNode1 == hMax || pairNode2 == hMax) {

		if(pairNode1 == hMax) {
			
			pairNode2->hLeftSib->hRightSib = pairNode2->hRightSib;
			pairNode2->hRightSib->hLeftSib = pairNode2->hLeftSib;								

			parentNode = pairNode1;
			childNode = pairNode2;			
		}
		else {

						pairNode1->hLeftSib->hRightSib = pairNode1->hRightSib;
                        pairNode1->hRightSib->hLeftSib = pairNode1->hLeftSib;                                               

                        parentNode = pairNode2;
                        childNode = pairNode1;
        }
	}
	else if(pairNode1->hElem > pairNode2->hElem) {			// Need to remove pairNode2 from root
		
        pairNode2->hLeftSib->hRightSib = pairNode2->hRightSib;
        pairNode2->hRightSib->hLeftSib = pairNode2->hLeftSib;
		
		parentNode = pairNode1;
        childNode = pairNode2;
		
	}
	else {								// Need to remove pairNode1 from root

		
        pairNode1->hLeftSib->hRightSib = pairNode1->hRightSib;
		pairNode1->hRightSib->hLeftSib = pairNode1->hLeftSib;
        
        parentNode = pairNode2;
        childNode = pairNode1;		

	}
	
	if(parentNode->hDegree == 0) {					// If the parent has no previous children, Insert new child

		parentNode->hChild = childNode;
		childNode->hParent = parentNode;

		childNode->hRightSib = childNode;
                childNode->hLeftSib = childNode;
			
	}
	else {
		
		childNode->hRightSib = childNode;
                childNode->hLeftSib = childNode;
		
		HeapEntry *defaultChild = parentNode->hChild;		// Accessing the already present child node
		HeapEntry *valNext = defaultChild->hRightSib;		// Store this since we are going to overwrite it.
		defaultChild->hRightSib = childNode;
		defaultChild->hRightSib->hLeftSib = defaultChild;
		childNode->hRightSib = valNext;
		childNode->hRightSib->hLeftSib = childNode;
		//parentNode->hChild = childNode;		// May be not necessary!!! remove and see if it is OKAY
		childNode->hParent = parentNode;
	}
	
	parentNode->hDegree++;				// Increase the degree of parent node as we just inserted a new child
	cout << "Exiting Comnine the pairs " <<endl;

	return parentNode;
}


/** Merge new node with the List of nodes already present in the heap **/
HeapEntry* sc::InsertIntoRootList(HeapEntry *oldNode, HeapEntry *newNode) {
	cout << "Entering InsertIntoRootList " <<endl;

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
	cout << "Exiting InsertIntoRootList " <<endl;
}


/** Separates the Child node from its parent node, as the key of Child is larger than its Parent **/
void sc::NodeCut(HeapEntry *childNode, HeapEntry *parentNode) {
	cout << "Entering NodeCut " <<endl;
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

		parentNode->hChild = NULL;
	}


	childNode->hRightSib = childNode->hLeftSib = childNode;
	childNode->hChildCut = false;		// ChildCut is set to false 
	parentNode->hDegree-- ;			// Decrease the degree of the parent node
	InsertNode(childNode);			// Remove the node and insert into the root list	
	cout << "Exiting NodeCut " <<endl;
	return;
	
}
 

/** Inserts the Separated Child into the root node List **/
void sc::NodeCascade(HeapEntry *parentNode) {
	cout << "Entering NodeCascade " <<endl;
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
	cout << "Exiting NodeCascade " <<endl;
	return;
}
