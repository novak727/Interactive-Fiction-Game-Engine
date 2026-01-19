#include "HPSPPlayer.h"
#include "UseItem.h"
#include "ConsumeItem.h"
#include "MapV2.h"

#include <iostream>
#include <string>
#include <vector>

using namespace std;

//---------------------------------------------------------------------------
/* Constructor for HPSP Players, setting hitPoints and sanityPoints to 100
*/
HPSPPlayer::HPSPPlayer()
{
    hitPoints = 100;
    sanityPoints = 100;
}

//---------------------------------------------------------------------------
/* isGameOver() returns one of 3 value depending on if the game continues (0),
* the player won (1), or the player lost (2).
*/
int HPSPPlayer::isGameOver()
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
/* resetPlayerStats() resets the HP and SP values back to 100.
*/
void HPSPPlayer::resetPlayerStats()
{
    hitPoints = 100;
    sanityPoints = 100;
}

//---------------------------------------------------------------------------
/* reportStats() prints out the current HP and SP values.
*/
void HPSPPlayer::reportStats()
{
    cout << "\t HP: " << hitPoints << endl;
    cout << "\t SP: " << sanityPoints << endl;
}

//---------------------------------------------------------------------------
/* consume() allows a Player to consume an item from their inventory, presuming
* it exists in the inventory.
*/
void HPSPPlayer::consume(string itemName)
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
void HPSPPlayer::use(string itemName, Map* mapptr)
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
/* applyEffect() is a helper function that takes the effects for a given item
* once consumed and applies those effects to the player's stats, either
* increasing or decreasing HP or SP.
*/
void HPSPPlayer::applyEffect(Effect* e)
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
        case 4: // negative attack, do nothing
            break;
        case 5: // positive attack, do nothing
            break;
        case 6: // negative defense, do nothing
            break;
        case 7: // positive defense, do nothing
            break;
        default: // any other value (this should not happen)
            cout << "Unknown effect ID: " << id << endl;
    }
}

//void updateStat Description
/********************************************************
Purpose:  Updates player's stats
Incoming: Event* event
Outgoing: Nothing
**********************************************************/
void HPSPPlayer::updateStat(Event* event)
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
    }
}
