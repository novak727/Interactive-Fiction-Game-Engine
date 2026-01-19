#ifndef H_area
#define H_area

#include <string>

class Player;

#include "Enemy.h"
#include "Item.h"
#include "ull.h"
// #include "Player.h"

using namespace std;

//---------------------------------------------------------------------------
/* Area
* This class handles information about the current area the user is in during
* the IF game.
* The class stores the area description and whether or not the area is an
* instadeath or goal location as private attributes. A public attribute to
* handle items for the current area is also present.
* Methods are available to set the attribute values, retrieve the attribute
* values, and to print the area description. With items implemented, there is
* also a search routine to check an area for any items that may be present.
*/
class Area
{
    public:
        void setDescription (string);
        void setGoal(bool);
        void setID(bool);
        string getDescription();
        bool getID();
        bool getGoal();
        void displayArea();
        void search();
        void listEnemies();
        virtual bool onEnter(Player*) = 0;
        virtual string getType() = 0;
        virtual void resetArea();
        virtual void setActiveMessage(string);
        virtual string getActiveMessage();
        virtual void addRest(Rest*);
        virtual Rest* getRest();
        virtual void addEvent(Event*);
        virtual Event* getEvent();
        void setAreaNumber (int);
        int getAreaNumber();
        uLList<Item*> items;
        uLList<Enemy*> enemies;

    protected:
        string description;
        string type;
        string actMessage;
        bool instadeath;
        bool goal;
        int areaNum;
};

#endif // H_area
