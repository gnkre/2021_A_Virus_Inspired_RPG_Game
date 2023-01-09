#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
//#include "Dungeon.h"
#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"


using namespace std;

class Item;
class Room;


class Player : public GameCharacter
{
    struct Ability
    {
        string name_of_ability = "NULL";
        int weight_attack = 0;
        int higher_player_def = 0;
        int higher_player_attack = 0;
    };
public:
    int does_player_has_all_abilities;
    Ability abilities[4];
    Room* currentRoom;
    Room* previousRoom;
    string room_going_to;
    vector<Room>* room_of_plr;
    vector<Item> inventory;
    Item head;
    Item left_hand;
    Item right_hand;
    Item body;
    int o_ka_ne;
    string appear[9];
    string appear_front[9];
public:
    Player();
    int player_room_X;
    int player_room_Y;
    int deal_X;
    int deal_Y;
    Player(string name_in, int atk_in, int def_in,int hp, int max_hp_in);
    //void addItem(Item);
    void increaseStates(int atk_in, int def_in, int max_hp_in);
    void changeRoom(Room* next);
    void updatePlayerAppear();
    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool triggerEvent(Object* obj_in);
    void drawPlayer();
    /* Set & Get function*/
    void setCurrentRoom(Room* cur_room_in);
    void setPreviousRoom(Room* prev_room_in);
    bool setRoomXY(int x, int y);
    void setInventory(vector<Item> inventory_in);
    Room* getCurrentRoom();
    char showStatus(int cursor);
    Room* getPreviousRoom();
    vector<Item> getInventory();
    void checkIfPlayerIsDead();
};

#endif // PLAYER_H_INCLUDED
