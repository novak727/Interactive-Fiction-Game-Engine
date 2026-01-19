#ifndef H_ifdparser
#define H_ifdparser

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

using namespace std;

//---------------------------------------------------------------------------
/* IFDParser
* This class helps parse the IFD file so that the program can read in all
* parts of a properly formatted file and build the map accordingly.
* There is an integer to keep track of where in the vector you are during
* processing, a string for the file name, and the vector itself.
* Methods for this class help with the traversing of the file, taking various
* parts of the file so the program can get the relevant information it needs.
*/
class IFDParser
{
    public:
        IFDParser();
        IFDParser(string);
        void setFile(string);
        void tokenIt();
        void eatToken();
        string getNext();
        void trim(string&);
        void printTokens();

    private:
        int pos;
        string gameFile;
        vector<string> tokenVec;
};

#endif // H_ifdparser
