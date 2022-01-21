// Implementation file for the Entry class

#include "Entry.h"
#include <iomanip>

void Entry::updateEntry(int lineNumber)
{
    if (lineNumber != lineNumbers[lineNumbers.size() - 1])
    {
        lineNumbers.push_back(lineNumber);
    }
}

void Entry::printEntry(ostream &outputStream) const
{
    outputStream << theWord << ":";
    for (int i = 0; i < lineNumbers.size() - 1; i++)
    {
        if (i % 10 == 0)
        {
            outputStream << "\n   ";
        }
        outputStream << setw(5) << lineNumbers[i] << ", ";
    }
    if (lineNumbers.size() % 10 == 1)
        outputStream << "\n   ";
    outputStream << setw(5) << lineNumbers[lineNumbers.size() - 1] << "\n"; // using \n instead of endl to improve efficiency writing to files
}
