#ifndef ROOM_H_INCLUDED
#define ROOM_H_INCLUDED

#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include <filesystem>
#include "Monster.h"

namespace fs = std::filesystem;
using namespace std;
struct Block
{
    bool can_walk;
    bool isExit;
    Object* obj_on_block;
    char object_display;
    //friend class Room;
};

/*class TransportPoint : public Object
{
public:
    TransportPoint(string, int from_in, int to_in, int init_x, int init_y, int place_x, int place_y);
    int index_from;
    int index_to;
    int to_x;
    int to_y;
    int from_x;
    int from_y;
    bool triggerEvent(Object* ply_in);
    //void transform();
};*/

class Folder : public GameCharacter
{
public:
    Folder(string name_in, bool need_k);
    bool need_key;
    string folder_name;
    Folder(string name_in);
    bool triggerEvent(Object* obj_in);

};

class Room
{
private:
    Room* upRoom;
    Room* downRoom;
    Room* leftRoom;
    Room* rightRoom;
public:
    string folder_room_name;
private:
    bool isFinalRoom;
    int index; //index = layer
    //vector<Object*> objects; /*contain 1 or multiple objects, including monster, npc, etc*/
public:
    Block blocksInRoom[10][20];
    Room();
    Room(bool isFinal, int index, string dir_in);//, vector<Object*> obj_inside);
    bool popObject(Object* obj_done); /*pop out the specific object, used when the interaction is done*/
    vector<Object*> objects;
    /* Set & Get function*/
    void setUpRoom(Room* rm_in);
    void setDownRoom(Room* rm_in);
    void setLeftRoom(Room* rm_in);
    void setRightRoom(Room* rm_in);

    //objs dat r unwalkable
    void setRoomInside(int x_in, int y_in, Object* obj_in, char obj_disp);
    void setIsFinal(bool is_exit_in);
    void setIndex(int index_in);

    //void setObjects(vector<Object*> obj_in_room, int* x_in, int y_in);
    bool getIsFinal();
    int getIndex();
    vector<Object*> getObjects();
    Room* getUpRoom();
    Room* getDownRoom();
    Room* getLeftRoom();
    Room* getRightRoom();
    vector<string> getFileInfoFromDir();
    vector<string> getFolderInfoFromDir();
    vector<string> getRealName();
    int getRandomX();
    int getRandomY();
};

#endif // ROOM_H_INCLUDED
