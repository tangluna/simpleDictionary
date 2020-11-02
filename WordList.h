// Specification file for the WordList class
// Project 3: Simple Dictionary - Tarang Lunawat - 07/15/2020
#ifndef WORDLIST_H
#define WORDLIST_H

#include <string>
#include <fstream>
#include <vector>
using namespace std;

class Word;

// manages a list of Words, allows adding, updating, deleting, searching, and checking for existence
class WordList
{
public:
	string toString();
	bool add(Word);
	string search(string);
	void save(ofstream&);
	bool exists(Word);
	bool update(Word);
	bool deleteWord(Word);
private:
	vector<Word> list;
};

#endif WORDLIST_H
