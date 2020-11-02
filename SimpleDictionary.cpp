// Project 3: Simple Dictionary - Tarang Lunawat
// 07/15/2020
#include <iostream>
#include<string>
#include <fstream>
#include "Word.h"
#include "WordList.h"
using namespace std;

string toUpperCase(string);
string promptUntilNotBlank(string, string);
void readFile(ifstream&, WordList&);
void promptAndAdd(WordList&);
void promptAndUpdate(WordList&);
void promptAndDelete(WordList&);

// reads in a command-line argument as a file name, validates it, and reads and stores a list of words and definitions from it
// repeatedly looks for menu commands until the user chooses to end the program
int main(int argc, char* argv[])
{
	if (argc == 1 || string(argv[1]).substr(string(argv[1]).length() - 4) != ".txt")
	{
		// there is either no command line argument or the (first) command line argument does not end with .txt
		cout << "Invalid command syntax. Please give a dictionary data file name." << endl;
		cout << "Syntax: Dictionary dictionary-data-file-name.txt" << endl << endl;
	}
	else
	{
		// opening provided file
		ifstream inFile(argv[1]);
		if (!inFile)
		{
			// file name is invalid
			cout << "The data file does not exist. Please check its name and location." << endl;
			cout << "Syntax: Dictionary dictionary-data-file-name.txt" << endl << endl;
		}
		else
		{
			// file name is valid
			// reading in words from file
			WordList dictionary;
			readFile(inFile, dictionary);
			inFile.close();

			cout << "Welcome to the dictionary!" << endl << endl;
			cout << "Please enter a command." << endl;
			cout << "Type 'end' to exit the program." << endl << endl;

			// loop for menu commands, ends when user enters 'end'
			// commands are case-insensitive
			string input;
			do
			{
				cin >> input;
				// capitalizing input to make it case insensitive
				input = toUpperCase(input);

				if (input == "LIST")
				{
					// clears buffer and prints out the dictionary
					cin.ignore(1024, '\n');
					cout << dictionary.toString();
				}
				else if (input == "ADD")
				{
					// clears buffer and calls function  to prompt user and validate add word to dictionary
					cin.ignore(1024, '\n');
					promptAndAdd(dictionary);
				}
				else if (input == "SEARCH")
				{
					// clears buffer
					cin.ignore(1024, '\n');
					// prompts for search string, calls WordList's search, and prints out the result
					string searchFor = promptUntilNotBlank("Please enter a word to search for: ", "Search");
					cout << dictionary.search(searchFor);
				}
				else if (input == "SAVE")
				{
					// opens user provided file as an ouput file
					ofstream outFile(argv[1]);
					// overwrites contents with the entire dictionary
					dictionary.save(outFile);
					outFile.close();
					cout << "Saved successfully." << endl;
					// clears buffer
					cin.ignore(1024, '\n');
				}
				else if (input == "UPDATE")
				{
					// clears buffer and calls function to prompt, validate, and update word
					cin.ignore(1024, '\n');
					promptAndUpdate(dictionary);
				}
				else if (input == "DELETE")
				{
					// clears buffer and calls function to prompt, validate, and delete word
					cin.ignore(1024, '\n');
					promptAndDelete(dictionary);
				}
				else if (input != "END")
				{
					// any other command is not recognized
					cout << "Invalid command." << endl;
					cin.ignore(1024, '\n');
				}

				cout << endl;
			} while (input != "END");
		}
	}
	// end message
	cout << "Thank you for using this program. Goodbye." << endl;
	return 0;
}

// returns a capitalized version of the string parameter
string toUpperCase(string str)
{
	// looping through and capitalizing each char
	for (char& c : str)
	{
		c = toupper(c);
	}
	return str;
}

// prompts user until the user enters something that is not empty or all spaces
// returns user's input
string promptUntilNotBlank(string prompt, string thingToEnter)
{
	// initial prompt
	cout << prompt;
	string userInput;
	getline(cin, userInput);
	// loops until the string contains a character that is not a space
	while (userInput.find_first_not_of(" ") == string::npos)
	{
		// error and reprompt
		cout << thingToEnter << " cannot be empty or blank. Please try again." << endl;
		cout << prompt;
		getline(cin, userInput);
	}

	return userInput;
}

// parses file and stores information as Word objects in provided WordList
void readFile(ifstream& inputFile, WordList& wl)
{
	// loops until end of file reached
	while (!inputFile.eof())
	{
		// reading word and definition, initializes Word object
		string word;
		inputFile >> word;
		inputFile.ignore(1024, '\n');
		string definition;
		getline(inputFile, definition);
		Word w(word, definition);
		// adds object to provided WordList
		wl.add(w);
	}
}

// prompts user for word and definition, then adds Word object to provided WordList
// gives output message based on whether add succeeded or was rejected
void promptAndAdd(WordList& wl)
{
	// reads input and creates word object
	string word = promptUntilNotBlank("Please enter a word: ", "Word");
	Word toAdd(word, "");
	if (!wl.exists(toAdd))
	{
		// provided WordList does not currently contain word the user wants to add
		// reads in definition and adds it to the word
		string definition = promptUntilNotBlank("Please enter the definition: ", "Definition");
		toAdd.setDefinition(definition);
		wl.add(toAdd);
		// provided WordList accepted and added Word
		cout << "Added new word successfully." << endl;
	}
	else
	{
		// provided WordList rejected Word because duplicate
		cout << "Word is already in dictionary. Could not add." << endl;
	}
}

// prompts user for word to update, validates it, then asks for definition and updates WordList
void promptAndUpdate(WordList& wl)
{
	// prompt for word to update definition of
	string word = promptUntilNotBlank("Please enter the word whose definition you would like to update: ", "Word");
	Word w(word, "");
	if (wl.exists(w))
	{
		// if the Word exists in provided WordList, prompts for definition and calls WordList's update with a new Word object with the new definition
		string definition = promptUntilNotBlank("Please enter the new definition: ", "Definition");
		wl.update(Word(word, definition));
		cout << "Word definition successfully updated" << endl;
	}
	else
	{
		// if the Word does not exist in the provided WordList, the user is not prompted for an updated definition
		cout << "That word does not exist in the dictionary." << endl;
	}
}

// prompts user for word to delete, validates it, and deletes if necessary
void promptAndDelete(WordList& wl)
{
	// prompts user for word to delete
	string word = promptUntilNotBlank("Please enter the word which you would like to delete: ", "Word");
	Word w(word, "");
	if (wl.exists(w))
	{
		// the user's input is a Word that exists in the dictionary
		// double-checking that the user wants to delete this word
		cout << "Are you sure you want to delete " << word << " from this dictionary (y/n)? ";
		char input;
		cin >> input;
		// repeating until valid input
		while (toupper(input) != 'Y' && toupper(input) != 'N')
		{
			cout << "Invalid answer. Please answer with either 'y' or 'n'." << endl;
			cin.ignore(1024, '\n');
			cout << "Are you sure you want to delete " << word << " from this dictionary (y/n)? ";
			cin >> input;
		}
		// clearing buffer
		cin.ignore(1024, '\n');
		if (toupper(input) == 'Y')
		{
			// user wants to delete, WordList is told to delete and a success message is printed
			wl.deleteWord(w);
			cout << "Deleted successfully." << endl;
		}
		else
		{
			// user does not want to delete
			cout << "Delete aborted." << endl;
		}
	}
	else
	{
		// the user's input is not a Word that exists in the dictionary
		cout << "That word does not exist in the dictionary." << endl;
	}
}
