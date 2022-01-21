// An entry for a concordance, consisting of a word and a vector of line numbers

#ifndef ENTRY_H
#define ENTRY_H

#include <vector>
#include <iostream>
#include <string>
using namespace std;

class Entry
{
private:
    string theWord;
    vector<int> lineNumbers;

public:
    // constructor
    Entry(string aWord, int lineNumber) : theWord(aWord)
    {
        lineNumbers.push_back(lineNumber);
    }

    // returns the data value for the entry (the word)
    string getKey() const { return theWord; }

    // update entry with a new line number
    void updateEntry(int lineNumber);

    // print entry to the specified output stream
    void printEntry(ostream &outputStream) const;
};

#endif
