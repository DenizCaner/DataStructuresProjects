#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include <string>

//using namespace std;

struct hashInput
{
	//status ->  0 = empty, 1 = inUse, 2 = deleted;	
	int status;
	int value;
	hashInput::hashInput()
	{
		value=-3;
		status=0;
	}
};

struct dataInput
{
	double loadFactor;
	int numOfProbes;
	dataInput::dataInput()
	{
		loadFactor=0;
		numOfProbes=0;
	}
};

class HashTable
{
public:
HashTable();
int hash(int key);
void insert(int a);
void remove(int a);
void print();
void dataPrint();
bool find(int a);
bool isFull();

private:
hashInput myTable[311];
dataInput successFind[312];
dataInput failedFind[312];
dataInput successInsert[312];
dataInput failedInsert[312];
dataInput successRemove[312];
dataInput failedRemove[312];
int usedCell;
double load;
int probeNum;
};

#endif