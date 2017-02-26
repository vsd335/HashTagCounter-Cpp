all:
	g++ FibonacciHeap.cpp hashtagcounter.cpp  -std=gnu++0x -o hashtagcounter
	#g++ FibonacciHeap.cpp hashtagcounter.cpp  -std=c++11 -o hashtagcounter


clean:
	rm -f *.o hashtagcounter


