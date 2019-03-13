#ifndef HEAP_H
#define HEAP_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct heapStruct{
	int yCoord;
	int label;
	heapStruct::heapStruct()
	{
		int label = 0;
		int yCoord = 0;
	}

	heapStruct::heapStruct(int a, int b)
		:yCoord(a), label(b){}
};

class heap{

private:
	vector <heapStruct> heapVector;
	vector <int> locationVector;
	int lastUsed;
	void percolateUp();
	void percolateDown(int index);
	void updateLocationVector();

public:
	heap();
	~heap();
	void insert(int yCoord, int label);
	int remove(int label);
	int getMax();
	int findYCoord(int label);
	bool isEmpty();
	void printLocationVector(); // for debugging purposes
	void printHeapVector(); // for debugging purposes
};


#endif