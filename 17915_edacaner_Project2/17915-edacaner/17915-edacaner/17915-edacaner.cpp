#include <iostream>
#include <fstream>
#include <string>
#include <cctype>
#include <sstream>
#include <string>
#include <iomanip>
#include "BinarySearchTree.h"

using namespace std;

int main ()
{
	BinarySearchTree myTree; // creates a binary search tree object
	ifstream inFile; // for the input file
	ofstream outFile; // for the output file
	string outFileName = "compout.txt"; 
	string FileName = "compin.txt";
	inFile.open(FileName.c_str()); // Tries to open the file.
	if(inFile.fail()) // Enters the loop if the file can not be opened.
	{
		cout << "File cannot be opened." << endl; //Displays a message
		return 0;
	}

	outFile.open(outFileName.c_str()); // Opens the outFileName file. 

	string previous, current, str;
	int codeNumber = 256;

	char ch; 
	inFile.get(ch);
	previous = ch;
	current = previous;

	while (inFile.get(ch)) // reads the file char by char
	{
		if(codeNumber < 4096) // if there is still space in the binary seacrh stree
		{
			current = ch;
			str = previous + current;
			if(str.length() >= 2) // checks if the string value is longer than 1
			{
				if(myTree.search(str) != false) // checks if the string value already exists in the tree.
				{
					previous = str;
				}
				else
				{
					myTree.insert(codeNumber, str); // it insert string value to the tree
					codeNumber++; // increments the code value by one
					if(previous.length() < 2)
					{
					outFile << int(previous.at(0)) << " " ;
					}
					else
					{
						outFile << myTree.search(previous) << " ";
					}
					previous = current;
					str = current;
				}	
			}
			else
			{
				previous = str;
			}
		}
		else // if there is no place left in the tree
		{
			current = ch;
			str = previous + current;
			if(str.length() >= 2)
			{
				if(myTree.search(str) != false) // if the string value already exists in the list
				{
					previous = str;
				}
				else // if the string value does not exist in the list
				{
					if(previous.length() < 2)
					{
						outFile << int(previous.at(0)) << " " ;
					}
					else
					{
						outFile << myTree.search(previous) << " ";
					}
					previous = current;
					str = current;
				}
			}
			else
			{
				outFile << int(previous.at(0)) << " " ;
			}
		}
	}
	if(str.length() < 2)
	{
		outFile << int(str.at(0)) << " " ;
	}
	else
	{
		outFile << myTree.search(str) << " ";
	}

	outFile.close();

	cout << "You can find the compressed version of the file in the file named compout." << endl;

	cin.get();
	cin.ignore();

	return 0;

}