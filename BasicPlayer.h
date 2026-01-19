#ifndef H_basicplayer
#define H_basicplayer

#include "Map.h"
#include "Player.h"

//---------------------------------------------------------------------------
/* BasicPlayer
* This class derives from Player, implementing the different methods to handle
* player stats and use/consume item types. The method to check if the game is
* over is also implemented due to its difference between different player
* types.
*/
class BasicPlayer : public Player
{
    public:
        int isGameOver();
        void resetPlayerStats();
        void reportStats();
        void consume(string);
        void use(string, Map*);
};

#endif // H_basicplayer
