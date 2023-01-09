#ifndef GAMECHARACTER_H_INCLUDED
#define GAMECHARACTER_H_INCLUDED

#include <iostream>
#include <string>
#include "Object.h"
using namespace std;

class GameCharacter : public Object
{
public:
    string name;
    int maxHealth;
    int currentHealth;
    int attack;
    int defense;
public:
    GameCharacter();
    GameCharacter(string name, string tag, int max_hp_in, int atk_in, int def_in);
    bool checkIsDead();
    int takeDamage(int damage_in); // return cur hp

    /* Set & Get function*/
    void setMaxHealth(int max_hp_in);
    void setCurrentHealth(int cur_hp_in);
    void setAttack(int atk_in);
    void setDefense(int def_in);
    int getMaxHealth();
    int getCurrentHealth();
    int getAttack();
    int getDefense();
};
#endif // GAMECHARACTER_H_INCLUDED
