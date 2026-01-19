#include <iostream>
#include "IFDParser.h"

//---------------------------------------------------------------------------
/* Default constructor. Requests name of IFD file from user now.
*/
IFDParser::IFDParser()
{
    pos = 0;
    cout << "Enter the name of the IFD File: ";
    cin >> gameFile;
}

//---------------------------------------------------------------------------
/* tokenIt() is the main function that processes the IFD file, splitting all
* parts of the file into the appropriate locations while processing the IFD
* file.
*/
void IFDParser::tokenIt()
{
    string token="";
    string nextLine;
    char c;

    ifstream inFile;
    inFile.open(gameFile.c_str());

    while (!inFile.eof())
    {
        getline(inFile, nextLine);
        trim(nextLine);
        c=nextLine[0];

        // dump any comment or blank line (all comments exist alone on their lines)
        if (c=='%' || nextLine == "")
        {
            //do nothing
        }
        else
        {
            // tokenize the entire line
            // cout << nextLine << endl;
            for (int i = 0; i < nextLine.length(); i++)
            {
                if (nextLine[i] == '>')
                {
                    token = token + nextLine[i];
                    if (token !="\n" && token !="" && token !=" " && token !="\t")
                    {
                        tokenVec.push_back(token);
                    }
                    token = "";
                }
                else if (nextLine[i]=='<')
                {
                    if (token !="\n" && token !="" && token !=" " && token !="\t")
                    {
                        tokenVec.push_back(token);
                    }
                    token = "";
                    token = token + nextLine[i];
                }
                else
                {
                    token = token + nextLine[i];
                }
            }
        }
    } // while !eof
    inFile.close();
    return;
} // end of tokenIt()

//---------------------------------------------------------------------------
/* eatToken() advances to the next token in the IFD file when called by
* incrementing the position value for the vector.
*/
void IFDParser::eatToken()
{
    pos++;
}

//---------------------------------------------------------------------------
/* getNext() returns the current token in the vector.
*/
string IFDParser::getNext()
{
    return tokenVec[pos];
}

//---------------------------------------------------------------------------
/* trim() takes a string as an attribute and trims out the unneeded whitespace
* to aid in reading in data from the file.
*/
//helper function for trimming a string's white space
void IFDParser::trim(string& s)
{
    size_t p = s.find_first_not_of(" \t");
    s.erase(0, p);
    p = s.find_last_not_of(" \t");
    if (string::npos != p)
    {
        s.erase(p+1);
    }
}

//---------------------------------------------------------------------------
/* printTokens() prints all tokens that have been traversed through in the IFD
* file.
*/
void IFDParser::printTokens()
{
    cout << ":::Printing the Tokens in Order:::" << endl;
    for (int i = 0; i < tokenVec.size(); i++)
    {
        cout << i << ": " << tokenVec[i] << endl;
    }
}
