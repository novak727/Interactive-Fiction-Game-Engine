#include "ConsumeItem.h"

//---------------------------------------------------------------------------
/* Constructor to set the item type as a "consume" item.
*/
ConsumeItem::ConsumeItem()
{
    type = "consume";
}

//---------------------------------------------------------------------------
/* setActiveMessage() sets the activeMessage attribute to the value of the
* parameter.
*/
void ConsumeItem::setActiveMessage(string s)
{
    activeMessage = s;
}

//---------------------------------------------------------------------------
/* getActiveMessage() returns the activeMessage attribute.
*/
string ConsumeItem::getActiveMessage()
{
    return activeMessage;
}

//---------------------------------------------------------------------------
/* setActiveArea() sets the activeArea attribute to the value of the parameter.
*/
void ConsumeItem::setActiveArea(int i)
{
    activeArea = i;
}

//---------------------------------------------------------------------------
/* getActiveArea() returns the activeArea attribute.
*/
int ConsumeItem::getActiveArea()
{
    return activeArea;
}

//---------------------------------------------------------------------------
/* addEffect() adds the pointer parameter to the vector.
*/
void ConsumeItem::addEffect(Effect* temp)
{
    effects.push_back(temp);
}

//---------------------------------------------------------------------------
/* getItemConsumeEffects() returns the vector attribute effects.
*/
vector<Effect*> ConsumeItem::getItemConsumeEffects()
{
    return effects;
}
