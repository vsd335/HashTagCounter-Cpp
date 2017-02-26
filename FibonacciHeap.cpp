/*
 * PROBLEM STATEMENT
 * You are required to implement a system to find the n most popular hashtags 
 * appeared on social media such as Facebook or Twitter. For the scope of this 
 * project hashtags will be given from an input file. 

 * Basic idea for the implementation is to use a max priority structure to find 
 * out the most popular hashtags.

 * You must use following structures for the implementation.
 * 1. Max Fibonacci heap: use to keep track of the frequencies of hashtags.
 * 2. Hash table: Key for the hash table is hashtag and value is pointer to the 
 * corresponding node in the Fibonacci heap.

 * You can assume there will be a large number of hashtags appears in the stream 
 * and you need to perform increase key operation many times. Max Fibonacci heap 
 * is required because it has better theoretical bounds for increase key operation
 */
 
/* Author : Vinayak Deshpande
 * UFID   : 4102 9538
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include "hashtagcounter.h"

using namespace std;

// Hash table(map)  for all the nodes to be inserted into the heap
unordered_map<string, HeapEntry*> hm;

int main(int argc, char *argv[]) {
  
  if(argc < 2) {
    
    cout << "Specify the input file containing hashtags" << endl;
    cout << "Usage : ./hashtagcounter <filename>" << endl;
    return 0;
    
  }
  
  
  // The Input File containing hash tags.
  ifstream inFile;
  inFile.open(argv[1]);
  
  if(!inFile.is_open()) {
    
    cout << "Check whether the inpue file exists or not" << endl;
    return 0;
  }
  
  //The Output File containing top most n hash tags
  ofstream outFile;
  outFile.open("output_file.txt");
  
  // This will read one hash tag at a time
  while(!inFile.eof()) {

    string readHashTag;
    getline(inFile, readHashTag);
    char first = readHashTag.at(0);       
    hashtagcounter heap;  // Initialize hashtagcounter class     

    // To Separate hash tags entries from queries
    if(first == '#' ) {						// These are hash tags
   
	int hashTagCount=0;
	string hashTag;
	hashTag = readHashTag.substr(1, readHashTag.find(" ")-1);
	hashTagCount = atoi(readHashTag.substr(readHashTag.find(" ")+1, readHashTag.size()-readHashTag.find(" ")-1).c_str());		   
	if (hm.find(hashTag) == hm.end()) {
		// hashTag is not present in HashMap so do InsertKey()
		HeapEntry *node;
		node = heap.HeapInit(hashTagCount, hashTag);
		hm[hashTag] = node;
		heap.InsertNode(node);
				
	}
	else {
		// hashTag is present in HashMap so do IncreaseKey()		
 	        heap.IncreaseKey(hm[hashTag],hashTagCount);
				
		
	}     
	
    }
    
    else if (first == 's' || first == 'S') {			// Stop here
   	
	inFile.close();
	outFile.close();   
   	exit(0);
	
    }
    
   else {							// These are removeMax queries 

	int query = stoi(readHashTag);	   
		
	HeapEntry *node[query];
	string key[query];
	int value[query];
	// Remove Max and Pairwise Combine operations
	for (int i=0; i<query; i++) {

	    node[i] = heap.RemoveMax();
	    key[i] = node[i]->hHashTag;		
            value[i] = node[i]->hElem;

	    // Write to output file
	    outFile << key[i];
	    if(i < query-1)
	        cout << ",";
		
	}
	
	// Insert the above removed nodes back into the root of Fibonacci heap
	for(int j=0; j<query; j++) {
	    node[j] = heap.HeapInit(value[j], key[j]);
	    hm[key[j]] = node[j]; 
  	}
   }  
      
  } 

  inFile.close();
  outFile.close();
  return 0;

}
