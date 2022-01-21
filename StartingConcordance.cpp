// Program to build a concordance from an input file using a dictionary
// There are two output files, one with the concordance, and one showing the structure of the dictionary

#include "Dictionary.h"
#include <fstream>
#include <ctype.h>
#include <sstream>

// function prototypes

// opens and reads the input file, building the dictionary
void buildDictionary(const string &inFileName, Dictionary &dict);

// open the concordance file and write the dictionary to it
void writeConcordance(const string &outFileName, const Dictionary &dict);

// open the dictionary structure file and write the structure of the dictionary to it
void writeDictionaryStructure(const string &outFileName, const Dictionary &dict);

int main(int argc, char **argv)
{
    // gather the file name arguments
    if (argc < 4)
    {
        // we didn't get enough arguments, so complain and quit
        cout << "Usage: " << argv[0] << " infile concordanceOutputFile dictionaryStructureOutputFile" << endl;
        exit(1);
    }

    string inFileName = argv[1];
    string concFileName = argv[2];
    string dictFileName = argv[3];


    Dictionary dict; // set up the dictionary

    // build the dictionary
    buildDictionary(inFileName, dict);

    // write the dictionary to the concordance file
    writeConcordance(concFileName, dict);

    // write the dictionary structure to the dictionary structure file
    writeDictionaryStructure(dictFileName, dict);
}

void buildDictionary(const string &inFileName, Dictionary &dict)
{
    int lineNumber = 1;
    string line;
    string curWord;

    // open the file
    ifstream infile(inFileName);
    if (infile.fail())
    {
        cerr << "Could not open " << inFileName << " for input" << endl;
        exit(1);
    }

    // YOUR CODE GOES HERE -- feel free to also add additional function(s) if desired

    //while there are still characters to get from the file, see if they are letters and store them in the dictionary
    while (std::getline(infile, line)){
        line += '\n';
        //iterate through each character in the line
        for (char character: line){
            //if the character is a letter
            if(isalpha(character)){
                curWord += tolower(character);//add lowercase character to current word
            }
            else{
                //if the word isn't empty, create new entry and place in dictionary
                if (!curWord.empty()){
                    //if the entry does not already exist in the dictionary
                    if(!dict.findEntry(curWord)){
                        Entry *entry = new Entry(curWord, lineNumber);
                        dict.addEntry(entry);
                    }
                    else{
                        dict.findEntry(curWord)->updateEntry(lineNumber); // add the lineNumber to the entry's list
                    }
                    curWord.clear();
                }
            }
        }
        lineNumber++;
    }
    infile.close();
}

void writeConcordance(const string &outFileName, const Dictionary &dict)
{
    ofstream outfile(outFileName);
    if (outfile.fail())
    {
        cerr << "Could not open " << outFileName << " for output\n";
        cerr << "Concordance not written " << endl;
        return;
    }
    dict.printDictionaryInOrder(outfile);
    outfile.close();
}

void writeDictionaryStructure(const string &outFileName, const Dictionary &dict)
{
    ofstream outfile(outFileName);
    if (outfile.fail())
    {
        cerr << "Could not open " << outFileName << " for output\n";
        cerr << "Dictionary structure file not written " << endl;
        return;
    }
    dict.printDictionaryKeys(outfile);
    outfile.close();
}
