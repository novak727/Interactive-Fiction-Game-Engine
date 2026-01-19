#ifndef H_restarea
#define	H_restarea

#include "Area.h"

//CLASS restArea
/********************************************************
Purpose:  A class that handles rest area types
Private: (Rest*) safe, (bool) rested;
Public: Contains mutators and accessors for event area information
methods:    eventArea(); string getType(); void resetArea();
    bool onEnter(Player* player); void setActiveMessage(string s);
    string getActiveMessage();void void addRest(Rest* temp);
    Rest* getRest();
**********************************************************/
class restArea : public Area
{
    public:
        restArea();
        void resetArea();
        string getType();
        bool onEnter(Player*);
        void setActiveMessage(string);
        string getActiveMessage();
        void addRest(Rest*);
        Rest* getRest();
    private:
        Rest* safe;
        bool rested;
};

#endif // H_restarea
