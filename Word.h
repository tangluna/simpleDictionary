// Specification file for the Word class
// Project 3: Simple Dictionary - Tarang Lunawat - 07/25/2020
#ifndef WORD_H
#define WORD_H

#include <string>
using namespace std;

// represents a single word, stores word and defintion, provides implementation to convert to string, access data, change definition, search, and check for matches
class Word
{
public:
	Word(string, string);
	string toString();
	string getWord();
	string getDefinition();
	void setDefinition(string);
	bool search(string);
	bool isWord(string);
private:
	string word;
	string definition;
	string toUpperCase(string str);
};

#endif WORD_H
