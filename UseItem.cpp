#include "UseItem.h"

//---------------------------------------------------------------------------
/* Constructor to set the item type as a "use" item.
*/
UseItem::UseItem()
{
    type = "use";
}

//---------------------------------------------------------------------------
/* setActiveMessage() sets the activeMessage attribute to the value of the
* parameter.
*/
void UseItem::setActiveMessage(string s)
{
    activeMessage = s;
}

//---------------------------------------------------------------------------
/* getActiveMessage() returns the activeMessage attribute.
*/
string UseItem::getActiveMessage()
{
    return activeMessage;
}

//---------------------------------------------------------------------------
/* setActiveArea() sets the activeArea attribute to the value of the parameter.
*/
void UseItem::setActiveArea(int i)
{
    activeArea = i;
}

//---------------------------------------------------------------------------
/* getActiveArea() returns the activeArea attribute.
*/
int UseItem::getActiveArea()
{
    return activeArea;
}

//---------------------------------------------------------------------------
/* addRule() adds the pointer parameter to the vector.
*/
void UseItem::addRule(Rule* temp)
{
    rules.push_back(temp);
}

//---------------------------------------------------------------------------
/* getItemUseRules() returns the vector attribute rules.
*/
vector<Rule*> UseItem::getItemUseRules()
{
    return rules;
}
