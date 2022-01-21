// Implementation file for the Dictionary class
// Stores data in a basic binary search tree

#include "Dictionary.h"

Dictionary :: Dictionary(){
    count = 0;
    sizeIndex = 0;
    tableSize = hashTableSizes[sizeIndex];
    hashTable = new Entry*[tableSize]();//an array of pointers to (null) entry objects may need to be changed later
}

// Assignment Operator
Dictionary &Dictionary::operator=(const Dictionary &rhs)
{
    if(this->hashTable != rhs.hashTable){
        clear();
        copy(rhs);
    }
    return *this;
}

// Check to see if the Dictionary isEmpty
bool Dictionary::isEmpty() const {
    return count == 0;
}

// Add an entry
// Precondition: the dictionary must not already have an Entry with the same key
// Postcondition: the Entry has been added to the dictionary
void Dictionary::addEntry(Entry *anEntry) {
    int index = hash(anEntry);
    //if hash produce a valid index
    if (index != -1){
        hashTable[index] = anEntry;
        count++;

        if((count + 1) > (tableSize/2)){
            rehash();
        }
    }
}

// Returns nullptr if the entry is not found and the pointer to the Entry if it is
Entry *Dictionary::findEntry(string key) const {
    int index = stringHash(key, tableSize);
    int offset = stringHash(key, secondaryHashNums[sizeIndex]) + 1;
    Entry *entry = nullptr;

    //if this this index in the table isnt empty
    if(hashTable[index]){
        //while the index being accessed exists, and
        // does not contain the key we are looking for
        while(hashTable[index] && (hashTable[index]->getKey() != key)){
            index += offset;
        }
        entry =  hashTable[index];
    }
    return entry;
}

// Print entries in order
// Calls printEntry on each Entry in order
void Dictionary::printDictionaryInOrder(ostream &outputStream) const {

    std::vector<Entry*> vectorOfTable;

    for(int i = 0; i <tableSize; i++){
        if(hashTable[i]){
            vectorOfTable.push_back(hashTable[i]);
        }
    }

    std::sort(vectorOfTable.begin(), vectorOfTable.end());

    for(int i = 0; i <tableSize; i++){
        if (vectorOfTable[i])
            vectorOfTable[i]->printEntry(outputStream);
    }
}

// Prints the dictionary keys only, demonstrating the dictionary structure
void Dictionary::printDictionaryKeys(ostream &outputStream) const {
    for(int i = 0; i<tableSize; i++){
        if(hashTable[i]){
            outputStream << hashTable[i]->getKey();
            if (i < tableSize - 1)
                outputStream << " ";
        }
    }
    outputStream << endl;
}

// clear helper method for copy constructor and assignment operator
void Dictionary::clear() {
    for(int i =0; i<tableSize; i++){
        if(hashTable[i])
            delete hashTable[i];
    }
    delete hashTable;
}

// copy helper method for destructor and assignment operator
void Dictionary::copy(const Dictionary &orig) {

    this->tableSize = orig.tableSize;
    this->hashTable = new Entry*[tableSize]();
    this->sizeIndex = orig.sizeIndex;
    this->count = orig.count;

    for(int i = 0; i<tableSize; i++){
        if(orig.hashTable[i]){
            this->hashTable[i] = new Entry(*(orig.hashTable[i]));
        }
    }
}

// Hash routine for string objects
// (Copied from Data Structures and Algorithm Analysis in C++. 4th Edition)
// Author(s): Weiss, Mark Allen. (2013)
unsigned int Dictionary::stringHash(const string &key, int tableSize) const{
    unsigned int hashVal = 0;

    for(char ch : key){
        hashVal = 37 * hashVal + ch;
    }
    return hashVal % tableSize;
}

// Utility method to create a table that is twice as big as
// the current table and store all keys from original in new table
// (Called right before original table is 50% full)
void Dictionary::rehash(){
    // create a new array that has a size of the first
    // prime number after doubling the size of the original array
    sizeIndex++;
    tableSize = hashTableSizes[sizeIndex];
    Entry ** newTable = new Entry*[tableSize]();

    // Loop through the original hash table and
    // place each entry in its correct spot in new table
    for (int i = 0; i< sizeIndex - 1; i++){
        //if the index in the original array isn't null, copy it over
        if (hashTable[i])
            newTable[hash(hashTable[i])] = hashTable[i];
    }

    delete hashTable;
    hashTable = newTable;
}

//Utility function to return the index of a new entry
int Dictionary::hash(Entry *anEntry) {
    //If the entry isn't null
    if (anEntry){
        int index = stringHash(anEntry->getKey(), tableSize);
        int offset = stringHash(anEntry->getKey(), secondaryHashNums[sizeIndex]) + 1;//MUST CHANGE THE INDEX OF secondaryHashNums HERE

        //while the index being accessed is not empty
        while(hashTable[index]){
            //wrap around to the beginning of the array if needed
            if(index > tableSize){
                index = index -  tableSize;
            } else{
                index += offset;
            }
        }
        return index;
    }
    else{
        return -1;
    }
}






