#include <iostream>
#include <sstream>
#include <stdlib.h>

#include "MapV2.h"

//---------------------------------------------------------------------------
/* buildMap() calls on other methods of the Map class while parsing through
* the IFD file to build the game map for the IF game. This overrided version
* now adds support for items and different player types.
*/
void MapV2::buildMap()
{
    ifderr = false;
    parser.tokenIt();

    nextToken = parser.getNext();

    if (nextToken == "<game>")
    {
        parser.eatToken();
        nextToken = parser.getNext();
        while (nextToken != "</game>" && !ifderr)
        {
            if (nextToken == "<ptype>")
            {
                parser.eatToken();
                nextToken = parser.getNext();
                string ptype = nextToken;
                makePlayer(ptype);
            }
            else if (nextToken == "<area>") // build the area along with the features of the area
            {
                parser.eatToken();
                nextToken = parser.getNext();

                if (nextToken == "<normal>")
                {
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeArea();
                }
                else if (nextToken == "<event>")
                {
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeEventArea();
                }
                else if (nextToken == "<rest>")
                {
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeRestArea();
                }
                else
                {
                    cout << "Parse Error Location 10" << endl;
                    ifderr = true;
                    break;
                }

                while (nextToken != "</area>") // to get past </area>
                {
                    parser.eatToken();
                    nextToken = parser.getNext();
                }
            }
            else if (nextToken == "<links>") // link all areas together
            {
                parser.eatToken();
                nextToken = parser.getNext();
                makeLinks();
            }
            else if (nextToken == "<item>") // add items to each area
            {
                parser.eatToken();
                nextToken = parser.getNext();

                if (nextToken == "<basic>")
                {
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeItem();
                }
                else if (nextToken == "<use>")
                {
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeUseItem();
                }
                else if (nextToken == "<consume>")
                {
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeConsumeItem();
                }
                else if (nextToken == "<battle>")
                {
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeBattleItem();
                }
                else
                {
                    cout << "Parse Error Location 5" << endl;
                    ifderr = true;
                    break;
                }

                while (nextToken != "</item>") // to get past </item>
                {
                    parser.eatToken();
                    nextToken = parser.getNext();
                }
            }
            else if (nextToken == "<enemy>")
            {
                parser.eatToken();
                nextToken = parser.getNext();
                makeEnemy();
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

        if (ifderr) // error in IFD file during any part of the building process
        {
            cout << " :: ERROR :: IF Document Formatting Error" << endl;
            cout << "Game Loading Failed" << endl;
            cout << "General Area of Parsing Failure:" << endl;
            cout << "-------------------------------------" << endl;
            cout << nextToken<<endl;
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

    // insert items into areas
    insertItems();

    // insert enemies into areas
    insertEnemies();
}

//void makeEventArea Description
/********************************************************
Purpose:  Handles the parsing for event areas
Incoming: Nothing
Outgoing: Nothing
**********************************************************/
void MapV2::makeEventArea()
{
    string xstr;
    areaNode* tempAreaPtr = new areaNode;
    tempAreaPtr->info = new eventArea;
    while (nextToken != "</event>")
    {

        if (nextToken == "<desc>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempAreaPtr->info->setDescription(nextToken);
        }
        else if (nextToken == "<feats>") // apply if instadeath or goal area
        {
            parser.eatToken();
            nextToken = parser.getNext();

            istringstream ss(nextToken);
            getline(ss, xstr, ',');
            tempAreaPtr->info->setID(atoi(xstr.c_str()));

            getline(ss, xstr, ',');
            tempAreaPtr->info->setGoal(atoi(xstr.c_str()));
        }
        else if (nextToken == "<actmess>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempAreaPtr->info->setActiveMessage(nextToken);
        }
        else if (nextToken == "<altstat>")
        {
            string xstr;
            Event* tempEventPtr = new Event;

            parser.eatToken();
            nextToken = parser.getNext();

            istringstream ss(nextToken);
            getline(ss, xstr, ',');
            tempEventPtr->eventID = atoi(xstr.c_str());

            getline(ss, xstr, ',');
            tempEventPtr->effectedStat = xstr[0]; // easy way to convert to char, since the directions are only 1 character

            getline(ss, xstr, ',');
            tempEventPtr->statChange = atoi(xstr.c_str());

            tempAreaPtr->info->addEvent(tempEventPtr);
        }
        else if (nextToken == "</altstat>" || nextToken == "</desc>" ||
            nextToken == "</feats>" || nextToken == "</actmess>")
        {
            // do nothing
        }
        else
        {
            cout << "Parse Error Location 6" << endl;
            ifderr = true;
            break;
        }

        parser.eatToken();
        nextToken = parser.getNext();
    }

    tempAreaPtr->info->setAreaNumber(areasVec.size() + 1);
    areasVec.push_back(tempAreaPtr);
}

//void makeRestArea Description
/********************************************************
Purpose:  Handles the parsing for rest areas
Incoming: Nothing
Outgoing: Nothing
**********************************************************/
void MapV2::makeRestArea()
{
    string xstr;
    areaNode* tempAreaPtr = new areaNode;
    tempAreaPtr->info = new restArea;
    while (nextToken != "</rest>")
    {
        if (nextToken == "<desc>") // set description of area
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempAreaPtr->info->setDescription(nextToken);
        }
        else if (nextToken == "<feats>") // apply if instadeath or goal area
        {
            parser.eatToken();
            nextToken = parser.getNext();

            istringstream ss(nextToken);
            getline(ss, xstr, ',');
            tempAreaPtr->info->setID(atoi(xstr.c_str()));

            getline(ss, xstr, ',');
            tempAreaPtr->info->setGoal(atoi(xstr.c_str()));
        }
        else if (nextToken == "<actmess>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempAreaPtr->info->setActiveMessage(nextToken);
        }
        else if (nextToken == "<pause>")
        {
            Rest* tempRestPtr = new Rest;

            parser.eatToken();
            nextToken = parser.getNext();
            tempRestPtr->rest = nextToken;

            tempAreaPtr->info->addRest(tempRestPtr);
        }
        else if (nextToken == "</desc>" || nextToken == "</feats>"
            || nextToken == "</pause>" || nextToken == "</actmess>")
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

    tempAreaPtr->info->setAreaNumber(areasVec.size() + 1);
    // add area to vector
    areasVec.push_back(tempAreaPtr);
}

//void makeArea Description
/********************************************************
Purpose:  Handles the parsing for normal (basic) areas
Incoming: Nothing
Outgoing: Nothing
**********************************************************/
void MapV2::makeArea()
{
    string xstr;
    areaNode* tempAreaPtr = new areaNode;
    tempAreaPtr->info = new basicArea;

    while (nextToken != "</normal>")
    {
        if (nextToken == "<desc>") // set description of area
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempAreaPtr->info->setDescription(nextToken);
        }
        else if (nextToken == "<feats>") // apply if instadeath or goal area
        {
            parser.eatToken();
            nextToken = parser.getNext();

            istringstream ss(nextToken);
            getline(ss, xstr, ',');
            tempAreaPtr->info->setID(atoi(xstr.c_str()));

            getline(ss, xstr, ',');
            tempAreaPtr->info->setGoal(atoi(xstr.c_str()));
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

    tempAreaPtr->info->setAreaNumber(areasVec.size() + 1);
    // add area to vector
    areasVec.push_back(tempAreaPtr);

}

//---------------------------------------------------------------------------
/* makeItem() builds the item information for each basic item from the IFD
* file. Each item's name, description, and starting area is set for each item
* and then each item's pointer is then stored into the vector.
*/
void MapV2::makeItem()
{
    Item* tempItemPtr = new Item;

    while (nextToken != "</basic>")
    {
        if (nextToken == "<name>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setName(nextToken);
        }
        else if (nextToken == "<desc>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setDesc(nextToken);
        }
        else if (nextToken == "<star>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setSR(atoi(nextToken.c_str()));
        }
        else if (nextToken == "</name>" || nextToken == "</desc>" ||
                 nextToken == "</star>")
        {
            // do nothing
        }
        else
        {
            cout << "Parse Error Location 4" << endl;
            ifderr = true;
            break;
        }

        parser.eatToken();
        nextToken = parser.getNext();
    }

    itemsVec.push_back(tempItemPtr);
}

//---------------------------------------------------------------------------
/* makeUseItem() builds the item information for each usable item from the
* IFD file. Each item's name, description, starting area, active message, and
* active area is set for each item, as well as a vector for all the rules for
* each item. These are all saved to an Item pointer and then the Item that
* the pointer points to is stored into the vector.
*/
void MapV2::makeUseItem()
{
    Item* tempItemPtr = new UseItem;

    while (nextToken != "</use>")
    {
        if (nextToken == "<name>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setName(nextToken);
        }
        else if (nextToken == "<desc>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setDesc(nextToken);
        }
        else if (nextToken == "<star>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setSR(atoi(nextToken.c_str()));
        }
        else if (nextToken == "<actmess>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setActiveMessage(nextToken);
        }
        else if (nextToken == "<actar>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setActiveArea(atoi(nextToken.c_str()));
        }
        else if (nextToken == "<rule>")
        {
            string xstr;
            Rule* tempRulePtr = new Rule;

            parser.eatToken();
            nextToken = parser.getNext();

            istringstream ss(nextToken);
            getline(ss, xstr, ',');
            tempRulePtr->beginRm = atoi(xstr.c_str());

            getline(ss, xstr, ',');
            tempRulePtr->direction = xstr[0]; // easy way to convert to char, since the directions are only 1 character

            getline(ss, xstr, ',');
            tempRulePtr->destRm = atoi(xstr.c_str());

            tempItemPtr->addRule(tempRulePtr);
        }
        else if (nextToken == "</name>" || nextToken == "</desc>" ||
                 nextToken == "</star>" || nextToken == "</actmess>" ||
                 nextToken == "</actar>" || nextToken == "</rule>")
        {
            // do nothing
        }
        else
        {
            cout << "Parse Error Location 6" << endl;
            ifderr = true;
            break;
        }

        parser.eatToken();
        nextToken = parser.getNext();
    }

    itemsVec.push_back(tempItemPtr);
}

//---------------------------------------------------------------------------
/* makeConsumeItem() builds the item information for each usable item from
* the IFD file. Each item's name, description, starting area, active message,
* and active area is set for each item, as well as a vector for all the
* effects for each item. These are all saved to an Item pointer and then the
* Item that the pointer points to is stored into the vector.
*/
void MapV2::makeConsumeItem()
{
    Item* tempItemPtr = new ConsumeItem;

    while (nextToken != "</consume>")
    {
        if (nextToken == "<name>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setName(nextToken);
        }
        else if (nextToken == "<desc>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setDesc(nextToken);
        }
        else if (nextToken == "<star>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setSR(atoi(nextToken.c_str()));
        }
        else if (nextToken == "<actmess>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setActiveMessage(nextToken);
        }
        else if (nextToken == "<actar>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setActiveArea(atoi(nextToken.c_str()));
        }
        else if (nextToken == "<effect>")
        {
            string xstr;
            Effect* tempEffectPtr = new Effect;

            parser.eatToken();
            nextToken = parser.getNext();

            istringstream ss(nextToken);
            getline(ss, xstr, ',');
            tempEffectPtr->effectID = atoi(xstr.c_str());

            getline(ss, xstr, ',');
            tempEffectPtr->effectAmt = atoi(xstr.c_str());

            tempItemPtr->addEffect(tempEffectPtr);
        }
        else if (nextToken == "</name>" || nextToken == "</desc>" ||
                 nextToken == "</star>" || nextToken == "</actmess>" ||
                 nextToken == "</actar>" || nextToken == "</effect>")
        {
            // do nothing
        }
        else
        {
            cout << "Parse Error Location 7" << endl;
            ifderr = true;
            break;
        }

        parser.eatToken();
        nextToken = parser.getNext();
    }

    itemsVec.push_back(tempItemPtr);
}

//---------------------------------------------------------------------------
/* makeUseItem() builds the item information for each usable item from the
* IFD file. Each item's name, description, starting area, active message, and
* active area is set for each item, as well as a vector for all the rules for
* each item. These are all saved to an Item pointer and then the Item that
* the pointer points to is stored into the vector.
*/
void MapV2::makeBattleItem()
{
    Item* tempItemPtr = new BattleItem;

    while (nextToken != "</battle>")
    {
        if (nextToken == "<name>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setName(nextToken);
        }
        else if (nextToken == "<desc>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setDesc(nextToken);
        }
        else if (nextToken == "<star>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setSR(atoi(nextToken.c_str()));
        }
        else if (nextToken == "<damage>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempItemPtr->setDamage(atoi(nextToken.c_str()));
        }
        else if (nextToken == "</name>" || nextToken == "</desc>" ||
                 nextToken == "</star>" || nextToken == "</damage>")
        {
            // do nothing
        }
        else
        {
            cout << "Parse Error Location 8" << endl;
            ifderr = true;
            break;
        }

        parser.eatToken();
        nextToken = parser.getNext();
    }

    itemsVec.push_back(tempItemPtr);
}

//---------------------------------------------------------------------------
/* insertItems() inserts the items into their starting areas as set by the IFD
* file.
*/
void MapV2::insertItems()
{
    int index;
    Item* tempItem;

    for (int i = 0; i < itemsVec.size(); i++)
    {
        tempItem = itemsVec[i];
        index = tempItem->getSR() - 1; // aligns index properly since area numbers start at 1

        areasVec[index]->info->items.insertLast(tempItem);
    }
}

//---------------------------------------------------------------------------
/* resetItems() clears the items from all areas, then re-inserts them into
* the original starting areas.
*/
void MapV2::resetItems()
{
    for (int i = 0; i < areasVec.size(); i++)
    {
        areasVec[i]->info->items.destroyList();
        areasVec[i]->info->resetArea();
    }

    insertItems();
}

//---------------------------------------------------------------------------
/* makePlayer() makes a dynamic player type based on the value in the IFD file.
*/
void MapV2::makePlayer(const string ptype)
{
    playerPtr = nullptr;

    if (ptype == "basic")
    {
        playerPtr = new BasicPlayer;
    }
    else if (ptype == "hpsp")
    {
        playerPtr = new HPSPPlayer;
    }
    else if (ptype == "combat")
    {
        playerPtr = new CombatPlayer;
    }
    else
    {
        cout << "Unknown Player type. Defaulting to basic." << endl;
        playerPtr = new BasicPlayer();
    }

    parser.eatToken();
    nextToken = parser.getNext();
}

//---------------------------------------------------------------------------
/* getPlayer() returns the player pointer.
*/
Player* MapV2::getPlayer()
{
    return playerPtr;
}

//---------------------------------------------------------------------------
/* makeEnemy() builds enemy information for each enemy read in from the IFD
* file.
*/
void MapV2::makeEnemy()
{
    Enemy* tempEnemyPtr = new Enemy;

    while (nextToken != "</enemy>")
    {
        if (nextToken == "<name>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempEnemyPtr->setName(nextToken);
        }
        else if (nextToken == "<hp>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempEnemyPtr->setHP(atoi(nextToken.c_str()));
        }
        else if (nextToken == "<attack>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempEnemyPtr->setDamage(atoi(nextToken.c_str()));
        }
        else if (nextToken == "<area>")
        {
            parser.eatToken();
            nextToken = parser.getNext();
            tempEnemyPtr->setActiveArea(atoi(nextToken.c_str()));
        }
        else if (nextToken == "</name>" || nextToken == "</hp>"||
                 nextToken == "</attack>" || nextToken == "</area>")
        {
            // do nothing
        }
        else
        {
            cout << "Parse Error Location 9" << endl;
            ifderr = true;
            break;
        }

        parser.eatToken();
        nextToken = parser.getNext();
    }

    enemiesVec.push_back(tempEnemyPtr);
}

//---------------------------------------------------------------------------
/* insertEnemies() puts the enemies into the areas assigned by the IFD file.
*/
void MapV2::insertEnemies()
{
    int index;
    Enemy* tempEnemy;

    for (int i = 0; i < enemiesVec.size(); i++)
    {
        tempEnemy = enemiesVec[i];
        index = tempEnemy->getActiveArea() - 1; // aligns index properly since area numbers start at 1

        areasVec[index]->info->enemies.insertLast(tempEnemy);
    }
}

//---------------------------------------------------------------------------
/* applyRule() handles the changing of the map when a usable item modifies
* how the map should be structured.
*/
void MapV2::applyRule(Rule* r)
{
    if (r == nullptr)
    {
        return;
    }

    int beginIndex = r->beginRm - 1;
    int destIndex = r->destRm - 1;

    if (beginIndex < 0 || beginIndex >= areasVec.size() || destIndex < 0 ||
        destIndex >= areasVec.size())
    {
        cout << "Invalid area number in rule." << endl;
        return;
    }

    areaNode* from = areasVec[beginIndex];
    areaNode* to = areasVec[destIndex];
    char direction = r->direction;

    switch (direction)
    {
        case 'u':
            from->u = to;
            break;
        case 'd':
            from->d = to;
            break;
        case 'r':
            from->r = to;
            break;
        case 'l':
            from->l = to;
            break;
        default:
            cout << "Unknown direction" << endl;
    }
}

//---------------------------------------------------------------------------
/* Stream insertion operator overloaded so that cout can be used to print out
* all details of the map.
*/
ostream& operator<<(ostream& osObject, MapV2& map)
{
    osObject << "******************************************************************" << endl;
    osObject << "CHEATING!!!! Printing the set of areas and connections on the map." << endl;
    osObject << "******************************************************************" << endl;
    for (int i = 0; i < map.areasVec.size(); i++)
    {
        cout << "This is area: " << i+1 << endl;
        cout << map.areasVec[i]->info->getDescription() << endl;
        if (map.areasVec[i]->info->getID() == 1)
        {
            cout << "Area is INSTADEATH." << endl;
        }
        if (map.areasVec[i]->info->getGoal() == 1)
        {
            cout << "Area is GOAL." << endl;
        }
        cout << "Connections:" << endl;
        cout << "\t u: Area #" << map.reverseLookUp(map.areasVec[i]->u) << endl;
        cout << "\t d: Area #" << map.reverseLookUp(map.areasVec[i]->d) << endl;
        cout << "\t l: Area #" << map.reverseLookUp(map.areasVec[i]->l) << endl;
        cout << "\t r: Area #" << map.reverseLookUp(map.areasVec[i]->r) << endl;
    }

    osObject << "******************************************************************" << endl;
    osObject << "CHEATING!!!! ITEM LOCATIONS FOR ALL NON-INVENTORY ITEMS."           << endl;
    osObject << "******************************************************************" << endl;
    for (int i = 0; i < map.areasVec.size(); i++)
    {
        cout << "Items for area " << i+1 << ": " << map.areasVec[i]->info->getDescription() << endl;
        // map.areasVec[i]->info.items.printNames();
        map.areasVec[i]->info->items.printNamesMore();
    }
    return osObject;
}
