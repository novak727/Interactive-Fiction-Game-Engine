#include <iostream>

#include "Player.h"

using namespace std;

//---------------------------------------------------------------------------
/* Default constructor, setting both pointers to NULL since no movement will
* have been made at the beginning of the game.
*/
Player::Player()
{
    lastLocation = NULL;
    currentLocation = NULL;
}

//---------------------------------------------------------------------------
/* setCurrent() sets the player's previous location and the current location
* they are in.
*/
void Player::setCurrent(areaNode* loc)
{
    lastLocation = currentLocation;
    currentLocation = loc;
}

//---------------------------------------------------------------------------
/* playerMoved() checks whether or not the player successfully changed location
* and returns the result of that check.
*/
bool Player::playerMoved()
{
    return !(lastLocation == currentLocation);
}

//---------------------------------------------------------------------------
/* getCurrent() returns the current location of the player.
*/
areaNode* Player::getCurrent()
{
    return currentLocation;
}

//---------------------------------------------------------------------------
/* inventory() lists out each item in the player's inventory, or states there
* are no items in the inventory if the player's inventory is empty.
*/
void Player::inventory()
{
    nodeType<Item*>* temp;
    temp = items.getFirst();
    //cout<<temp<<endl;
    if(temp == NULL)
    {
        cout << "No items are in your inventory." << endl;
    }
    else
    {
        cout << "You have the following items:" << endl;
        while(temp != NULL)
        {
            cout << "\t" << temp->info->getName() << endl;
            temp = temp->link;
        }
    }
}

//---------------------------------------------------------------------------
/* take() allows the user to take an item in an area and add it to their
* inventory. If no item in the area matches the entry from the user, that will
* be stated if there are items present in the area. If no items are in the area,
* that will be printed instead.
*/
void Player::take(string itemName)
{
    string n = itemName;
    //cout<<"Looking for item: "<<n<<endl;
    nodeType<Item*>* temp = NULL;
    temp = currentLocation->info->items.getFirst();
    //cout<<temp<<endl;
    if(temp == NULL)
    {
        cout << "No items are in this room to take." << endl;
    }
    else
    {
        bool found = false;
        while(temp != NULL && !found)
        {
            if(n == temp->info->getName())
            {
                found = true;
                //add to player list
                items.insertLast(temp->info);
                //delete from room list
                currentLocation->info->items.deleteNode(temp->info);
            }
            else
            {
                temp = temp->link;
            }
        }
        if(found)
        {
            cout << "You have taken: " << n << endl;
        }
        else
        {
            cout << "No item by that name here." << endl;
        }
    }
}

//---------------------------------------------------------------------------
/* leave() allows the player to leave an item from their inventory in the
* current area they are in. If no item matches the item entry from the player,
* then that will be stated, as well as if the player's inventory is empty.
*/
void Player::leave(string itemName)
{
    string n = itemName;
    //cout<<"Looking for item: "<<n<<endl;
    nodeType<Item*>* temp = NULL;
    temp = items.getFirst();
    //cout<<temp<<endl;
    if(temp == NULL)
    {
        cout << "You have no items in your inventory." << endl;
    }
    else
    {
        bool found = false;
        while(temp != NULL && !found)
        {
            if(n == temp->info->getName())
            {
                found = true;
                // add to room list
                currentLocation->info->items.insertLast(temp->info);
                // delete from player list
                items.deleteNode(temp->info);
            }
            else
            {
                temp = temp->link;
            }
        }
        if(found)
        {
            cout << "You have dropped: " << n << endl;
        }
        else
        {
            cout << "No item by that name in your inventory." << endl;
        }
    }
}

//---------------------------------------------------------------------------
/* examine() allows the player to examine an item in their inventory, printing
* the description of the item entered by the user, or says there is no item
* with that name in their inventory if the input doesn't match any item. If the
* inventory is empty, it will be printed instead.
*/
void Player::examine(string itemName)
{
    string n = itemName;
    // cout<<"Looking for item: "<<n<<endl;
    nodeType<Item*>* temp = NULL;
    temp = items.getFirst();
    // cout<<temp<<endl;
    if(temp == NULL)
    {
        cout << "You have no items in your inventory to examine." << endl;
    }
    else
    {
        bool found = false;
        while(temp != NULL && !found)
        {
            if(n == temp->info->getName())
            {
                found = true;
                // display item description
                cout << temp->info->getDesc() << endl;
            }
            else
            {
                temp = temp->link;
            }
        }
        if(!found)
        {
            cout << "No item by that name in your inventory." << endl;
        }
    }
}

//---------------------------------------------------------------------------
/* equip() prints an error message since only combat player types equip
* weapons.
*/
void Player::equip(string itemName)
{
    cout << "You cannot equip weapons in this player mode." << endl;
}

//---------------------------------------------------------------------------
/* attack() prints an error message since only combat player types attack
* enemies.
*/
void Player::attack(string enemyName)
{
    cout << "You cannot attack in this player mode." << endl;
}

//void updateStat Description
/********************************************************
Purpose:  Event* event
Incoming: Nothing
Outgoing: Nothing
**********************************************************/
void Player::updateStat(Event* event)
{
    cout << "Baisc Player's stats can not change" << endl;
}
