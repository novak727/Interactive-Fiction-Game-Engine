#ifndef H_mapv2
#define H_mapv2

#include <vector>
#include <string>

#include "Map.h"
#include "UseItem.h"
#include "ConsumeItem.h"
#include "BattleItem.h"
#include "areaNode.h"
#include "Area.h"
#include "IFDParser.h"
#include "LinkData.h"
#include "BasicPlayer.h"
#include "HPSPPlayer.h"
#include "CombatPlayer.h"
#include "Enemy.h"
#include "Player.h"
#include "Item.h"
#include "ull.h"
#include "basicArea.h"
#include "restArea.h"
#include "eventArea.h"

using namespace std;

//---------------------------------------------------------------------------
/* MapV2
* Derived from the Map class, this class includes the ability to add items into
* the IF Game.
* In addition to the inherited attributes from Map, a vector has been added to
* store the pointers to item objects.
* The buildMap routine has been overloaded to include items in the Map, and
* appropriate methods have been added to build the items, set the items to
* their starting areas, and reset all items back to their starting positions.
* The Map now also handles the creation of players with the implementation of
* different player types, as well as applying rules when an item that affects
* the game map is used.
*/
class MapV2 : public Map
{
    public:
        void buildMap();
        void makeEventArea();
        void makeRestArea();
        void makeArea();
        void makeItem();
        void makeUseItem();
        void makeConsumeItem();
        void makeBattleItem();
        void insertItems();
        void resetItems();
        void makePlayer(const string);
        Player* getPlayer();
        void makeEnemy();
        void insertEnemies();
        void applyRule(Rule*);
        friend ostream& operator<<(ostream&, MapV2&);
    private:
        vector<Item*> itemsVec;
        vector<Enemy*> enemiesVec;
        Player* playerPtr;
};

#endif // H_mapv2
