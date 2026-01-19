#include <iostream>

#include "Game.h"

//---------------------------------------------------------------------------
/* Default constructor for the Game class. Builds the map from the IFD file
* and sets the player to the beginning location of the map.
*/
Game::Game()
{
    map.buildMap();

    player1 = map.getPlayer();

    player1->setCurrent(map.getStart());
}

//---------------------------------------------------------------------------
/* trim() removes leading and trailing whitespace from a string.
*/
string Game::trim(const string& str) {
    size_t first = str.find_first_not_of(" \t");
    size_t last = str.find_last_not_of(" \t");
    return (first == string::npos) ? "" : str.substr(first, last - first + 1);
}

//---------------------------------------------------------------------------
/* The play() function handles a large majority of gameplay aspects of the
* engine
*/
void Game::play()
{
    string userInput;
    cin.ignore();
    bool directionalInput = false;

    while (true)
    {
        // check game status
        if (player1->isGameOver() != 0)
        {
            player1->getCurrent()->info->displayArea();
            return;
        }

        // display area data
        if (player1->playerMoved())
        {
            player1->getCurrent()->info->displayArea();
            if (player1->getCurrent()->info->getActiveMessage() == "rest")
            {
                cout << player1->getCurrent()->info->getActiveMessage() << endl;
            }
            if (player1->getCurrent()->info->getType() == "event")
            {
                if (bool entered = player1->getCurrent()->info->onEnter(player1)) {}
            }
        }
        else
        {
            if (directionalInput)
            {
                cout << "There appears to be no way to go that direction." << endl;
            }
            else
            {
                player1->getCurrent()->info->displayArea();
            }
        }


        // get movement selection
        cout << "Which way would you like to go?  Enter u, d, l, or r" << endl;
        getline(cin, userInput);
        stringstream ss(userInput);
        string command;
        ss >> command;

        string itemName;
        getline(ss, itemName); // get the rest of the line
        itemName = trim(itemName); // remove leading/trailing spaces

        // update area
        if (command == "u")
        {
            directionalInput = true;
            player1->setCurrent(player1->getCurrent()->u);
        }
        else if (command == "d")
        {
            directionalInput = true;
            player1->setCurrent(player1->getCurrent()->d);
        }
        else if (command == "l")
        {
            directionalInput = true;
            player1->setCurrent(player1->getCurrent()->l);
        }
        else if (command == "r")
        {
            directionalInput = true;
            player1->setCurrent(player1->getCurrent()->r);
        }
        else if (command == "iseedeadpeople") // cheat code to reveal map
        {
            // map.print();
            directionalInput = false;
            cout << map;
        }
        else if (command == "exit" || command == "Exit") // immediately end game
        {
            cout << "Good bye!" << endl;
            return;
        }
        else if (command == "help" || command == "Help")
        {
            directionalInput = false;
            cout << "You may type: " << endl;
            cout << "\t u, d, l, or r: to move up, down, left or right on the map." << endl;
            cout << "\t reset: to reset the game." << endl;
            cout << "\t exit: to exit the game." << endl;
            cout << "\t search: to search the area for items." << endl;
            cout << "\t inventory: to view your inventory." << endl;
            cout << "\t take: to take an item from the area you are in and add it to your inventory." << endl;
            cout << "\t leave: to leave an item from your inventory in the current area." << endl;
            cout << "\t examine: to examine an item in your inventory." << endl;
            cout << "\t use: to use an item from your inventory." << endl;
            cout << "\t consume: to consume an item from your inventory." << endl;
            cout << "\t stats: to show player statistics (if available)." << endl;
            cout << "\t rest: to reset player's Stats." << endl;
            cout << "\t equip: to equip an item from your inventory." << endl;
            cout << "\t attack: to attack an enemy in the current area." << endl;
            cout << "\t enemies: to see all enemies in the current area." << endl;
            cout << endl;
        }
        else if (command == "reset" || command == "Reset")
        {
            directionalInput = false;
            cout << "Resetting game" << endl;
            resetGame();
        }
        else if (command == "search" || command == "scan" || command == "scan room"
                || command == "Search" || command == "Scan" || command == "Scan Room" ||
                command == "Scan room")
        {
            directionalInput = false;
            player1->getCurrent()->info->search();
        }
        else if (command == "inventory" || command == "check inventory" ||
                 command == "Inventory" || command == "Check Inventory" ||
                 command == "Check inventory")
        {
            directionalInput = false;
            player1->inventory();
        }
        else if (command == "take" || command == "get" || command == "grab"
                || command == "Take" || command == "Get" || command == "Grab")
        {
            directionalInput = false;
            player1->take(itemName);
        }
        else if (command == "leave" || command == "drop" || command == "discard"
                || command == "Leave" || command == "Drop" || command == "Discard")
        {
            directionalInput = false;
            player1->leave(itemName);
        }
        else if (command == "examine" || command == "inspect" || command == "look at"
                || command == "Examine" || command == "Inspect" ||
                command == "Look at" || command == "Look At")
        {
            directionalInput = false;
            player1->examine(itemName);
        }
        else if (command == "use" || command == "employ" || command == "wield"
                 || command == "operate" || command == "Use" ||
                 command == "Employ" || command == "Wield" || command == "Operate")
        {
            directionalInput = false;
            player1->use(itemName, &map);
        }
        else if (command == "consume" || command == "eat" || command == "swallow"
                 || command == "ingest" || command == "digest" || command == "Consume"
                 || command == "Eat" || command == "Swallow" || command == "Ingest"
                 || command == "Digest")
        {
            directionalInput = false;
            player1->consume(itemName);
        }
        else if (command == "stats" || command == "show my stats" || command == "show player stats"
                || command == "Stats" || command == "Show my stats" ||
                command == "Show player stats" || command == "Show My Stats" ||
                command == "Show Player Stats")
        {
            directionalInput = false;
            player1->reportStats();
        }
        else if (command == "rest" || command == "recover" || command == "Rest"
                 || command == "Recover")
        {
            directionalInput = false;
            if (player1->getCurrent()->info->getType() !=  "rest")
            {
                cout << "WAKE UP, YOU CAN NOT REST HERE!" << endl;
            }
            else
            {
                bool didPlayerRest = player1->getCurrent()->info->onEnter(player1);
            }
        }
        else if (command == "equip" || command == "Equip")
        {
            directionalInput = false;
            player1->equip(itemName);
        }
        else if (command == "attack" || command == "strike" || command == "Attack"
                 || command == "Strike")
        {
            directionalInput = false;
            player1->attack(itemName);
        }
        else if (command == "enemies" || command == "foes" || command == "opponents" ||
                 command == "Enemies" || command == "Foes" || command == "Opponents")
        {
            directionalInput = false;
            player1->getCurrent()->info->listEnemies();
        }
        else // any other invalid input
        {
            directionalInput = false;
            cout << "I do not understand: " << userInput << endl << endl;
        }
    } // end while
} // end play()

//---------------------------------------------------------------------------
/* resetGame() clears the player's inventory, resets all items back to their
* original location, and then resets the Player object.
*/
void Game::resetGame()
{
    player1->items.destroyList();
    map.resetItems();

    // reset player object to avoid the "There appears to be no way to
    // go that direction" message if you reset in Area 1.
    player1->resetPlayerStats();
    player1->setCurrent(map.getStart());
}
