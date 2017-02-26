#include <iostream>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include "hashtagcounter.h"

using namespace std;
//using namespace hashtagcounter;

// Set the initial left and right sibling of a new node to itself
HeapEntry* hashtagcounter::HeapInit(int elem, string hHashTag) {
  
  HeapEntry *node = new HeapEntry;
  node->hRightSib = node;
  node->hLeftSib = node; 
  node->hHashTag = hHashTag;
  node->hElem = elem;
 
  return node;  

}

/** Insert() : Insert a new node into the heap **/ 
void hashtagcounter::InsertNode(HeapEntry *newNode) {

	cout << "Inside Insert Node" << endl;

}

/** IncreaseKey() : Increase the value of a node in the heap **/
void hashtagcounter::IncreaseKey(HeapEntry *node, int newVal) {

	cout << "Inside Increase Key" << endl;
	
}

