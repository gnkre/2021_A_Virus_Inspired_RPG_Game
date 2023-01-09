#ifndef ENEMY_H_INCLUDED
#define ENEMY_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Player.h"

using namespace std;
class Monster;
class Boss : public GameCharacter
{
public:
    vector<Monster*> every;
    string pixels[19];
    Boss(vector<Monster*> ever);
    Boss(int hp, vector<Monster*> ever);
    void unlockAll();
    bool triggerEvent(Object* obj_in);
    void drawBoss();
    
};
class Monster : public GameCharacter
{
public:
    string real_name;
    bool is_infected;
    string pixels[7];
public:

    Monster();
    Monster(bool is_infected, string real_name_in, string name_in, int atk_in, int def_in, int max_hp_in);
    bool checkIfIsDead();
    /* Virtual function that you need to complete   */
    /* In Monster, this function should deal with   */
    /* the combat system.                           */
    bool triggerEvent(Object* obj_in);
    void drawMonster();
    void updateMonsterAppearence();
    void unlock();
};


#endif // ENEMY_H_INCLUDED
