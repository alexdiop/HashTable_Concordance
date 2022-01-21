// An dictionary created using a basic binary search tree

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "Entry.h"
#include <algorithm>

class Dictionary
{
private:
    int count;
    int sizeIndex;
    const int hashTableSizes [14] = {101, 211, 431, 863, 1733, 3469, 6947, 13901,
                                      27803, 55609, 11127, 222461, 444929, 889871};
    const int secondaryHashNums [14] = {97, 199, 421, 859, 1723, 3467, 6917, 13883,
                                  27799, 55603, 111217, 222437, 444901, 889829};
    int tableSize;
    Entry** hashTable;
    bool operator()(Entry* e1, Entry* e2) const
    {
        return e1 < e2;
    }

public:
    // Constructor
    Dictionary();

    // Copy constructor
    Dictionary(const Dictionary &orig) {copy(orig);}

    // Destructor
    ~Dictionary(){clear();}

    // Assignment operator
    Dictionary &operator=(const Dictionary &rhs);

    // Check to see if the Dictionary isEmpty
    bool isEmpty() const;

    // Add an entry
    // Precondition: the dictionary must not already have an Entry with the same key
    // Postcondition: the Entry has been added to the dictionary
    void addEntry(Entry *anEntry);

    // Find an entry
    // Returns nullptr if the entry is not found and the pointer to the Entry if it is
    Entry *findEntry(string key) const;

    // Print entries in order
    // Calls printEntry on each Entry in order
    void printDictionaryInOrder(ostream &outputStream) const;

    // Prints the dictionary keys only, demonstrating the dictionary structure
    void printDictionaryKeys(ostream &outputStream) const;

private:
    // clear helper method for copy constructor and assignment operator
    void clear();

    // copy helper method for destructor and assignment operator
    void copy(const Dictionary &orig);

    unsigned int stringHash(const string& key, int tableSize) const;

    //Utility function to return the index of a new entry
    int hash(Entry *anEntry);

    // Utility method to create a table that is twice as big as
    // the current table and store all keys from original in new table
    // (Called right before original table is 50% full)
    void rehash();

};

#endif
