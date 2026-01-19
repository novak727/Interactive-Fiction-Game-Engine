#include "basicArea.h"

//basicArea basicArea Description
/********************************************************
Purpose:  Constructor
Incoming: Nothing
Outgoing: Nothing
**********************************************************/
basicArea::basicArea()
{
    type = "basic";
}

//bool onEnter Description
/********************************************************
Purpose:  Keeps track if a player has entered an area
Incoming: Player* player
Outgoing: true
**********************************************************/
bool basicArea::onEnter(Player* player)
{
    return true;
}

//string getType Description
/********************************************************
Purpose:  accessor
Incoming: Nothing
Outgoing: type
**********************************************************/
string basicArea::getType()
{
    return type;
}
