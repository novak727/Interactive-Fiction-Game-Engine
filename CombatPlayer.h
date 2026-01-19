#ifndef H_combatplayer
#define H_combatplayer

#include "Map.h"
#include "BattleItem.h"
#include "Enemy.h"
#include "Item.h"
#include "Player.h"
#include "eventArea.h"

//---------------------------------------------------------------------------
/* CombatPlayer
* This is a new player type derived from the base Player class, which allows
* players to attack enemies. This player still has HP and SP, but now also has
* an attack and defense stat, along with the ability to equip a weapon. There
* are various functions to handle damaging both the player and the enemy as
* well.
*/
class CombatPlayer : public Player
{
    public:
        CombatPlayer();
        int isGameOver();
        void resetPlayerStats();
        void reportStats();
        void consume(string);
        void use(string, Map*);
        void equip(string);
        void attack(string);
        void updateStat(Event*);

    private:
        int hitPoints;
        int sanityPoints;
        int attackStat;
        int defenseStat;
        Item* equippedWeapon;
        void applyEffect(Effect*);
        double multiplier();
        int calcPlayerDamage();
        int calcEnemyDamage(int);
};

#endif // H_combatplayer
