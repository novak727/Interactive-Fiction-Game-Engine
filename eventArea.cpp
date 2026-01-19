#include "eventArea.h"
#include "Player.h"

//eventArea eventArea Description
/********************************************************
Purpose:  Constructor
Incoming: Nothing
Outgoing: Nothing
**********************************************************/
eventArea::eventArea()
{
    type = "event";
    activated = false;
}

//void resetArea Description
/********************************************************
Purpose:  Used to reset event areas from being activated
Incoming: Nothing
Outgoing: Nothing
**********************************************************/
void  eventArea::resetArea()
{
    activated = false;
}

//string getType Description
/********************************************************
Purpose:  accessor
Incoming: Nothing
Outgoing: type
**********************************************************/
string eventArea::getType()
{
    return type;
}

//bool onEnter Description
/********************************************************
Purpose:  Keeps track if a player has entered an area
	and applies effects
Incoming: Player* player
Outgoing: true
**********************************************************/
bool eventArea::onEnter(Player* player)
{
    if (activated) //Logic Case: Player has already rested there
	{
		return false;
	}

	activated = true;	//Logic Case: Area has been activated

	player->updateStat(passive);
    cout << getActiveMessage() << endl;
	return true;
}

//void setActiveMessage Description
/********************************************************
Purpose:  setter
Incoming: string s
Outgoing: Nothing
**********************************************************/
void eventArea::setActiveMessage(string s)
{
    actMessage = s;
}

//string getActiveMessage Description
/********************************************************
Purpose:  accessor
Incoming: Nothing
Outgoing: actMessage
**********************************************************/
string eventArea::getActiveMessage()
{
    return actMessage;
}

//void addEvent Description
/********************************************************
Purpose:  setter
Incoming: Event* temp
Outgoing: Nothing
**********************************************************/
void eventArea::addEvent(Event* temp)
{
    passive = temp;
}

//Event* getEvent Description
/********************************************************
Purpose:  accessor
Incoming: Nothing
Outgoing: passive
**********************************************************/
Event* eventArea::getEvent()
{
    return passive;
}
