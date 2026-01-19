#ifndef H_enemy
#define H_enemy

#include <string>

using namespace std;

//---------------------------------------------------------------------------
/* Enemy
* This class declares enemies that can be attacked by players. Getters and
* setters are present for all attributes, along with a default constructor, a
* function to print the enemy's name and current HP, and functions to handle
* damage.
*/
class Enemy
{
    public:
        Enemy();
        void setName(string);
        string getName() const;
        void displayName() const;
        void setHP(int);
        int getHP() const;
        void takeDamage(int);
        bool isDead();
        void setDamage(int);
        int getDamage() const;
        void setActiveArea(int);
        int getActiveArea() const;
    private:
        string name;
        string description;
        int hp;
        int damage;
        int activeArea;
};

#endif // H_enemy
