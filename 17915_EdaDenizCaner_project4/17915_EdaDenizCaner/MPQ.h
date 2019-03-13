#ifndef MPQ_H
#define MPQ_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class MPQ
{
public:
	
	MPQ( const vector<int> & items);
	~MPQ();


private:
	int elementNum; // Number of elements in heap
	vector<int> heapArray; // The heap array

	void buildHeap( );
	void percolateDown( int hole );
};

#endif