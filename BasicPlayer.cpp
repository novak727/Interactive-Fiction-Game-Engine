#include <iostream>

#include "BasicPlayer.h"
#include "UseItem.h"
#include "ConsumeItem.h"
#include "MapV2.h"

using namespace std;

//---------------------------------------------------------------------------
/* isGameOver() returns one of 3 value depending on if the game continues (0),
* the player won (1), or the player lost (2).
*/
int BasicPlayer::isGameOver()
{
    if (currentLocation->info->getGoal())
    {
        return 1;
    }
    else if (currentLocation->info->getID())
    {
        return 2;
    }
    else
    {
        return 0;
    }
}

//---------------------------------------------------------------------------
/* resetPlayerStats() does nothing.
*/
void BasicPlayer::resetPlayerStats()
{
    // Do nothing, no stats to reset
}

//---------------------------------------------------------------------------
/* reportStats() prints out that there are no stats to report for a basic
* player type.
*/
void BasicPlayer::reportStats()
{
    cout << "No player statistics to report" << endl;
}

//---------------------------------------------------------------------------
/* consume() allows a Player to consume an item from their inventory, presuming
* it exists in the inventory.
*/
void BasicPlayer::consume(string itemName)
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
                    // int currentArea = mapptr->reverseLoopUp(getCurrent());

                    int currentArea = currentLocation->info->getAreaNumber();

                    if (actar == 0 || actar == currentArea)
                    {
                        cout << cur->getActiveMessage() << endl;
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
void BasicPlayer::use(string itemName, Map* mapptr)
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
