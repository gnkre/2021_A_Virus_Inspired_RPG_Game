#ifndef NPC_H_INCLUDED
#define NPC_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Item.h"
#include "GameCharacter.h"

#include "Player.h"

/*
                ,-.
               |* *|
                \-/   ;/_
               /\v/\_//'
              || | .-'
              || |u|
              ('_|_|
               | | |
             _,|_|_|,_
            / (_,|,_) \
           /___________\
           |___________|
            |Developer|
            |  ERIK   |
            |   NING  |
           /|_________|\
          /_____________\
          |_____________|
*/
using namespace std;
class Statue : public Object
{
public:
    Statue();
    string appear[18];
    bool triggerEvent(Object* obj_in);
};
class NPC : public GameCharacter
{
public:
    string script[5];
    vector<Item> commodity;

public:
    NPC();
    NPC(string name_in, int index);
    void listCommodity(int cursor); /*print all the Item in this NPC*/
    string pixels[7];
    void buyDaItem(int cursor, Player* plr_in);
    /* Virtual function that you need to complete   */
    /* In NPC, this function should deal with the   */
    /* transaction in easy implementation           */
    bool triggerEvent(Object*);
    void drawNPC();
    /* Set & Get function*/
    void setScript(string);
    void setCommodity(vector<Item>);
    string getScript();
    vector<Item> getCommodity();
    
};


#endif // NPC_H_INCLUDED
