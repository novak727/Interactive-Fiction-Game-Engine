#ifndef H_hpspplayer
#define H_hpspplayer

#include "Map.h"
#include "Player.h"
#include "eventArea.h"

//---------------------------------------------------------------------------
/* HPSPPlayer
* This class derives from Player, implementing the different methods to handle
* player stats and use/consume item types. The method to check if the game is
* over is also implemented due to its difference between different player
* types.
* This class also has two attributes to track player hit points and sanity
* points, which will be modified by the appropriate methods. This class also
* has a constructor to set the initial values of this class.
*/
class HPSPPlayer : public Player
{
    public:
        HPSPPlayer();
        int isGameOver();
        void resetPlayerStats();
        void reportStats();
        void consume(string);
        void use(string, Map*);
        void updateStat(Event*);
    private:
        int hitPoints;
        int sanityPoints;
        void applyEffect(Effect*);
};

#endif // H_hpspplayer
