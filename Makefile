all:
	g++ FibonacciHeap.cpp hashtagcounter.cpp  -std=gnu++0x -o hashtagcounter	


clean:
	rm -f *.o hashtagcounter


