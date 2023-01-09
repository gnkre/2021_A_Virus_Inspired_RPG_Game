#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "GameCharacter.h"
#include "Room.h"
#include "Item.h"

using namespace std;

class Item;

class Player : public GameCharacter
{
private:
    Room* currentRoom;
    Room* previousRoom;
    int player_room_X;
    int player_room_Y;
    vector<Item> inventory;
public:
    Player();
    Player(string name_in, int atk_in, int def_in, int max_hp_in);
    void addItem(Item);
    void increaseStates(int atk_in, int def_in, int max_hp_in);
    void changeRoom(Room* next);

    /* Virtual function that you need to complete   */
    /* In Player, this function should show the     */
    /* status of player.                            */
    bool triggerEvent(Object* obj_in);

    /* Set & Get function*/
    void setCurrentRoom(Room* cur_room_in);
    void setPreviousRoom(Room* prev_room_in);
    void setRoomXY(int x, int y);
    void setInventory(vector<Item> inventory_in);
    Room* getCurrentRoom();
    Room* getPreviousRoom();
    vector<Item> getInventory();
};

#endif // PLAYER_H_INCLUDED
