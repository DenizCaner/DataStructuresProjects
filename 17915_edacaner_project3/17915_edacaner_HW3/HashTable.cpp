#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "HashTable.h"
#include <fstream>
#include <ostream>

using namespace std;

HashTable::HashTable()
{
	usedCell = 0;
	load = 0;
	probeNum = 0;
}

int HashTable::hash(int key)
{ 
	int index = (key % 311);
	int k = 0;
	probeNum = 0;
	while(myTable[index].status == 1 && k < 310 && myTable[index].value != key)
	{
		k++;
        index++;
		probeNum++;
	}
	return index;
}

void HashTable::insert(int a)
{
	int index = hash(a);
	if(myTable[index].value == a) // failed insert
	{
		cout << myTable[index].value << " already exists" << endl;
		failedInsert[usedCell].numOfProbes = probeNum;
		failedInsert[usedCell].loadFactor = double(usedCell)/311;
	}
	else // succesful insert
	{
		myTable[index].value = a;
		myTable[index].status = 1;
		usedCell++;
		cout << myTable[index].value << " is inserted in " << index << endl;
		successInsert[usedCell].numOfProbes = probeNum;
		successInsert[usedCell].loadFactor = double(usedCell)/311;
	}
}

void HashTable::remove(int a)
{
	int index = hash(a);
	if(myTable[index].value == a) // successfull remove
	{
		myTable[index].status = 2;
		usedCell--;
		cout << myTable[index].value << " is removed" << endl;
		successRemove[usedCell].numOfProbes = probeNum;
		successRemove[usedCell].loadFactor = double(usedCell)/311;
	}
	else // failed remove
	{
		cout << a << " is not found" << endl;
		failedRemove[usedCell].numOfProbes = probeNum;
		failedRemove[usedCell].loadFactor = double(usedCell)/311;
	}
}

bool HashTable::find(int a)
{
	int index = hash(a);
	if(myTable[index].value == a && myTable[index].status == 1) // successful find
	{

		cout << myTable[index].value << " is found" << endl;
		successFind[usedCell].numOfProbes = probeNum;
		successFind[usedCell].loadFactor = double(usedCell)/311;
		return true;
	}

	else //failed find
	{
		cout << a << " is not found" << endl;
		failedFind[usedCell].numOfProbes = probeNum;
		failedFind[usedCell].loadFactor = double(usedCell)/311;
		return false;
	}
}

void HashTable::print()
{
	for(int i = 0; i < 311 ; i ++)
	{
		if(myTable[i].status == 1)
		{
			cout << myTable[i].value << " index no " << i << endl; 
		}
	}
}

bool HashTable::isFull()
{
	if(usedCell == 311)
	{
		return true;
	}
	return false;
}

void HashTable::dataPrint()
{
	string fileName = "eda.csv";
	ofstream out;
	out.open(fileName.c_str());
	out << "For successfull insert" << endl ;
	for(int i = 0; i < 312 ; i++)
	{
		if(successInsert[i].loadFactor == 0 && successInsert[i].numOfProbes == 0 )
		{
		
		}
		else
		{
			out << successInsert[i].loadFactor << " ; " << successInsert[i].numOfProbes << endl ;
		}
	}

	out << "For failed insert" << endl ;
	for(int i = 0; i < 312 ; i++)
	{
		if(failedInsert[i].loadFactor == 0 && failedInsert[i].numOfProbes == 0 )
		{

		}
		else
		{
			out << failedInsert[i].loadFactor << " ; " << failedInsert[i].numOfProbes << endl ;
		}
	}

	out << "For successfull remove" << endl ;
	for(int i = 0; i < 312 ; i++)
	{
		if(successRemove[i].loadFactor == 0 && successRemove[i].numOfProbes == 0 )
		{
		
		}
		else
		{
			out << successRemove[i].loadFactor << " ; " << successRemove[i].numOfProbes << endl ;
		}
	}

	out << "For failed remove" << endl ;
	for(int i = 0; i < 312 ; i++)
	{
		if(failedRemove[i].loadFactor == 0 && failedRemove[i].numOfProbes == 0 )
		{
		
		}
		else
		{
			out << failedRemove[i].loadFactor << " ; " << failedRemove[i].numOfProbes << endl ;
		}
	}


	out << "For successfull find" << endl ;
	for(int i = 0; i < 312 ; i++)
	{
		if(successFind[i].loadFactor == 0 && successFind[i].numOfProbes == 0 )
		{
		 
		}
		else 
		{
			out << successFind[i].loadFactor << " ; " << successFind[i].numOfProbes << endl ;
		}
	}

	out << "For failed find" << endl ;
	for(int i = 0; i < 312 ; i++)
	{
		if(failedFind[i].loadFactor == 0 && failedFind[i].numOfProbes == 0 )
		{
		
		}
		else
		{
			out << failedFind[i].loadFactor << " ; " << failedFind[i].numOfProbes << endl ;
		}
	}
}
