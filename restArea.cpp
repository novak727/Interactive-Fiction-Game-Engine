#include "restArea.h"
#include "Player.h"

//restArea restArea Description
/********************************************************
Purpose:  Constructor
Incoming: Nothing
Outgoing: Nothing
**********************************************************/
restArea::restArea()
{
    type = "rest";
    rested = false;
}

//void resetArea Description
/********************************************************
Purpose:  Used to reset rested areas from being activated
Incoming: Nothing
Outgoing: Nothing
**********************************************************/
void restArea::resetArea()
{
    rested = false;
}

//string getType Description
/********************************************************
Purpose:  accessor
Incoming: Nothing
Outgoing: type
**********************************************************/
string restArea::getType()
{
    return type;
}

//bool onEnter Description
/********************************************************
Purpose:  Keeps track if a player has entered an area
	and applies effects
Incoming: Player* player
Outgoing: false and true
**********************************************************/
bool restArea::onEnter(Player* player)
{
    if (rested)
    {
        cout << "You can not rest here again" << endl;
        return false;
    }

    string restType = safe->rest;
    if (restType == "f")
    {
        player->resetPlayerStats();
        cout << "You Feel energized and calm again" << endl << endl;
        rested = true;
        return true;
    }
    else
    {
        return false;
    }
}

//void setActiveMessage Description
/********************************************************
Purpose:  setter
Incoming: string s
Outgoing: Nothing
**********************************************************/
void restArea::setActiveMessage(string s)
{
    actMessage = s;
}

//string getActiveMessage Description
/********************************************************
Purpose:  accessor
Incoming: Nothing
Outgoing: actMessage
**********************************************************/
string restArea::getActiveMessage()
{
    return actMessage;
}

//void addRest Description
/********************************************************
Purpose:  setter
Incoming: Rest* temp
Outgoing: Nothing
**********************************************************/
void restArea::addRest(Rest* temp)
{
    safe = temp;
}

//Rest* getRest Description
/********************************************************
Purpose:  accessor
Incoming: Nothing
Outgoing: safe
**********************************************************/
Rest* restArea::getRest()
{
    return safe;
}
