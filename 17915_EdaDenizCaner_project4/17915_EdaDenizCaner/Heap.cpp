#include "Heap.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

heap::heap()
{
	lastUsed = 0;
}

heap::~heap()
{
	
}

void heap::insert(int yCoord, int label)
{
	heapStruct temp(yCoord, label);
	if(heapVector.empty())
	{
		locationVector.resize(label);
		heapVector.resize(1);
		heapVector.push_back(temp);		
		heapVector[0].label = 0;
		heapVector[0].yCoord = 0;
		lastUsed = 1;
		locationVector.push_back(1);
	}
	else
	{
		heapVector.push_back(temp);
		lastUsed++;
		if(locationVector.size() <= label)
		{
			locationVector.resize(label);
			locationVector.push_back(lastUsed);
			percolateUp();
		}
		else
		{
			locationVector[label] = lastUsed;		
			percolateUp();
		}
		
	}


}

int heap::remove(int label)
{
	int num = heapVector[locationVector[label]].yCoord;
	if(locationVector[label] == lastUsed) // we try to delete the last element
	{
		locationVector[label] = 0;
		heapVector.pop_back();
		lastUsed--;
	}
	else
	{
		int temp = heapVector[locationVector[label]].yCoord;
		int temp2 = heapVector[locationVector[label]].label;
		heapVector[locationVector[label]].yCoord = heapVector[lastUsed].yCoord;
		heapVector[locationVector[label]].label = heapVector[lastUsed].label;
		heapVector[lastUsed].yCoord = temp;
		heapVector[lastUsed].label = temp2;
		heapVector.pop_back();
		lastUsed--; // not sure of it
		percolateDown(locationVector[label]);
		locationVector[label] = 0;
		updateLocationVector();
	}
	return num;
}

int heap::getMax()
{
	if(this->isEmpty() == true)
	{
		cout << "Heap is currently empty." << endl;
		return -1;
	}
	else
	{
		return heapVector[1].yCoord;
	}
}

bool heap::isEmpty()
{
	if(lastUsed == 0)
	{
		return true;
	}
	return false;
}

void heap::percolateUp()
{
	int temp = lastUsed;
	while(heapVector[temp].yCoord > heapVector[temp/2].yCoord && temp > 1)
	{
		int temp2 = locationVector[heapVector[temp].label] ;
		locationVector[heapVector[temp].label] = locationVector[heapVector[temp/2].label] ;
		locationVector[heapVector[temp/2].label] = temp2;

		heapStruct eda(heapVector[temp/2].yCoord, heapVector[temp/2].label);
		heapVector[temp/2].yCoord = heapVector[temp].yCoord;
		heapVector[temp/2].label = heapVector[temp].label;
		heapVector[temp].yCoord = eda.yCoord;
		heapVector[temp].label = eda.label;
		temp = temp/2;
	}
}
	
void heap::percolateDown(int index)
{
	bool finished = false;
	int childIndex = (index*2);
	while(childIndex <=lastUsed && finished == false)
	{
		if(  childIndex <= lastUsed && heapVector[index].yCoord <= heapVector[childIndex].yCoord ) // checking the left child 
		{
			int temp = heapVector[index].yCoord;
			int temp2 = heapVector[index].label;
			heapVector[index].yCoord = heapVector[childIndex].yCoord;
			heapVector[index].label = heapVector[childIndex].label;
			heapVector[childIndex].yCoord = temp;
			heapVector[childIndex].label = temp2;

			index = childIndex;
			childIndex = (index*2);
		}
		else if( (childIndex+1) <= lastUsed && heapVector[index].yCoord <= heapVector[childIndex+1].yCoord) // checking the right child
		{
			childIndex++;
			int temp = heapVector[index].yCoord;
			int temp2 = heapVector[index].label;
			heapVector[index].yCoord = heapVector[childIndex].yCoord;
			heapVector[index].label = heapVector[childIndex].label;
			heapVector[childIndex].yCoord = temp;
			heapVector[childIndex].label = temp2;

			index = childIndex;
			childIndex = (index*2);
		}
		else
		{
			finished = true;
		}
	}
}

void heap::updateLocationVector()
{
	for(unsigned int i = 1; i < heapVector.size(); i++)
	{
		int label = heapVector[i].label;
		locationVector[label] =  i;
	}
}

void heap::printLocationVector() // for debugging purposes
{
	for(unsigned int i = 0; i < locationVector.size(); i++)
	{
		if(locationVector[i] != 0)
			cout << locationVector[i] << endl;
	}
}

void heap::printHeapVector() // for debugging purposes
{
	for(unsigned int i = 1; i < heapVector.size(); i++)
	{
		cout << "Label is " << heapVector[i].label << " and height is " << heapVector[i].yCoord <<  endl;
	}
}

int heap::findYCoord(int label)
{
	return heapVector[locationVector[label]].yCoord;
}