// Implementation file for the Word class
// Project 3: Simple Dictionary - Tarang Lunawat - 07/15/2020
#include "Word.h"
#include <string>
using namespace std;

// Constructor: removes leading whitespace from word and defintion, adds correct whitespace to definition, and initializes both fields
Word::Word(string w, string d)
{
	if (w.find_first_not_of(" ") != string::npos)
	{
		// if there is any leading whitespace, removes it
		word = w.substr(w.find_first_not_of(" "));
	}
	else
	{
		// if not, initializes to parameter
		word = w;
	}
	
	if (d.find_first_not_of(" ") != 2 && d.find_first_not_of(" ") != string::npos)
	{
		// if there is leading whitespace and there is not 2 spaces, takes out whitespace and adds 2 leading spaces
		definition = "  " + d.substr(d.find_first_not_of(" "));
	}
	else if (d.find_first_not_of(" ") == string::npos)
	{
		// if there is no whitespace, adds 2 spaces
		definition = "  " + d;
	}
	else
	{
		// if there are alrewady 2 spaces of whitespace, simply initializes to parameter
		definition = d;
	}
}

// returns a string with the word and definition
// one line contains the word, the next has the definition with an indent of 2 spaces
string Word::toString()
{
	string returnString = word + "\n" + definition;
	return returnString;
}

// returns word
string Word::getWord()
{
	return word;
}

// returns definition WITH leading whitespace
string Word::getDefinition()
{
	return definition;
}

// formats and stores new definition in same way as in the constructor
void Word::setDefinition(string newDef)
{
	if (newDef.find_first_not_of(" ") != 2 && newDef.find_first_not_of(" ") != string::npos)
	{
		// if there is leading whitespace and there is not 2 spaces, takes out whitespace and adds 2 leading spaces
		definition = "  " + newDef.substr(newDef.find_first_not_of(" "));
	}
	else if (newDef.find_first_not_of(" ") == string::npos)
	{
		// if there is no whitespace, adds 2 spaces
		definition = "  " + newDef;
	}
	else
	{
		// if there are alrewady 2 spaces of whitespace, simply initializes to parameter
		definition = newDef;
	}
}

// returns a capitalized version of the string parameter
string Word::toUpperCase(string str)
{
	// looping through and capitalizing each char
	for (char& c : str)
	{
		c = toupper(c);
	}

	return str;
}

// searches for passed in string in the Word name and definition
// returns true if found, case-insensitive
bool Word::search(string searchFor)
{
	// capitalizes to ignore case
	searchFor = toUpperCase(searchFor);
	// returns true if the string is found in either the name or definition
	return toUpperCase(word).find(searchFor) != string::npos || toUpperCase(definition).find(searchFor) != string::npos;
}

// checks if the parameter string is the Word name, case-insensitive
bool Word::isWord(string checkAgainst)
{
	// capitalizes before checking
	return toUpperCase(word) == toUpperCase(checkAgainst);
}
