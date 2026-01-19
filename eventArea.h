#ifndef H_eventarea
#define H_eventarea

#include "Area.h"

//CLASS eventArea
/********************************************************
Purpose:  A class that handles event area types
Private: (Event*) passive, (bool) activated;
Public: Contains mutators and accessors for event area information
methods:    eventArea(); string getType(); void resetArea();
    bool onEnter(Player* player); void setActiveMessage(string s);
    string getActiveMessage();void addEvent(Event* temp);
    Event* getEvent();
**********************************************************/
class eventArea : public Area
{
    public:
        eventArea();
        string getType();
        void resetArea();
        bool onEnter(Player*);
        void setActiveMessage(string);
        string getActiveMessage();
        void addEvent(Event*);
        Event* getEvent();
    private:
        Event* passive;
        bool activated;
};

#endif // H_eventarea
