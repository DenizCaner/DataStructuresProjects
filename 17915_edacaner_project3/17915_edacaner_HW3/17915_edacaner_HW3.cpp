#include <iostream>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "HashTable.h"

using namespace std;

int main()
{
	HashTable myTable;
	int transNum = 0;
	srand(4);
	while(myTable.isFull() == false && transNum < 1000000)
	{
		int random = rand();
		int trans = (random%8);
		if(trans < 2)
		{
			random = rand();
			myTable.insert(random%3110);
		}
		else if (trans == 2)
		{
			random = rand();
			myTable.remove(random%3110);
		}
		else if (trans > 2)
		{
			random = rand();
			myTable.find(random%3110);
		}	
	}

	myTable.print(); 
	myTable.dataPrint();

	cin.get();
	cin.ignore();

	return 0;
}
