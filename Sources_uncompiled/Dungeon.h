#ifndef DUNGEON_H_INCLUDED
#define DUNGEON_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <exception>
#include "Item.h"
#include "Player.h"
#include "Monster.h"
#include "NPC.h"
#include "Room.h"
#include "Record.h"
#include <filesystem>
#include <random>

namespace fs = std::filesystem;
using namespace std;

class Player;
class Dungeon {
private:
    Player player;
    Room* player_at_map;
    vector<Monster*> every_monster_in_world;
//public:
    //static 
    vector<Room> rooms;
public:
    Dungeon();
    Dungeon(bool);
    /* Create a new player, and give him/her basic status */
    void createPlayer();

    /* Create a map, which include several different rooms */
    void createMap();

    /* Deal with player's moveing action */
    void handleMovementAndSetPlr(char in);

    /* Deal with player's iteraction with objects in that room */
    void handleEvent(Object*);

    /* Deal with all game initial setting       */
    /* Including create player, create map etc  */
    void startGame();
    void lock3File(vector<string>, string);
    /* Deal with the player's action     */
    /* including showing the action list */
    /* that player can do at that room   */
    /* and dealing with player's input   */
    void chooseAction(vector<Object*>);

    /* Check whether the game should end or not */
    /* Including player victory, or he/she dead */
    bool checkGameLogic();
    int getRandomX();
    void dumpPlayer();
    int getRandomY();
    void clearAndPrintMap();
    /* Deal with the whole game process */
    void runDungeon();
    void createRoomRecurr(string dir_in, int index, string myself);
};


#endif // DUNGEON_H_INCLUDED
