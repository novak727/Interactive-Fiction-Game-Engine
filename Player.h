#ifndef H_player
#define H_player

#include "areaNode.h"
#include "Item.h"
#include "ull.h"
#include "Map.h"

//---------------------------------------------------------------------------
/* Player
* This class defines information about the player and actions that can be
* taken, checking whether or not actions worked successfully based on the
* current and previous area of the player.
* Two areaNode pointers are created to reference the current location and the
* previous location of the player. These are private attributes. A linked list
* of items for the player is also added as a public attribute to keep up with
* the player's inventory.
* Methods are created to set the location the player is in, whether or not the
* player moved successfully, a check for if the game is over and how it ended,
* and a way to get the player's current location. The player also now has an
* inventory, with routines to allow the player to view their inventory, examine
* items in their inventory, and take/leave items in the area they are
* currently in.
* There are also methods for interfacing with different Item types and player
* stats.
*/
class Player
{
    public:
        uLList<Item*> items;

        Player();
        void setCurrent(areaNode*);
        bool playerMoved();
        areaNode* getCurrent();
        void inventory();
        void take(string);
        void leave(string);
        void examine(string);

        virtual int isGameOver() = 0;
        virtual void resetPlayerStats() = 0;
        virtual void reportStats() = 0;
        virtual void consume(string) = 0;
        virtual void use(string, Map*) = 0;

        virtual void equip(string);
        virtual void attack(string);

        virtual void updateStat(Event*);

    protected:
        areaNode* currentLocation;
        areaNode* lastLocation;
};

#endif // H_player
