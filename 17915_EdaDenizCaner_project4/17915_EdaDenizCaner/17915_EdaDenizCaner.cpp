#include <iostream>
#include <vector>
#include "Heap.h"
#include <string>
#include <fstream>
#include <sstream>

using namespace std;

// Eda Deniz Caner - 17915

struct xVectorNode{
	int xCoordinate;
	int buildingNum;
	char side;
};

struct yVectorNode{
	int yCoordinate;
	int buildingNumber;
};

void debug()
{
	heap eda;
	eda.insert(8,63);
	eda.insert(7,98);
	eda.insert(9,22);
	eda.insert(10,17);
	eda.insert(15,53);
	eda.printHeapVector();
	eda.printLocationVector();
	cout << "Height is: " <<	eda.findYCoord(17)	<< endl;
	cout << "Height is: " <<	eda.findYCoord(22)	<< endl;
	eda.remove(63);
	cout << "Height is: " <<	eda.findYCoord(98)	<< endl;
	eda.printHeapVector();
	eda.printLocationVector();
	eda.remove(98);
	eda.printHeapVector();
	eda.printLocationVector();
	eda.remove(22);
	eda.printHeapVector();
	eda.printLocationVector();
	eda.remove(17);
	eda.printHeapVector();
	eda.printLocationVector();
	eda.remove(53);
	eda.printHeapVector();
	eda.printLocationVector();
}

void printX(vector<xVectorNode> xVector) 
{
	unsigned int i = 0;
	while(i < xVector.size())
	{
		cout << xVector[i].xCoordinate << " " << xVector[i].buildingNum << " " << xVector[i].side << endl;;
		i++;
	}
}

void printY(vector<yVectorNode> yVector)
{
	unsigned int i = 0;
	while(i < yVector.size())
	{
		cout << yVector[i].yCoordinate << " " << yVector[i].buildingNumber << endl;;
		i++;
	}
}

void sort(vector<xVectorNode> & xVector) // sort the xVector
{
	unsigned int j;
	for(unsigned int p = 1; p < xVector.size(); p++)
	{
		xVectorNode temp;
		temp.buildingNum= xVector[p].buildingNum;
		temp.xCoordinate = xVector[p].xCoordinate;
		temp.side = xVector[p].side;
		for(j = p; j > 0 && temp.xCoordinate < xVector[j-1].xCoordinate; j--)
		{
			xVector[j].xCoordinate = xVector[j-1].xCoordinate;
			xVector[j].side = xVector[j-1].side;
			xVector[j].buildingNum = xVector[j-1].buildingNum;
		}
		xVector[j].buildingNum = temp.buildingNum;
		xVector[j].side = temp.side;
		xVector[j].xCoordinate = temp.xCoordinate;
	}

}

int main()
{
	int numOfBuildings = 0;
	fstream inFile;
	string FileName = "input.txt";
	inFile.open(FileName.c_str()); // Tries to open the file.
	while(inFile.fail()) // Enters the loop if the file can not be opened.
	{
		cout << "File cannot be opened." << endl; //Displays a message
		inFile.open(FileName.c_str()); // Tries to open the file.
	}

	string line;
	getline(inFile, line);
	istringstream strStream(line);
	strStream >> numOfBuildings;
	vector<xVectorNode> xVector(numOfBuildings*2);
	vector<yVectorNode> yVector(numOfBuildings);
	int i = 0, j = 0;
	while (getline(inFile, line)) // reads the file line by line.
	{
		istringstream strStream(line);
		strStream >> xVector[i].xCoordinate >> yVector[j].yCoordinate >> xVector[i+1].xCoordinate ;
		xVector[i].buildingNum = (j+1);
		xVector[i].side = 'L';
		xVector[i+1].buildingNum = (j+1);
		xVector[i+1].side = 'R';
		yVector[j].buildingNumber = (j+1);
		i = i+2;
		j++;
	}

	sort(xVector);
	//printX(xVector);
	//printY(yVector);

	heap myHeap;
	int currentMax = 0;

	if(xVector[0].xCoordinate > 0)
	{
		cout << "0 0" << endl;
	}

	for(unsigned int i = 0; i < xVector.size(); i++)
	{
		if(xVector[i].side == 'L')
		{
			myHeap.insert(yVector[xVector[i].buildingNum-1].yCoordinate,xVector[i].buildingNum );
			if(currentMax != myHeap.getMax())
			{
				cout << xVector[i].xCoordinate << " " << yVector[xVector[i].buildingNum-1].yCoordinate << endl;
				currentMax = myHeap.getMax();
			}
		}
		else if (xVector[i].side == 'R')
		{
			myHeap.remove(xVector[i].buildingNum);
			if(myHeap.isEmpty())
			{
				cout << xVector[i].xCoordinate << " 0" << endl;
			}
			else if(currentMax != myHeap.getMax())
			{
				cout << xVector[i].xCoordinate << " " << myHeap.getMax() << endl ;
				currentMax = myHeap.getMax();
			}
		}
	}

	cin.get();
	cin.ignore();
	return 0;
}