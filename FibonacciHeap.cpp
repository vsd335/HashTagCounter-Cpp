/**
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
 **/
 
/** Author : Vinayak Deshpande
  * UFID   : 4102 9538
  **/

#include <iostream>
#include <string>
#include <cstdlib>
#include <unordered_map>
#include <cmath>
#include <fstream>
#include "hashtagcounter.h"

using namespace std;

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
  
  // hashtagcounter class object to access methods
 // hashtagcounter node = new hashtagcounter();
  
  //The Output File containing top most n hash tags
  ofstream outFile;
  outFile.open("output_file.txt");
  
  // This will read one hash tag at a time
  string readHashTag;
  int hashTagCount;
  char first;
  while(!inFile.eof()) {
	
    getline(inFile, readHashTag);
    first = readHashTag(0);
    cout << first;
    //cout << readHashTag << endl;
	
    

    // To Separate hash tags entries from queries
   /* if() {							// These are hash tags
      
      
    }
    
    else if () {						// Stop here
      
      
    }
    
    else {							// These are removeMax queries 
      
      
      
  }

  inFile.close();
  outFile.close();
  return 0;

}
