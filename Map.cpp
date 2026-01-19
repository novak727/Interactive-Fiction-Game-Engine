#include <iostream>

#include "Map.h"

//---------------------------------------------------------------------------
/* Default constructor.
*/
Map::Map()
{
    areacnt = 0;
    ifderr = false;
    nextToken = "";
}

//---------------------------------------------------------------------------
/* buildMap() calls on other methods of the Map class while using the IFD file
* to build the initial game map for the IF game.
*/
void Map::buildMap()
{
    ifderr = false;
    parser.tokenIt();

    nextToken = parser.getNext();

    if (nextToken == "<game>")
    {
        parser.eatToken();
        nextToken = parser.getNext();
        while (nextToken != "</game>") // consider what happens when run out of tokens && not error state
        {
            if (nextToken == "<area>") // build the area along with the features of the area
            {
                parser.eatToken();
                nextToken = parser.getNext();
                makeArea();
            }
            else if (nextToken == "<links>") // link all areas together
            {
                parser.eatToken();
                nextToken = parser.getNext();
                makeLinks();
            }
            else
            {
                cout << "Parse Error Location 1" << endl;
                ifderr = true;
                break;
            }
            parser.eatToken();
            nextToken = parser.getNext();
        } // while !</game>

        if (ifderr) // error in IFD file during any part of the map building process
        {
            cout << " :: ERROR :: IF Document Formatting Error" << endl;
            cout << "Game Loading Failed" << endl;
            cout << "General Area of Parsing Failure:" << endl;
            cout << "-------------------------------------" << endl;
            cout << nextToken << endl;
            parser.eatToken();
            nextToken = parser.getNext();
            cout << nextToken << endl;
            parser.eatToken();
            nextToken = parser.getNext();
            cout << nextToken << endl;
            parser.eatToken();
            nextToken = parser.getNext();
            cout << nextToken << endl;
            cout << "-------------------------------------" << endl;
            return;
        }
    }
    else
    {
        cout << " :: ERROR :: No \"<game>\" tag found." << endl;
        cout << "Game Loading Failed" << endl;
    }

    // link up areas
    linkLinks();
}

//---------------------------------------------------------------------------
/* makeArea() builds each individual area of the map and applies all relevant
* features to each individual area.
*/
void Map::makeArea()
{
    string xstr;
    areaNode* tempNodePtr = new areaNode;

    while (nextToken != "</area>")
    {
        if (nextToken == "<desc>") // set description of area
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempNodePtr->info->setDescription(nextToken);
        }
        else if (nextToken == "<feats>") // apply if instadeath or goal area
        {
            parser.eatToken();
            nextToken = parser.getNext();

            istringstream ss(nextToken);
            getline(ss, xstr, ',');
            tempNodePtr->info->setID(atoi(xstr.c_str()));

            getline(ss, xstr, ',');
            tempNodePtr->info->setGoal(atoi(xstr.c_str()));
        }
        else if (nextToken == "</desc>" || nextToken == "</feats>")
        {
            // do nothing
        }
        else
        {
            cout << "Parse Error Location 2" << endl;
            ifderr = true;
            break;
        }

        parser.eatToken();
        nextToken = parser.getNext();
    } // while !</area>

    // add area to vector
    areasVec.push_back(tempNodePtr);
} // end makeArea()

//---------------------------------------------------------------------------
/* makeLinks() creates the links between each areas of the IF game map, as a
* part of the map building process.
*/
void Map::makeLinks()
{
    string xstr;
    int u, d, l, r;
    while (nextToken != "</links>")
    {
        if (nextToken == "<linkset>")
        {
            parser.eatToken();
            nextToken = parser.getNext();

            LinkData* tempLDPtr = new LinkData;
            istringstream ss(nextToken);
            getline(ss, xstr, ',');
            u = atoi(xstr.c_str());
            getline(ss, xstr, ',');
            d = atoi(xstr.c_str());
            getline(ss, xstr, ',');
            l = atoi(xstr.c_str());
            getline(ss, xstr, ',');
            r = atoi(xstr.c_str());

            tempLDPtr->setDigits(u, d, l, r);
            linkVec.push_back(tempLDPtr);
        }
        else if (nextToken == "</linkset>")
        {
            //do nothing
        }
        else
        {
            cout << "Parse Error Location 3" << endl;
            ifderr = true;
            break;
        }
        parser.eatToken();
        nextToken = parser.getNext();
    } // while !</links>
} // makeLinks()

//---------------------------------------------------------------------------
/* linkLinks() links up all areas of the map together as part of the map
* building process.
*/
void Map::linkLinks()
{
    for (int i = 0; i < linkVec.size(); i++)
    {
        areasVec[i]->u = areasVec[(linkVec[i]->getDigit(0))-1];
        areasVec[i]->d = areasVec[(linkVec[i]->getDigit(1))-1];
        areasVec[i]->l = areasVec[(linkVec[i]->getDigit(2))-1];
        areasVec[i]->r = areasVec[(linkVec[i]->getDigit(3))-1];
    }
}

//---------------------------------------------------------------------------
/* getStart() returns the starting area of the map (aka the first area)
*/
areaNode* Map::getStart()
{
    return areasVec[0];  //returns a pointer to the first area listed
}

//---------------------------------------------------------------------------
/* print() prints out all information about the map, including all connections
* to and from areas and whether or not an area is a win or instadeath. Called
* currently only when the cheat code is entered by player.
*/
void Map::print()
{
    cout << "******************************************************************" << endl;
    cout << "CHEATING!!!! Printing the set of areas and connections on the map." << endl;
    cout << "******************************************************************" << endl;
    for (int i = 0; i < areasVec.size(); i++)
    {
        cout << "This is area: " << i+1 << endl;
        cout << areasVec[i]->info->getDescription() << endl;
        if (areasVec[i]->info->getID() == 1)
        {
            cout << "Area is INSTADEATH." << endl;
        }
        if (areasVec[i]->info->getGoal() == 1)
        {
            cout << "Area is GOAL." << endl;
        }
        cout << "Connections:" << endl;
        cout << "\t u: Area #" << reverseLookUp(areasVec[i]->u) << endl;
        cout << "\t d: Area #" << reverseLookUp(areasVec[i]->d) << endl;
        cout << "\t l: Area #" << reverseLookUp(areasVec[i]->l) << endl;
        cout << "\t r: Area #" << reverseLookUp(areasVec[i]->r) << endl;
    }
}

//---------------------------------------------------------------------------
/* Stream insertion operator overloaded so that cout can be used instead of
* calling the print() function.
*/
ostream& operator<<(ostream& os, Map& m)
{
    os << "******************************************************************" << endl;
    os << "CHEATING!!!! Printing the set of areas and connections on the map." << endl;
    os << "******************************************************************" << endl;
    for (int i=0; i < m.areasVec.size(); i++)
    {
        os << "This is area: " << i+1 << endl;
        os << m.areasVec[i]->info->getDescription() << endl;
        if (m.areasVec[i]->info->getID() == 1)
        {
            os << "Area is INSTADEATH." << endl;
        }
        if (m.areasVec[i]->info->getGoal() == 1)
        {
            os << "Area is GOAL." << endl;
        }
        os << "Connections:" << endl;
        os << "\t u: Area #" << m.reverseLookUp(m.areasVec[i]->u) << endl;
        os << "\t d: Area #" << m.reverseLookUp(m.areasVec[i]->d) << endl;
        os << "\t l: Area #" << m.reverseLookUp(m.areasVec[i]->l) << endl;
        os << "\t r: Area #" << m.reverseLookUp(m.areasVec[i]->r) << endl;
    }

    return os;
}
//---------------------------------------------------------------------------
/* reverseLookUp() searches for the area number for each connected area to
* another area. Only called currently when the cheat code is called.
*/
int Map::reverseLookUp(areaNode* addy)
{
    for (int i = 0; i < areasVec.size(); i++)
    {
        if (areasVec[i] == addy)
        {
            return i+1;
        }
    }

    // this should not happen
    return -1;
}
