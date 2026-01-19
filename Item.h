#ifndef H_item
#define H_item

#include <string>
#include <vector>
#include "structs.h"

using namespace std;

//---------------------------------------------------------------------------
/* Item
* This class is the basis for information regarding items, mainly the item's
* name, description, and the area the item starts in.
* Getters and setters for the name, description, and type attributes have been
* created for use with basic items, along with virtual getters and setters for
* use, consume, and battle items, as well as functions to print an item's name
* and description. The stream insertion operator is also overloaded to allow
* directly printing of class instances.
*/
class Item
{
    public:
        Item();
        void setName (string);
        void setDesc(string);
        void setSR(int);
        string getName();
        string getDesc();
        int getSR();
        void displayName();
        void displayDesc();
        string getType();
        virtual void setActiveMessage(string);
        virtual string getActiveMessage();
        virtual void setActiveArea(int);
        virtual int getActiveArea();
        virtual void addRule(Rule*);
        virtual vector<Rule*> getItemUseRules();
        virtual void addEffect(Effect*);
        virtual vector<Effect*> getItemConsumeEffects();
        virtual void setDamage(int);
        virtual int getDamage();
        friend ostream& operator<<(ostream&, Item&);

    protected:
        string name;
        string description;
        int startRoom;
        string activeMessage;
        int activeArea;
        string type;
};

#endif // H_item
