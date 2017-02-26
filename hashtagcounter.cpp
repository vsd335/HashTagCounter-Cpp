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

	//cout << "Inside Insert Node" << endl;

}

/** IncreaseKey() : Increase the value of a node in the heap **/
void sc::IncreaseKey(HeapEntry *node, int newVal) {

	//cout << "Inside Increase Key" << endl;
	
}


HeapEntry* sc::RemoveMax() {

	//cout << "Inside Remove Max" << endl;


}


void sc::AddChildren2Root(HeapEntry *firstChild) {


}


void sc::RecursiveMerge(HeapEntry *pairNode1) {


}


HeapEntry* sc::CombineThePairs(HeapEntry *pairNode1, HeapEntry *pairNode2) {


}


HeapEntry* sc::InsertIntoRootList(HeapEntry *oldNode, HeapEntry *newNode) {


}


void sc::NodeCut(HeapEntry *childNode, HeapEntry *parentNode) {


}
 

void sc::NodeCascade(HeapEntry *parentNode) {


}
