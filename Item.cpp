#include <iostream>

#include "Item.h"

//---------------------------------------------------------------------------
/* Constructor to set the item type as a "basic" item and to set activeMessage
* and activeArea values to indicate that basic items do not have those present.
*/
Item::Item()
{
    activeMessage = "That seems quite impossible.";
    activeArea = -1;
    type = "basic";
}

//---------------------------------------------------------------------------
/* setName() takes a string parameter and sets the name of the item to what
* is stored in the parameter.
*/
void Item::setName (string n)
{
    name = n;
}

//---------------------------------------------------------------------------
/* setDesc() takes the string parameter and sets the description of the item
* to what is stored in the parameter.
*/
void Item::setDesc(string desc)
{
    description = desc;
}

//---------------------------------------------------------------------------
/* setSR() takes an integer parameter and sets the starting area for the item
* to the value of the parameter.
*/
void Item::setSR(int rm)
{
    startRoom = rm;
}

//---------------------------------------------------------------------------
/* getName() returns the name of the item.
*/
string Item::getName()
{
    return name;
}

//---------------------------------------------------------------------------
/* getDesc() returns the description of the item.
*/
string Item::getDesc()
{
    return description;
}

//---------------------------------------------------------------------------
/* getSR() returns the starting area for the item.
*/
int Item::getSR()
{
    return startRoom;
}

//---------------------------------------------------------------------------
/* displayName() prints out the name of the item.
*/
void Item::displayName()
{
    cout << name << endl;
}

//---------------------------------------------------------------------------
/* displayDesc() prints out the description the item.
*/
void Item::displayDesc()
{
    cout << description << endl;
}

//---------------------------------------------------------------------------
/* getType() returns the type of item when requested (either basic, use, or
* consume).
*/
string Item::getType()
{
    return type;
}

//---------------------------------------------------------------------------
/* setActiveMessage() prints a debug warning since this should never be called
* directly.
*/
void Item::setActiveMessage(string s)
{
    cout << "DEBUG WARNING: Objects of the Item (basic items) class don't " <<
        "have active messages." << endl;
}

//---------------------------------------------------------------------------
/* getActiveMessage() returns a blank string since this should never be called
* directly.
*/
string Item::getActiveMessage()
{
    // Objects of the Item (basic items) class don't have active messages.
    string aM = "";
    return aM;
}

//---------------------------------------------------------------------------
/* setActiveArea() prints a debug warning since this should never be called
* directly.
*/
void Item::setActiveArea(int i)
{
    cout << "DEBUG WARNING: Objects of the Item (basic items) class don't " <<
        "have active areas." << endl;
}

//---------------------------------------------------------------------------
/* getActiveArea() returns a negative area value since this should never be
* called directly.
*/
int Item::getActiveArea()
{
    // as this is a basic item, it doesn't have an active area
    return -1;
}

//---------------------------------------------------------------------------
/* addRule() prints a debug warning since this should never be called directly.
*/
void Item::addRule(Rule* temp)
{
    cout << "DEBUG WARNING: Objects of the Item (basic items) class don't " <<
        "have associated rules." << endl;
}

//---------------------------------------------------------------------------
/* getItemUseRules() sends blank data when called since it should never be
* called directly.
*/
vector<Rule*> Item::getItemUseRules()
{
    // shouldn't ever call this method directly
    vector<Rule*> blank;
    return blank;
}

//---------------------------------------------------------------------------
/* addEffect() prints a debug warning since this should never be called
* directly.
*/
void Item::addEffect(Effect* temp)
{
    cout << "DEBUG WARNING: Objects of the Item (basic items) class don't " <<
        "have associated effects." << endl;
}

//---------------------------------------------------------------------------
/* getItemConsumeEffects() sends blank data when called since it should never
* be called directly.
*/
vector<Effect*> Item::getItemConsumeEffects()
{
    // shouldn't ever call this method directly
    vector<Effect*> blank;
    return blank;
}

//---------------------------------------------------------------------------
/* setDamage() prints a debug statement since this should never be called
* directly.
*/
void Item::setDamage(int)
{
    cout << "DEBUG WARNING: Objects of the Item (basic items) class don't " <<
        "have damage." << endl;
}

//---------------------------------------------------------------------------
/* getDamage() returns -1 since it should never be called directly.
*/
int Item::getDamage()
{
    return -1;
}

//---------------------------------------------------------------------------
/* Stream insertion operator overloading to print instances of the class.
*/
ostream& operator<<(ostream& osObject, Item& item)
{
    osObject << "Name: " << item.getName() << endl;
    osObject << "Desc: " << item.getDesc() << endl;
    osObject << "StrtRm: " << item.getSR() << endl;
    return osObject;
}
