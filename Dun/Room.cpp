#include "Room.h"

Room::Room()
{
	upRoom = nullptr;
	downRoom = nullptr;
	leftRoom = nullptr;
	rightRoom = nullptr;

}

Folder::Folder(string name_in)
{
	setTag("Folder");
	setName(name_in);
	folder_name = name_in;
	need_key = false;
}
Folder::Folder(string name_in, bool need_k)
{
	setTag("Folder");
	setName(name_in);
	folder_name = name_in;
	need_key = true;
}

bool Folder::triggerEvent(Object* obj_in)
{
	if (obj_in->getTag() == "Player")
	{
		Player* ply = dynamic_cast<Player*>(obj_in);
		
		//ply->room_going_to = folder_name;
		ply->currentRoom->blocksInRoom[ply->player_room_Y][ply->player_room_X].can_walk = true;
		ply->currentRoom->blocksInRoom[ply->player_room_Y][ply->player_room_X].object_display = ' ';
		ply->currentRoom->blocksInRoom[ply->player_room_Y][ply->player_room_X].obj_on_block = nullptr;
		if (need_key == true)
		{
			for (int i = 0; i < ply->inventory.size(); i++)
			{
				if (ply->inventory[i].getName() == "Key")
				{
					system("cls");
					cout << "Do you wanna use [Key] ?\n y/n\n";
					char temp = '\0';
					cin >> temp;

					if (temp == 'y')
					{
						ply->triggerEvent(this);
						ply->setRoomXY(10, 1);
						return true;
					}
					else
					{
						return false;
					}
				}
			}
			system("cls");
			cout << "\n\n\nYou need a [Key] to get in this room!!\nEnter any key to continue.\n";
			char temp = '\0';
			cin >> temp;
			return false;
		}

		ply->triggerEvent(this);
		
		ply->setRoomXY(10, 1);
	}
	return true;
}

Room::Room(bool isFinal, int index, string dir_in)
{
	folder_room_name = dir_in;
	isFinalRoom = isFinal;
	index = index;
	upRoom = nullptr;
	downRoom = nullptr;
	leftRoom = nullptr;
	rightRoom = nullptr;

	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 20; j++)
		{
			blocksInRoom[i][j].can_walk = true;
			blocksInRoom[i][j].isExit = false;
			blocksInRoom[i][j].obj_on_block = nullptr;
			blocksInRoom[i][j].object_display = ' ';
		}
	}
	for (int i = 0; i < 10; i++)
	{
		blocksInRoom[i][0].can_walk = false;
		blocksInRoom[i][0].isExit = false;
		blocksInRoom[i][0].obj_on_block = nullptr;
		blocksInRoom[i][0].object_display = '|';

		blocksInRoom[i][19].can_walk = false;
		blocksInRoom[i][19].isExit = false;
		blocksInRoom[i][19].obj_on_block = nullptr;
		blocksInRoom[i][19].object_display = '|';
	}
	for (int i = 0; i < 20; i++)
	{
		blocksInRoom[0][i].can_walk = false;
		blocksInRoom[0][i].isExit = false;
		blocksInRoom[0][i].obj_on_block = nullptr;
		blocksInRoom[0][i].object_display = '-';

		blocksInRoom[9][i].can_walk = false;
		blocksInRoom[9][i].isExit = false;
		blocksInRoom[9][i].obj_on_block = nullptr;
		blocksInRoom[9][i].object_display = '-';
	}
	blocksInRoom[0][0].object_display = '+';
	blocksInRoom[9][0].object_display = '+';
	blocksInRoom[9][19].object_display = '+';
	blocksInRoom[0][19].object_display = '+';

	
}
int Room::getRandomX()
{
	srand(time(NULL));
	int x = rand() % 19 + 1;
	return x;
}
int Room::getRandomY()
{
	srand(time(NULL));
	int x = rand() % 9 + 1;
	return x;
}
bool Room::popObject(Object* obj_done)
{
	for (int i = 0; i < objects.size(); i++)
	{
		if (objects[i] == obj_done)
		{
			objects.erase(next(objects.begin()));
			// not sure on this
			return true;
		}
	}
	return false;
}
vector<string> Room::getFolderInfoFromDir()
{
	std::string path = folder_room_name;
	vector<string> folder;
	std::string temp;
	int folder_ctr = 0;
	//make sure dir have more than 2 folder and 4 file
	for (const auto& entry : fs::directory_iterator(path))
	{
		temp = entry.path().string();
		//temp.erase(0, path.length() + 1);
		if (temp.find('.', path.length() + 1) == std::string::npos && folder_ctr <= 1)
		{
			folder.push_back(temp);
			folder_ctr++;
		}
		if (folder_ctr >= 2)
		{
			cout << "returning" << folder.size();
			return folder;
		}
	}
	return folder;
}
vector<string> Room::getRealName()
{
	std::string path = folder_room_name;
	//std::string file[4];
	vector<string> file;
	std::string temp;
	int file_ctr = 0;

	//make sure dir have more than 4 folder and 4 file
	for (const auto& entry : fs::directory_iterator(path))
	{
		temp = entry.path().string();
		temp.erase(0, path.length() + 1);
		if (temp.find('.') != std::string::npos && file_ctr <= 3)
		{
			temp = path + "\\" + temp;
			file.push_back(temp);
			file_ctr++;
		}
		if (file_ctr >= 4)
		{
			return file;
		}
	}
	return file;
}
vector<string> Room::getFileInfoFromDir()
{
	std::string path = folder_room_name;
	//std::string file[4];
	vector<string> file;
	std::string temp;
	int file_ctr = 0;

	//make sure dir have more than 4 folder and 4 file		if (inputs[i].find(".zzzzzzzzz") == string::npos && inputs[i].find("Dun.exe") == string::npos)

	for (const auto& entry : fs::directory_iterator(path))
	{
		temp = entry.path().string();
		temp.erase(0, path.length() + 1);
		if (temp.find('.') != std::string::npos && file_ctr <= 3 && temp.find("Dun.exe") == string::npos)
		{
			file.push_back(temp);
			file_ctr++;
		}
		if (file_ctr >= 4)
		{
			return file;
		}
	}
	return file;
}
void Room::setUpRoom(Room* rm_in)
{
	upRoom = rm_in;
	return;
}

void Room::setDownRoom(Room* rm_in)
{
	downRoom = rm_in;
	return;
}

void Room::setLeftRoom(Room* rm_in)
{
	leftRoom = rm_in;
	return;
}

void Room::setRightRoom(Room* rm_in)
{
	rightRoom = rm_in;
	return;
}

void Room::setRoomInside(int x_in, int y_in, Object* obj_in, char obj_disp)
{
	blocksInRoom[y_in][x_in].can_walk = false;
	blocksInRoom[y_in][x_in].isExit = false;
	blocksInRoom[y_in][x_in].object_display = obj_disp;
	blocksInRoom[y_in][x_in].obj_on_block = obj_in;
	return;
}

void Room::setIsFinal(bool is_exit_in)
{
	isFinalRoom = is_exit_in;
	return;
}

void Room::setIndex(int index_in)
{
	index = index_in;
	return;
}

bool Room::getIsFinal()
{
	return isFinalRoom;
}

int Room::getIndex()
{
	return index;
}

vector<Object*> Room::getObjects()
{
	return objects;
}

Room* Room::getUpRoom()
{
	return upRoom;
}

Room* Room::getDownRoom()
{
	return downRoom;
}

Room* Room::getLeftRoom()
{
	return leftRoom;
}

Room* Room::getRightRoom()
{
	return rightRoom;
}

