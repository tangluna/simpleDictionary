// Implementation file for the WordList class
// Project 3: Simple Dictionary - Tarang Lunawat - 07/15/2020
#include "WordList.h"
#include "Word.h"
#include <string>
#include <fstream>
#include <vector>

// adds the parameter Word to the list if it is not a duplicate of an already existing word (definitions are not checked, only word name) and neither field is empty
// returns true if the Word was successfully added
bool WordList::add(Word toAdd)
{
	bool success = true;
	// checks if either Word field is empty or contains only spaces, if so, throws flag to not add word
	if (toAdd.getWord().find_first_not_of(" ") == string::npos || toAdd.getDefinition().find_first_not_of(" ") == string::npos)
	{
		success = false;
	}
	// checks if Word already exists, i.e word name is same as an already stored one, if so throws flag to not add word
	for (size_t i = 0; i < list.size() && success; i++)
	{
		if (list[i].isWord(toAdd.getWord()))
		{
			success = false;
		}
	}
	// if flag is not thrown, adds Word to vector
	if (success)
	{
		list.push_back(toAdd);
	}
	return success;
}

// returns a string format of all the Words stored in the WordList
// one line has the word name, the next has the definiton indented by 2 spaces
string WordList::toString()
{
	string toReturn = "";
	if (list.size() == 0)
	{
		// if there are no words, sets the return string
		toReturn = "No words in dictionary.\n";
	}
	// loops through each word and adds it to the string to return
	for (size_t i = 0; i < list.size(); i++)
	{
		toReturn += list[i].toString();
		toReturn += '\n';
	}
	return toReturn;
}

// searches for a string in all the Words names and definitions, returns a string with all the matches
// one line has the word name, the next has the definition indented by 2 spaces
string WordList::search(string searchFor)
{
	string matching = "";
	// loops through Words
	for (size_t i = 0; i < list.size(); i++)
	{
		if (list[i].search(searchFor))
		{
			// if there is a match, adds Word to string to return
			matching += list[i].toString();
			matching += '\n';
		}
	}
	// if there are no matches, sets return string to say so
	if (matching == "")
	{
		matching = "No matches found.\n";
	}
	return matching;
}

// writes the toString() return string to the passed in ofstream object
void WordList::save(ofstream &outFile)
{
	outFile << this->toString();
}

// returns true if there is a Word that has the same name as the passed in Word object
bool WordList::exists(Word w)
{
	bool exists = false;
	// loops through all Words unless a match is found
	for (size_t i = 0; i < list.size() && !exists; i++)
	{
		// if there is a match, throws flag
		if (list[i].isWord(w.getWord()))
		{
			exists = true;
		}
	}
	return exists;
}

// changes the definition of a Word object with the same name as the parameter object to match the parameter object's defintion
// returns false if there is no match found to update
bool WordList::update(Word w)
{
	bool success = false;
	// loops through all Words unless a match is found
	for (size_t i = 0; i < list.size() && !success; i++)
	{
		// if a match is found, sets definition to that of the parameter Word
		if (list[i].isWord(w.getWord()))
		{
			list[i].setDefinition(w.getDefinition());
			success = true;
		}
	}
	return success;
}

// deletes the Word object whose name matches the parameter object from the list
// if no such object is found, returns false
bool WordList::deleteWord(Word w)
{
	bool success = false;
	// loops through all Words unless a match is found
	for (size_t i = 0; i < list.size() && !success; i++)
	{
		// if a match is found, erases that Word object from the list
		if (list[i].isWord(w.getWord()))
		{
			list.erase(list.begin() + i);
			success = true;
		}
	}
	return success;
}
