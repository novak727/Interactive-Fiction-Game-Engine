#ifndef H_game
#define H_game

#include "MapV2.h"
#include "Area.h"
#include "Player.h"
#include "Item.h"

//---------------------------------------------------------------------------
/* Game
* This class handles the gameplay aspects of the IF game.
* A Player and Map object are created to handle the player actions and the
* creation of the map from the IFD file.
* A default constructor and a play function have been defined that call on
* the Player and Map classes to assist with gameplay.
*/
class Game
{
    public:
        Game();
        void play();
        void resetGame();
        string trim(const string&);

	private:
        Player* player1;
        MapV2 map;
};

#endif // GAME_H
