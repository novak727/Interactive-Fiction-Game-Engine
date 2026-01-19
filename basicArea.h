#ifndef H_basicarea
#define H_basicarea

#include "Area.h"

//CLASS basicArea
/********************************************************
Purpose:  A class that handles basic area types
Public methods: basicArea(); string getType(); bool onEnter(Player* player);
**********************************************************/
class basicArea : public Area
{
    public:
        basicArea();
        bool onEnter(Player*);
        string getType();
};

#endif // H_basicarea
