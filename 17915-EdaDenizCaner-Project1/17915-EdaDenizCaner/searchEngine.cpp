#include <iostream>
#include <cctype>
#include <string>
#include "searchEngine.h"

using namespace std;

LinkedList::LinkedList()
{
	head = NULL; //equalizes head pointer to null
	tail = NULL; //equalizes tail pointer to null
} // constructor

void LinkedList::AddWord(string & a) // this function is created to add a word to a sorted doubly linked list.
{
	if (head == NULL)  // checks if the list is empty.
	{   // creates a new node and equalizes head pointer to it.
		wordNode* tmp = new wordNode;
		tmp->right = NULL;
		tmp->word = a;
		head = tmp; //equalizes head pointer to tmp
		tail = tmp; //equalizes tail pointer to tmp
		tail->next = NULL; //equalizes tail->next to null
		head->next = NULL; //equalizes head->next to null
		return;
	}
	if( a < head->word) // check if new nodes should be added before the head of the list.
	{//creates a new node and makes it a head pointer and connects to the rest of the link list.
		wordNode * temp = new wordNode;  //node to be inserted 
		temp->word = a;
		temp->right = NULL;
		temp->next = head;
		head = temp;
		return;
	}
	wordNode * ptr = head;   // loop variable
	while (ptr->next != NULL && ptr->next && ptr->next->word < a) //search the linked list until the end or the place to insert the new node.
	{    
		ptr = ptr->next;
	} 
	if(ptr->next)
	{
		wordNode * temp = new wordNode;  //node to be inserted is created.
		temp->word = a;
		temp->right = NULL;
		temp->next = ptr->next; //connects the rest
		ptr->next = temp;
	}
	else
	{
		wordNode * temp = new wordNode;  //node to be inserted is created.
		temp->word = a;
		temp->right = NULL;
		ptr->next = temp;
		tail = temp;
		tail->next = NULL;
	}
} // adds a word to the list

bool LinkedList::doesExist(string & a) //checks whether the word already exists in the list or not.
{
	wordNode * ptrTemp = head; // creates a new loop pointer and equalizes it to the head pointer.
	while (ptrTemp != NULL)
	{
		if(ptrTemp->word == a) //it returns true if the word already exists in the list.
		{
			return true;
		}
		else // goes to the next pointer in the linked list.
		{
			ptrTemp = ptrTemp->next;
		}
	}
	return false; // returns false if the node does not exist in the linked list.
} 

bool LinkedList::doesExistDocNum(wordNode * ptrIn, int & b) //checks whether the document number already exists in the list of that specific word.
{
	wordNode * ptrTemp = ptrIn; // creates a new loop pointer and equalizes it to the head pointer.
	fileNode * ptrInFile = ptrIn->right;
	while (ptrInFile != NULL)
	{
		if(ptrInFile->fileNumber == b) //it returns true if the word already exists in the list.
		{
			return true;
		}
		else // goes to the next pointer in the linked list.
		{
			ptrInFile = ptrInFile->right;
		}
	}
	return false; // returns false if the node does not exist in the linked list.
}

void  LinkedList::findWordAddDoc(string & a, int & b) // finds the node that store the specific word and adds document number to its list.
{
	wordNode * ptrTemp = head; // creates a new loop pointer and equalizes it to the head pointer.
	while (ptrTemp->word != a) // checks if the word is what it is looking for or not.
	{
			ptrTemp = ptrTemp->next;	
	}

	if (ptrTemp->right == NULL) // checks if the next node in the document number list of that specific word is NULL or nor.
	{   
		fileNode* temp = new fileNode; // node to be inserted
		temp->fileNumber = b;
		ptrTemp->right = temp;
		temp->right = NULL;
		return;
	}
	if( ptrTemp->right != NULL && b < ptrTemp->right->fileNumber) 
	{
		fileNode * temp = new fileNode;  //node to be inserted 
		temp->fileNumber = b;
		temp->right = ptrTemp->right; // connects the rest
		ptrTemp->right = temp;
		return;
	}
	fileNode * ptr = ptrTemp->right;   // loop variable
	while (ptr->right != NULL && ptr->right && ptr->right->fileNumber < b) //search the linked list until the end or the place to insert the new node.
	{    
		ptr = ptr->right;
	} 
	if(ptr->right)
	{
		fileNode * temp = new fileNode;  //node to be inserted is created.
		temp->fileNumber = b;
		temp->right = ptr->right; //connects the rest
		ptr->right = temp;
	}
	else // if document number is added to the end of that specific word's document number list.
	{
		fileNode * temp = new fileNode;  //node to be inserted is created.
		temp->fileNumber = b;
		ptr->right = temp;
		temp->right = NULL; //makes if the end node and makes sure that its right pointer sis equal to NULL.
	}

}

wordNode * LinkedList::findWord(string & a) // finds that specific word in the linked list and returns a pointer to it.
{
	wordNode * ptrTemp = head; // creates a new loop pointer and equalizes it to the head pointer.
	while (ptrTemp->word != a && ptrTemp->next != NULL)
	{
			ptrTemp = ptrTemp->next;	
	}
	if(ptrTemp->word == a) // checks if it is the word the function is looking for.
	{
		return ptrTemp;
	}
}

wordNode * LinkedList::getHead() // returns the head of the word linked list.
{
	return head;
}

fileNode * LinkedList::RemoveDocNum2(wordNode * ptrIn, int & b) // remove the document number from that specific word. 
{
	wordNode * temp = ptrIn;
	fileNode * ptrFile = ptrIn->right;
	if(ptrIn->right->fileNumber != b)
	{
		while (ptrFile->right != NULL  && ptrFile->right->fileNumber != b) //search the linked list until the end or the place to insert the new node.
		{    
			ptrFile = ptrFile->right;
		} 
		fileNode * ptrTemp = ptrFile->right;
		if(ptrTemp->right != NULL) 
		{    
			ptrFile->right = ptrTemp->right;
			delete ptrTemp;
			return ptrFile;
		}
		else // if the node to be deleted is the last node in the list.
		{    
			ptrFile->right = NULL;
			delete ptrTemp;
			return ptrFile;
		}
	} 
	else // if the node to be deleted is the first node of the document number list of that specific word.
	{
		ptrIn->right = ptrFile->right;
		delete ptrFile;
		return ptrIn->right;
	} 
}

void LinkedList::DisplayResult(wordNode * ptrIn) // displays the results 
{
	wordNode * temp = ptrIn;
	while(temp->next != NULL)
	{
		cout << temp->word << " " ;
		temp = temp->next;
	}
	
	if(ptrIn->right == NULL ) // if the list is empty in displays 0
	{
		cout << "0" << endl;
	}
	else
	{
		while(temp  != NULL) // displays the words in the word linked list
		{
			cout << " " ;
			cout << temp->word << " "  ;
			cout << " "  ;
			temp = temp-> next;
		}

		fileNode * fileTemp = ptrIn->right;
		while(fileTemp != NULL) // displays the common document numbers
		{
		cout << fileTemp->fileNumber << " " ;
		fileTemp = fileTemp->right;

		}
	}
}

void LinkedList::deleteList() // it deletes the list when we are done with it.
{
	wordNode * wordPtr = head;
	fileNode * filePtr = wordPtr->right;
	while(filePtr != NULL)
	{
		fileNode * tempFile = filePtr->right;
		if(filePtr->right != NULL)
		{
			filePtr->right = tempFile->right;
			delete tempFile;
		}
		else
		{
			filePtr->right = NULL;
			delete tempFile;
			filePtr = filePtr->right;
		}	
	}
	while(wordPtr->next != NULL)
	{
		wordNode * tempWord = wordPtr->next;
		if(wordPtr->next != NULL)
		{
			wordPtr->next = tempWord->next;
			delete tempWord;
		}
		else
		{
			wordPtr->next = NULL;
			delete tempWord;
			wordPtr = wordPtr->next;
		}
	}	
	delete head;
	head = NULL;
}