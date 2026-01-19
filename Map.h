#ifndef H_map
#define H_map

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>

#include "areaNode.h"
#include "Area.h"
#include "IFDParser.h"
#include "LinkData.h"

using namespace std;

//---------------------------------------------------------------------------
/* Map
* This class handles building of the map and the individual areas using the
* information from the IFD file.
* Attributes are created to help aid in building the map for the game, as well
* as a check to ensure the file was formatted properly, and to catch an
* improperly formatted file during map creation.
* Methods are created to build the map, the individual areas, link the areas
* together, and some features if the player calls the secret cheat code.
*/
class Map
{
    public:
        Map();
        void buildMap();
        void makeArea();
        void makeLinks();
        void linkLinks();
        areaNode* getStart();
        void print();
        friend ostream& operator<<(ostream& os, Map&);
        int reverseLookUp(areaNode*);

    protected:
        vector<areaNode*> areasVec;
        int areacnt;

        // Here is the instance of IFDParser
        IFDParser parser;

        // Some additional class attributes here
        vector<LinkData*> linkVec;
        string nextToken;

        bool ifderr;
};

#endif // H_map
