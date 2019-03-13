#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
#include <cctype>
#include <vector>
#include <sstream>
#include <string>
#include "strutils.h"

using namespace std;

int main()
{
	string dictArray[4096];

	for(int i = 0; i < 256; i++) // enters the string values of ascii table into the array
	{
		dictArray[i] = char(i) ;
	}

	ifstream inFile; // for the input file
	ofstream outFile;  // for the output file
	string FileName = "decompin.txt";
	string outFileName = "decompout.txt"; 
	inFile.open(FileName.c_str()); // Tries to open the file.
	if(inFile.fail()) // Enters the loop if the file can not be opened.
	{
		cout << "File cannot be opened." << endl; //Displays a message
		return 0;
	}

	outFile.open(outFileName.c_str()); // Opens the outFileName file. 

	int counter = 256; // my counter starts from the 256th index
	int previous, current; // previously read index number and currently read index number
	int input;
	string  str, line;

	while(getline(inFile, line))
	{
		istringstream strStream(line);
		strStream >> input;
		previous = input;
		while(strStream >> input) // reads the file word by word eating up the space 
		{
			current = input;
			if(counter > current ) // checks if the values exists in the list
			{
				str = dictArray[previous] + dictArray[current].at(0) ;
				outFile << dictArray[previous] ;
				previous = current;
				if(counter < 4096 ) //checks if there is still space in the array
				{
					dictArray[counter] = str;
					counter++;
				}
			}
			else  // if the code does not exists in the array
			{
				str = dictArray[previous] + dictArray[previous].at(0) ;
				outFile << str ;
				if(counter < 4096 ) // if there is a space to enter the new values
				{
					dictArray[counter] = str;
					counter ++;
				}
				previous = current;
			}
		}
	}
	
	outFile << dictArray[previous] ;
	outFile.close();  // closes the file

	cout << "You can find the decompressed version of the file in the file named decompout." << endl;

	cin.get();
	cin.ignore();

	return 0;
}