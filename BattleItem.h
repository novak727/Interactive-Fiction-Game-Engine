#ifndef H_battleitem
#define H_battleitem

#include "Item.h"

//---------------------------------------------------------------------------
/* BattleItem
* This class derives from the Item class, creating items of the "battle" type.
* A default constructor has been implemented to set the type attribute in the
* base class, and a getter & setter are implemented for the damage attribute
* for this class. This represents the base damage that a battle item will do
* to enemies.
*/
class BattleItem : public Item
{
    public:
        BattleItem();
        void setDamage(int);
        int getDamage();
    private:
        int damage;
};

#endif // H_battleitem
