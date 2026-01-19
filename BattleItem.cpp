#include "BattleItem.h"

//---------------------------------------------------------------------------
/* Default constructor, set item type and default damage of 0.
*/
BattleItem::BattleItem()
{
    type = "battle";
    damage = 0;
}

//---------------------------------------------------------------------------
/* setDamage() takes a parameter and sets the damage attribute to that value.
*/
void BattleItem::setDamage(int d)
{
    damage = d;
}

//---------------------------------------------------------------------------
/* getDamage() returns the value of the damage attribute.
*/
int BattleItem::getDamage()
{
    return damage;
}
