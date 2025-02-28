#ifndef HASHTAGCOUNTER_H
#define HASHTAGCOUNTER_H

#include <iostream>
#include <string>

using namespace std;

//This stucture holds the node structure for the Fibonacci heap

struct HeapEntry {
  
  int hDegree=0;			// Number of children in the node
  string hHashTag;		// Holds the hash tag
  HeapEntry *hLeftSib;		// Left Sibling element 
  HeapEntry *hRightSib;		// Right Sibling element
  HeapEntry *hParent=NULL;	// Parent in the fibonacci heap (if any)
  HeapEntry *hChild=NULL;	// Child node (if any)
  bool hChildCut = false;	// Whether a node has lost a child or not
  int hElem;			// Element stored in the node
  
};


class hashtagcounter {
  
    private:
	/** Pointer to the maximum element in the heap. */
	HeapEntry *hMax;
     
    public:
	hashtagcounter();	// Constructor	
	HeapEntry* HeapInit(int elem, string hHashTag);	
	void InsertNode(HeapEntry *newNode);		
	void IncreaseKey(HeapEntry *node, int newVal);	
	HeapEntry *RemoveMax();				
	void AddChildren2Root(HeapEntry *removedChild); 	
	void RecursiveMerge(HeapEntry *pairNode1);	
	HeapEntry *CombineThePairs(HeapEntry *pairNode1, HeapEntry *pairNode2);	
        HeapEntry *InsertIntoRootList(HeapEntry *oldNode, HeapEntry *newNode);
	void NodeCut(HeapEntry *childNode, HeapEntry *parentNode);
	void NodeCascade(HeapEntry *parentNode);
    
};


#endif
