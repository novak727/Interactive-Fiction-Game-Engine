#include <iostream>

#include "Area.h"

//---------------------------------------------------------------------------
/* setDescription() sets the description of the area the player is currently
* in, pulled from the IFD file.
*/
void Area::setDescription(string desc)
{
    description = desc;
}

//---------------------------------------------------------------------------
/* setGoal() sets whether or not you have reached a goal area, meaning you
* have successfully won the game.
*/
void Area::setGoal(bool g)
{
    goal = g;
}

//---------------------------------------------------------------------------
/* setID() sets whether or not the area is an instadeath area, meaning you
* have lost the game.
*/
void Area::setID(bool id)
{
    instadeath = id;
}

//---------------------------------------------------------------------------
/* getDescription() sends the description of the current area.
*/
string Area::getDescription()
{
    return description;
}

//---------------------------------------------------------------------------
/* getID() sends the current value of the instadeath variable.
*/
bool Area::getID()
{
    return instadeath;
}

//---------------------------------------------------------------------------
/* getGoal() sends the current value of the goal variable.
*/
bool Area::getGoal()
{
    return goal;
}

//---------------------------------------------------------------------------
/* displayArea() prints the description of the current area the player is in.
*/
void Area::displayArea()
{
    cout << description << endl;
}

//---------------------------------------------------------------------------
/* search() iterates through the unordered linked list of all items in the
* current area and prints out all items if there are any, or prints that no
* items are in this area if there are none (meaning the linked list is empty).
*/
void Area::search()
{
    if (items.isEmptyList())
    {
        cout << "No items in this area" << endl;
    }
    else
    {
        nodeType<Item*>* current = items.getFirst();
        while (current != nullptr)
        {
            cout << "\t";
            current->info->displayName();
            current = current->link;
        }
    }
}

//---------------------------------------------------------------------------
/* listEnemies() lists all the enemies in an area as well as the remaining HP
* for each enemy.
*/
void Area::listEnemies()
{
    if (enemies.isEmptyList())
    {
        cout << "No enemies in this area." << endl;
    }
    else
    {
        nodeType<Enemy*>* current = enemies.getFirst();
        while (current != nullptr)
        {
            cout << "\t";
            current->info->displayName();
            current = current->link;
        }
    }
}

//---------------------------------------------------------------------------
/* addRest() prints a debug warning.
*/
void Area::addRest(Rest* temp)
{
    cout << "DEBUG WARNING: Objects of the Area (basic areas) class can not rest." << endl;
}

//---------------------------------------------------------------------------
/* getRest() returns a nullptr.
*/
Rest* Area::getRest()
{
    Rest* blank = nullptr;
    return blank;
}

//---------------------------------------------------------------------------
/* addEvent() prints a debug warning.
*/
void Area::addEvent(Event* temp)
{
    cout << "DEBUG WARNING: Objects of the Area (basic areas) class do have events ." << endl;
}

//---------------------------------------------------------------------------
/* getEvent() returns a nullptr.
*/
Event* Area::getEvent()
{
    Event* blank = nullptr;
    return blank;
}

//---------------------------------------------------------------------------
/* setActiveMessage() prints a debug warning.
*/
void Area::setActiveMessage(string s)
{
    cout << "DEBUG WARNING: Objects of the Item (basic areas) class don't have active messages." << endl;
}

//---------------------------------------------------------------------------
/* getActiveMessage() returns a blank string.
*/
string Area::getActiveMessage()
{
    string blank = "";
    return blank;
}

//---------------------------------------------------------------------------
/* resetArea() does nothing.
*/
void Area::resetArea()
{
    return;
}

//---------------------------------------------------------------------------
/* setAreaNum() sets the number for the area.
*/
void Area::setAreaNumber(int num)
{
    areaNum = num;
}

//---------------------------------------------------------------------------
/* getAreaNum() returns the areaNum attribute.
*/
int Area::getAreaNumber()
{
    return areaNum;
}
