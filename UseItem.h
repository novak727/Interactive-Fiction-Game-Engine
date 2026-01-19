#ifndef H_useitem
#define H_useitem

#include <vector>
#include <string>

#include "Item.h"
#include "structs.h"

using namespace std;

//---------------------------------------------------------------------------
/* UseItem
* This class derives from the Item class, creating items of the "use" type.
* Getters and setters for the active message, active area, and the rules for
* an item are created, along with a vector to store the rules for an item. A
* constructor is also defined to set the item type.
* These have an "is-a" relationship with the Item class.
*/
class UseItem : public Item
{
    public:
        UseItem();
        void setActiveMessage(string);
        string getActiveMessage();
        void setActiveArea(int);
        int getActiveArea();
        void addRule(Rule* temp);
        vector<Rule*> getItemUseRules();
    private:
        vector<Rule*> rules;
};

#endif // H_useitem
