#include <iostream>
#include <fstream>
#include "strutils.h"
#include <string>
#include <cctype>
#include <sstream>
#include <string>
#include "prompt.h"
#include <iomanip>
#include "searchEngine.h"

using namespace std;

//EDA DENÝZ CANER - 17915

int main()
{
	LinkedList wordList; // the list for the data
	LinkedList outList; // the list which includes the search result
	string word, docNum, value;
	int docNumInt, valueInt = 0, length, s2;
	ifstream inFile;
	string FileName = "docdb.txt";
	inFile.open(FileName.c_str()); // Tries to open the file.
	if(inFile.fail()) // Enters the loop if the file can not be opened.
	{
		cout << "File cannot be opened." << endl; //Displays a message
		return 0;
	}

	string line;
	while (getline(inFile, line)) // reads the file line by line.
	{
		int len = line.length(); // finds the length of the line.
		int s1 = line.find(' ');

		word = line.substr(0, s1); // redefines the line.
		StripWhite(word);
		ToLower(word);
		
		docNum = line.substr(s1+1, len - s1 - 1); //subtract the ID number from the line.
		StripWhite(docNum); 
		docNumInt = atoi(docNum);// transforms the string valu into integer.


		if(wordList.doesExist(word)) // checks if the word it reads already exists in the list or not
		{
			wordList.findWordAddDoc(word, docNumInt); // if the word exists, finds the node that store that word and add a doc number to it.
		}
		else
		{
			wordList.AddWord(word); // if the word does not exist in the list, adds the word to the list.
			wordList.findWordAddDoc(word, docNumInt); // finds the words in the list and add a document number.
		}	
	}

	string input; // = PromptString("Enter:"); //Wants user to enter input to search.
	cout << "Enter the words that you want to search: " ;
	cin >> input ;
	cout << "    " << endl;
	
	length = input.length(); // finds the length of the line.
	s2 = input.find(' ');

	value = input.substr(0, s2); // redefines the line.
	StripWhite(value);
	valueInt = atoi(value);// transforms the string valu into integer.

	while(valueInt != 0)
	{
		getline(cin,word); // reads the input line

		//input= input.substr(s2+1, length - s2 - 1); 
		StripWhite(word); 
	
		istringstream strStream(word);
		string inputWord;

		for (int i= 0; i<valueInt; i++) 
		{	
			strStream >> inputWord; // reads the input line word by word.
			if (wordList.doesExist(inputWord))
			{
				wordNode * temp = wordList.findWord(inputWord);
				fileNode * tempFile = temp->right;
				outList.AddWord(temp->word);
				wordNode * temp2 = outList.findWord(inputWord);
				fileNode * temp2File = temp2->right;
				outList.findWordAddDoc(inputWord,tempFile->fileNumber);
				while(tempFile->right != NULL)
				{
					tempFile = tempFile->right;
					outList.findWordAddDoc(inputWord,tempFile->fileNumber);
				}
			}
			else
			{
				cout << word << " 0 " << endl;
				cout << "    " << endl;
				cout << "    " << endl;
				cout << "Enter the words that you want to search: " ;
				cin >> input ;
				cout << "    " << endl;
	
				length = input.length(); // finds the length of the line.
				s2 = input.find(' ');

				value = input.substr(0, s2); // redefines the line.
				StripWhite(value);
				valueInt = atoi(value);// transforms the string valu into integer.
			}
			
		}

		wordNode * temp1 = outList.getHead();
		fileNode * file1 = temp1->right;

		if (valueInt == 1) // if the user is searching for only one word
		{
			outList.DisplayResult(temp1); 
		}
		else if (valueInt > 1) // if the user is ssearching for more than one word
		{
			wordNode * temp2 = temp1->next;
			fileNode * file2 = temp2->right;
	
			for(int i = 1; i < valueInt; i++)
			{
				while(file1->right != NULL)
				{
						if(outList.doesExistDocNum(temp2, file1->fileNumber))
						{	
							file1 = file1->right;
						}
						else
						{	
							file1 = outList.RemoveDocNum2(temp1,file1->fileNumber);
							file1 = file1->right;
						}	
			   }
				if(file1->right == NULL )
				{
					if(outList.doesExistDocNum(temp2, file1->fileNumber)) // if the document number is common with the first word in the list
						{	
							file1 = file1->right;
						}
						else
						{	
							file1 = outList.RemoveDocNum2(temp1,file1->fileNumber); // it removes the doc num from the list if it is not common
							file1 = file1->right;
						}
				}
				file1 = temp1->right;
				temp2 = temp2->next;
			}
			outList.DisplayResult(temp1); // displays the results
		}

		outList.deleteList(); // deletes the list which we store the results in it in order to run the program once more.

	cout << "    " << endl;
	cout << "    " << endl;
	cout << "Enter the words that you want to search: " ;
	cin >> input ;
	cout << "    " << endl;
	
	length = input.length(); // finds the length of the line.
	s2 = input.find(' ');

	value = input.substr(0, s2); // redefines the line.
	StripWhite(value);
	valueInt = atoi(value);// transforms the string valu into integer.
	}
}