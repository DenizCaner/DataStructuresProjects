#ifndef _SEARCHENGINE_H
#define _SEARCHENGINE_H
#include <string>

using namespace std;

struct fileNode // class definition
{
	int fileNumber;
	fileNode * right;
};

struct wordNode // class definition
{
	string word;
	wordNode * next;
	fileNode * right;
};

class LinkedList // class definition
{
public:
	LinkedList(); //constructor
	void AddWord(string & a);
	void AddDocNum(int & a);
	void findWordAddDoc(string & a, int & b);
	void DisplayWord(string & a);
	void DisplayResult(wordNode * ptrIn);
	void deleteList();
	wordNode * getHead();
	bool doesExist(string & a);
	bool doesExistDocNum(wordNode * ptrIn, int & b);
	void RemoveDocNum(string & a, int & b);
	fileNode * RemoveDocNum2(wordNode * ptrIn, int & b);
	wordNode * findWord(string & a);
private:
	wordNode * head;
	wordNode * tail;
};

#endif