#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
//#include "Player.h"
using namespace std;

class Player;

class Item : public Object
{
public:
    int health, attack, defense, value;
public:
    Item();
    Item(string name_in, int atk_in, int def_in, int hp_in, int value_in);

    /* Virtual function that you need to complete    */
    /* In Item, this function should deal with the   */
    /* pick up action. You should add status to the  */
    /* player.                                       */
    bool triggerEvent(Object* obj_in);
    bool interactwith(Player* plr_in);
    /* Set & Get function*/
    int getHealth();
    int getAttack();
    int getDefense();
    void setHealth(int hp_in);
    void setAttack(int atk_in);
    void setDefense(int def_in);
};  

#endif // ITEM_H_INCLUDED
