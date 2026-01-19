#include "CombatPlayer.h"
#include "MapV2.h"

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>

using namespace std;

//---------------------------------------------------------------------------
/* Default constructor, sets all stats to their default values and no equipped
* weapon.
*/
CombatPlayer::CombatPlayer()
{
    hitPoints = 100;
    sanityPoints = 100;
    attackStat = 10;
    defenseStat = 10;
    equippedWeapon = nullptr;
    srand(time(0));
}

//---------------------------------------------------------------------------
/* isGameOver() returns one of 3 value depending on if the game continues (0),
* the player won (1), or the player lost (2).
*/
int CombatPlayer::isGameOver()
{
    if (currentLocation->info->getGoal())
    {
        return 1;
    }
    else if (currentLocation->info->getID() || hitPoints <= 0 ||
             sanityPoints <= 0)
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

//---------------------------------------------------------------------------
/* resetPlayerStats() resets the stat values back to 100 and unequips any
* weapon.
*/
void CombatPlayer::resetPlayerStats()
{
    hitPoints = 100;
    sanityPoints = 100;
    attackStat = 10;
    defenseStat = 10;
    equippedWeapon = nullptr;
}

//---------------------------------------------------------------------------
/* reportStats() prints out the current stat values and equipped weapon.
*/
void CombatPlayer::reportStats()
{
    cout << "\t HP: " << hitPoints << endl;
    cout << "\t SP: " << sanityPoints << endl;
    cout << "\t Attack: " << attackStat << endl;
    cout << "\t Defense: " << defenseStat << endl;
    if (equippedWeapon != nullptr)
    {
        cout << "\t Equipped Weapon: " << equippedWeapon->getName() << endl;
    }
    else
    {
        cout << "\t Equipped Weapon: None" << endl;
    }
}

//---------------------------------------------------------------------------
/* consume() allows a Player to consume an item from their inventory, presuming
* it exists in the inventory.
*/
void CombatPlayer::consume(string itemName)
{
    string n = itemName;

    nodeType<Item*>* temp = NULL;
    temp = items.getFirst();

    if(temp == NULL)
    {
        cout << "You have no items in your inventory." << endl;
    }
    else
    {
        bool found = false;
        while (temp != NULL && !found)
        {
            if (n == temp->info->getName())
            {
                found = true;
                ConsumeItem* cur = dynamic_cast<ConsumeItem*>(temp->info);
                if (!cur)
                {
                    cout << "That item is not consumable." << endl;
                }
                else
                {
                    int actar = cur->getActiveArea();
                    // int currentArea = mapptr->reverseLookUp(getCurrent());

                    int currentArea = currentLocation->info->getAreaNumber();

                    if (actar == 0 || actar == currentArea)
                    {
                        cout << cur->getActiveMessage() << endl;
                        vector<Effect*> effects = cur->getItemConsumeEffects();
                        for (Effect* e : effects)
                        {
                            applyEffect(e);
                        }
                        items.deleteNode(temp->info);
                    }
                    else
                    {
                        cout << "That item cannot be consumed here." << endl;
                    }
                }
            }
            else
            {
                temp = temp->link;
            }
        }
        if (!found)
        {
            cout << "No item by that name in your inventory." << endl;
        }
    }
}

//---------------------------------------------------------------------------
/* use() allows an item to be used by the player.
*/
void CombatPlayer::use(string itemName, Map* mapptr)
{
    string n = itemName;

    nodeType<Item*>* temp = NULL;
    temp = items.getFirst();

    if(temp == NULL)
    {
        cout << "You have no items in your inventory." << endl;
    }
    else
    {
        bool found = false;
        while (temp != NULL && !found)
        {
            if (n == temp->info->getName())
            {
                found = true;
                UseItem* cur = dynamic_cast<UseItem*>(temp->info);
                if (!cur)
                {
                    cout << "That item is not usable." << endl;
                }
                else
                {
                    int actar = cur->getActiveArea();
                    // int currentArea = mapptr->reverseLookUp(getCurrent());

                    int currentArea = currentLocation->info->getAreaNumber();

                    if (actar == 0 || actar == currentArea)
                    {
                        cout << cur->getActiveMessage() << endl;
                        vector<Rule*> rules = cur->getItemUseRules();
                        MapV2* mapv2 = static_cast<MapV2*>(mapptr);
                        for (Rule* r : rules)
                        {
                            mapv2->applyRule(r);
                        }
                        items.deleteNode(temp->info);
                    }
                    else
                    {
                        cout << "That item cannot be used here." << endl;
                    }
                }
            }
            else
            {
                temp = temp->link;
            }
        }
        if (!found)
        {
            cout << "No item by that name in your inventory." << endl;
        }
    }
}

//---------------------------------------------------------------------------
/* equip() allows players to equip a weapon from their inventory.
*/
void CombatPlayer::equip(string itemName)
{
    string n = itemName;

    nodeType<Item*>* temp = NULL;
    temp = items.getFirst();

    if(temp == NULL)
    {
        cout << "You have no items in your inventory." << endl;
    }
    else
    {
        bool found = false;
        while (temp != NULL && !found)
        {
            if (n == temp->info->getName())
            {
                found = true;
                BattleItem* cur = dynamic_cast<BattleItem*>(temp->info);
                if (!cur)
                {
                    cout << "That item is not a weapon." << endl;
                }
                else
                {
                    equippedWeapon = temp->info;
                    cout << "You have equipped: " << equippedWeapon->getName()
                        << endl;
                }
            }
            else
            {
                temp = temp->link;
            }
        }
        if (!found)
        {
            cout << "No item by that name in your inventory." << endl;
        }
    }
}

//---------------------------------------------------------------------------
/* attack() attacks an enemy if it is present in the area and handles the
* removing of an enemy when it dies.
*/
void CombatPlayer::attack(string enemyName)
{
    string n = enemyName;

    areaNode* curArea = getCurrent();
    nodeType<Enemy*>* e = curArea->info->enemies.getFirst();
    Enemy* target = nullptr;

    while (e != nullptr)
    {
        if (e->info->getName() == n)
        {
            target = e->info;
            break;
        }
        e = e->link;
    }

    if (!target)
    {
        cout << "No enemy by that name here" << endl;
    }
    else if (equippedWeapon != nullptr)
    {
        int damageToEnemy = calcPlayerDamage();
        target->takeDamage(damageToEnemy);
        cout << "You attacked " << target->getName() << ", dealing " <<
            damageToEnemy << " damage!" << endl;

        if (target->isDead())
        {
            cout << "You defeated " << target->getName() << "!" << endl;

            // delete enemy from area
            nodeType<Enemy*>* current = curArea->info->enemies.getFirst();
            while (current != nullptr)
            {
                if (current->info == target)
                {
                    delete target;
                    curArea->info->enemies.deleteNode(target);
                }

                current = current->link;
            }
        }
        else
        {
            int damageToPlayer = calcEnemyDamage(target->getDamage());
            hitPoints -= damageToPlayer;
            cout << target->getName() << " hit you, dealing " <<
                damageToPlayer << " damage!" << endl;
        }
    }
    else
    {
        cout << "You cannot attack without a weapon equipped." << endl;
    }
}

//---------------------------------------------------------------------------
/* applyEffect() is a helper function that takes the effects for a given item
* once consumed and applies those effects to the player's stats, either
* increasing or decreasing HP, SP, attack, or defense.
*/
void CombatPlayer::applyEffect(Effect* e)
{
    int id = e->effectID;
    int amount = e->effectAmt;
    switch (id)
    {
        case 0: // negative hp
            hitPoints -= amount;
            cout << "You lost " << amount << " HP." << endl;
            break;
        case 1: // positive hp
            hitPoints += amount;
            cout << "You gained " << amount << " HP." << endl;
            break;
        case 2: // negative sp
            sanityPoints -= amount;
            cout << "You lost " << amount << " sanity." << endl;
            break;
        case 3: // positive sp
            sanityPoints += amount;
            cout << "You gained " << amount << " sanity." << endl;
            break;
        case 4: // negative attack
            attackStat -= amount;
            cout << "You lost " << amount << " attack." << endl;
            break;
        case 5: // positive attack
            attackStat += amount;
            cout << "You gained " << amount << " attack." << endl;
            break;
        case 6: // negative defense
            defenseStat -= amount;
            cout << "You lost " << amount << " defense." << endl;
            break;
        case 7: // positive defense
            defenseStat += amount;
            cout << "You gained " << amount << " defense." << endl;
            break;
        default: // any other value (this should not happen)
            cout << "Unknown effect ID: " << id << endl;
    }
}

//---------------------------------------------------------------------------
/* multiplier() rolls a random value from 1-16 and uses that value to randomly
* calculate how much damage the player or enemy will do to each other by
* converting that value into a decimal for 85-100% of damage.
*/
double CombatPlayer::multiplier()
{
    int roll = rand() % 16; // roll a random value from 0 to 15
    return 0.85 + ((roll / 15.0) * 0.15); // returns value from 0.85 to 1.00
                                          // representing 85-100% of possible damage
}

//---------------------------------------------------------------------------
/* calcPlayerDamage() calculates the amount of damage the player deals to the
* enemy when the player attacks.
*/
int CombatPlayer::calcPlayerDamage()
{
    double baseDamage = attackStat + equippedWeapon->getDamage();
    double damageMultiplier = multiplier();
    int totalDamage = static_cast<int>(baseDamage * damageMultiplier);
    if (totalDamage < 1) // ensure player will always deal at least 1 HP of damage
    {
        totalDamage = 1;
    }
    return totalDamage;
}

//---------------------------------------------------------------------------
/* calcEnemyDamage() calculates the amount of damage the enemy deals to the
* player when the player attacks.
*/
int CombatPlayer::calcEnemyDamage(int baseDamage)
{
    const double BALANCE = defenseStat * 0.4; // for if defense gets really high
    double damage = baseDamage - BALANCE;
    double minDamage = baseDamage * 0.15;

    // Ensure some meaningful amount of base damage before running through multiplier()
    if (damage < minDamage)
    {
        damage = minDamage;
    }

    double damageMultiplier = multiplier();
    int totalDamage = static_cast<int>(damage * damageMultiplier);
    if (totalDamage < 1)
    {
        totalDamage = 1;
    }
    return totalDamage;
}

//void updateStat Description
/********************************************************
Purpose:  Updates player's stats
Incoming: Event* event
Outgoing: Nothing
**********************************************************/
void CombatPlayer::updateStat(Event* event)
{
    int posOrNeg = event->eventID;
    int updateStat = event->statChange;
    char stat = event->effectedStat;

    if (posOrNeg == 1)	//Positive update
    {
        if (stat == 'h')
        {
            hitPoints += updateStat;
        }
        else if (stat == 's')
        {
            sanityPoints += updateStat;
        }
        else if (stat == 'a')
        {
            attackStat += updateStat;
        }
        else if (stat == 'd')
        {
            defenseStat += updateStat;
        }
    }
    else if (posOrNeg == 0)	//Negative update
    {
        if (stat == 'h')
        {
            hitPoints -= updateStat;
        }
        else if (stat == 's')
        {
            sanityPoints -= updateStat;
        }
        else if (stat == 'a')
        {
            attackStat -= updateStat;
        }
        else if (stat == 'd')
        {
            defenseStat -= updateStat;
        }
    }
}
