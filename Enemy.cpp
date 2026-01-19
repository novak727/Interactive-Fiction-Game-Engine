#include "Enemy.h"

#include <iostream>

//---------------------------------------------------------------------------
/* Constructor for Enemy class.
*/
Enemy::Enemy()
{
    name = "";
    description = "";
    hp = 1;
    damage = 0;
    activeArea = -1;
}

//---------------------------------------------------------------------------
/* setName() sets the name of the enemy.
*/
void Enemy::setName(string n)
{
    name = n;
}

//---------------------------------------------------------------------------
/* getName() returns the name of the enemy.
*/
string Enemy::getName() const
{
    return name;
}

//---------------------------------------------------------------------------
/* displayName() prints out the name of the enemy to console.
*/
void Enemy::displayName() const
{
    cout << name << " (HP: " << hp << ")" << endl;
}

//---------------------------------------------------------------------------
/* setHP() sets the HP of the enemy.
*/
void Enemy::setHP(int val)
{
    hp = val;
}

//---------------------------------------------------------------------------
/* getHP() returns the HP of the enemy.
*/
int Enemy::getHP() const
{
    return hp;
}

//---------------------------------------------------------------------------
/* takeDamage() subtracts the amount of damage dealt by the player from the
* enemies HP.
*/
void Enemy::takeDamage(int dmg)
{
    hp -= dmg;
}

//---------------------------------------------------------------------------
/* isDead() checks if the enemy's HP is 0 or less and returns the result as
* true or false.
*/
bool Enemy::isDead()
{
    return (hp <= 0);
}

//---------------------------------------------------------------------------
/* setDamage() sets the amount of damage the enemy does to the player when
* it attacks the player.
*/
void Enemy::setDamage(int d)
{
    damage = d;
}

//---------------------------------------------------------------------------
/* getDamage() returns the amount of damage the enemy does to the player when
* it attacks the player.
*/
int Enemy::getDamage() const
{
    return damage;
}

//---------------------------------------------------------------------------
/* setActiveArea() sets the area the enemy appears in.
*/
void Enemy::setActiveArea(int a)
{
    activeArea = a;
}

//---------------------------------------------------------------------------
/* getActiveArea() returns the area the enemy appears in.
*/
int Enemy::getActiveArea() const
{
    return activeArea;
}
