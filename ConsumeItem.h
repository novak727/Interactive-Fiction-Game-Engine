#ifndef H_consumeitem
#define H_consumeitem

#include <string>
#include <vector>

#include "Item.h"
#include "structs.h"

using namespace std;

//---------------------------------------------------------------------------
/* ConsumeItem
* This class derives from the Item class, creating items of the "consume"
* type.
* Getters and setters for the active message, active area, and the effects
* for an item are created, along with a vector to store the rules for an
* item. A constructor is also defined to set the item type.
* These have an "is-a" relationship with the Item class.
*/
class ConsumeItem : public Item
{
    public:
        ConsumeItem();
        void setActiveMessage(string);
        string getActiveMessage();
        void setActiveArea(int);
        int getActiveArea();
        void addEffect(Effect*);
        vector<Effect*> getItemConsumeEffects();
    private:
        vector<Effect*> effects;
};

#endif // H_consumeitem
