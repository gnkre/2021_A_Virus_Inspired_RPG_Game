#include "Dungeon.h"
int Dungeon::getRandomX()
{

	int x = rand() % 18 + 1;
	return x;
}
int Dungeon::getRandomY()
{
	//srand(time(NULL));
	int x = rand() % 8 + 1;
	return x;
}
Dungeon::Dungeon(bool temp)
{
	createMap();
	cout << "\n\n   ----> all the above are files that I locked" << endl << "  -->> game starts now!!" << endl;
	system("pause");
	system("cls");
	
	ifstream fle("DUNSV");
	string name;
	//getline(fle, name);
	fle >> name;
	int hp = 0;
	fle >> hp;
	int max_hp = 0;
	fle >> max_hp;
	int atk = 0;
	fle >> atk;
	int def = 0;
	fle >> def;
	int num_of_inv = 0;
	fle >> num_of_inv;
	int money = 0;
	fle >> money;
	player = Player(name, atk, def, hp, max_hp);
	player.o_ka_ne = money;
	string itm_nm;
	int itm_h = 0;
	int itm_d = 0;
	int itm_a = 0;
	int itm_m = 0;
	for (int i = 0; i < num_of_inv; i++)
	{
		fle >> itm_nm >> itm_a >> itm_d >> itm_h >> itm_m;
		player.inventory.push_back(Item(itm_nm, itm_a, itm_d, itm_h, itm_m));
	}
	//left hand right hand hat armor
	fle >> itm_nm;
	if (itm_nm != "NULL")
	{
		fle >> itm_a >> itm_d >> itm_h >> itm_m;
		player.left_hand = Item(Item(itm_nm, itm_a, itm_d, itm_h, itm_m));
	}
	fle >> itm_nm;
	if (itm_nm != "NULL")
	{
		fle >> itm_a >> itm_d >> itm_h >> itm_m;
		player.right_hand = Item(Item(itm_nm, itm_a, itm_d, itm_h, itm_m));
	}
	fle >> itm_nm;
	if (itm_nm != "NULL")
	{
		fle >> itm_a >> itm_d >> itm_h >> itm_m;
		player.head = Item(Item(itm_nm, itm_a, itm_d, itm_h, itm_m));
	}
	fle >> itm_nm;
	if (itm_nm != "NULL")
	{
		fle >> itm_a >> itm_d >> itm_h >> itm_m;
		player.body = Item(Item(itm_nm, itm_a, itm_d, itm_h, itm_m));
	}
	string cur_room;
	fle >> cur_room;
	for (int i = 0; i < rooms.size(); i++)
	{
		if (rooms[i].folder_room_name == cur_room)
		{
			player.currentRoom = &rooms[i];
			player.previousRoom = &rooms[i];
			break;
		}
	}
	player.player_room_X = 3;
	player.player_room_Y = 3;
	player.setRoomXY(3, 3);
	player.room_of_plr = &rooms;
}
Dungeon::Dungeon()
{

	createMap();
	cout << "\n\n   ----> all the above are files that I locked" << endl << "  -->> game starts now!!" << endl;
	system("pause");
	system("cls");
	createPlayer();
	player_at_map = player.getCurrentRoom();
	//clearAndPrintMap();
}
void Dungeon::runDungeon()
{
	char input = '\0';
	while (1)
	{
		if (input != 'r' && input != 'n')
			clearAndPrintMap();
		cin >> input;
		if (input == 'e')
		{
			int cursor = 0;
			while (1)
			{
				if (input == 's')
				{
					cursor++;
				}
				else if (input == 'w')
				{
					cursor--;
				}
				else if (input == 'r')
				{
					clearAndPrintMap();
					
					break;
				}
				input = player.showStatus(cursor);
				//cin >> input;
			}
			
		}
		else if (input == 'c')
		{
			dumpPlayer();
			cout << "Now exit";
			system("pause");
			exit(0);
		}
		//need to exclude the situation that 
		//user is dumb and enter sth not wasd
		
		handleMovementAndSetPlr(input);
		if (input != 'r' && input != 'n')
			clearAndPrintMap();
	}
}
void Dungeon::dumpPlayer()
{
	fstream fleo;
	fleo.open("DUNSV", ios::out);
	fleo << player.getName() << "\n";
	fleo << player.currentHealth << "\n";
	fleo << player.maxHealth << "\n";
	fleo << player.attack << "\n";
	fleo << player.defense << "\n";
	fleo << player.inventory.size() << "\n";
	fleo << player.o_ka_ne << "\n";
	for (int i = 0; i < player.inventory.size(); i++)
	{
		fleo << player.inventory[i].getName() << ' ' << player.inventory[i].attack << ' ' << player.inventory[i].defense << ' ' << player.inventory[i].health << ' ' << player.inventory[i].value << "\n";
	}
	//left hand right hand hat armor
	if (player.left_hand.getName() != "NULL")
	{
		fleo << player.left_hand.getName() << ' ' << player.left_hand.attack << ' ' << player.left_hand.defense << ' ' << player.left_hand.health << ' ' << player.left_hand.value << "\n";
	}
	else
		fleo << "NULL\n";
	if (player.right_hand.getName() != "NULL")
	{
		fleo << player.right_hand.getName() << ' ' << player.right_hand.attack << ' ' << player.right_hand.defense << ' ' << player.right_hand.health << ' ' << player.right_hand.value << "\n";
	}
	else
		fleo << "NULL\n";
	if (player.head.getName() != "NULL")
	{
		fleo << player.head.getName() << ' ' << player.head.attack << ' ' << player.head.defense << ' ' << player.head.health << ' ' << player.head.value << "\n";
	}
	else
		fleo << "NULL\n";
	if (player.body.getName() != "NULL")
	{
		fleo << player.body.getName() << ' ' << player.body.attack << ' ' << player.body.defense << ' ' << player.body.health << ' ' << player.body.value << "\n";
	}
	else
		fleo << "NULL\n";
	fleo << player.currentRoom->folder_room_name;
}
void Dungeon::handleMovementAndSetPlr(char in)
{
	int x = player.player_room_X;
	int y = player.player_room_Y;

	if (in == 'w')
	{
		if (player.setRoomXY(player.player_room_X, player.player_room_Y - 1) == 0)
		{
			return;
		}
	}
	else if (in == 'd')
	{
		if (player.setRoomXY(player.player_room_X + 1, player.player_room_Y) == 0)
		{
			return;
		}
	}
	else if (in == 'a')
	{
		if (player.setRoomXY(player.player_room_X - 1, player.player_room_Y) == 0)
		{
			return;
		}
	}
	else if (in == 's')
	{
		if (player.setRoomXY(player.player_room_X, player.player_room_Y + 1) == 0)
		{
			return;
		}
	}
	player.getCurrentRoom()->blocksInRoom[y][x].can_walk = true;
	player.getCurrentRoom()->blocksInRoom[y][x].object_display = ' ';
	player.getCurrentRoom()->blocksInRoom[y][x].obj_on_block = nullptr;
	return;
}
void Dungeon::createPlayer()
{
	string name_input;
	cout << "Please enter your name: ";
	cin >> name_input;
	cout << endl;
	cout << "Player [" << name_input << "]" << endl << endl;
	cout << "You have \nHP:100\nATK:50\nDEF:50" << endl;
	char temp;
	cout << "Enter any key to create" << endl;
	cin >> temp;
	player.setName(name_input);
	player.setAttack(10);
	player.setDefense(50);
	player.o_ka_ne = 10000;
	player.setMaxHealth(100);
	player.setCurrentHealth(100);
	player.setCurrentRoom(&rooms[0]);
	player.setPreviousRoom(nullptr);
	player.setRoomXY(3, 3);
	player.head = Item();
	player.left_hand = Item();
	player.right_hand = Item();
	player.body = Item();
	player.room_of_plr = &rooms;
	return;
}

/*void Dungeon::handleEvent(Object*)
{
=========================================
                   [cdcsvdvs.exe      ]
                       -----------
                       |         |
                       |  X.X    |
                       |         | 
                       |         |
                       |         |
                       ----------- 
      [erik]
    ----------
	| X      |
	|     X  |
	|   X    |
=========================================
What do you want to do ?
a.Fight
b.retreat


}*/
void Dungeon::lock3File(vector<string> inputs, string folder_name)
{
	int size = inputs.size();

	if (size >= 4)
		size = 4;
	for (int i = 1; i < size; i++)
	{
		if (inputs[i].find(".zzzzzzzzz") == string::npos && inputs[i].find("Dun.exe") == string::npos)
		{
			rename((folder_name + "//" + inputs[i]).c_str(), (folder_name + "//" + inputs[i] + ".zzzzzzzzz").c_str());
		}
	}
	return;
}
void Dungeon::createRoomRecurr(string dir_in, int index, string myself)
{
	if (index > 2)
		return;
	rooms.push_back(Room(false, index, dir_in));
	//get infos
	//vector<string> files;
	//vector<string> folders;
	//vector<string> real_na = rooms.back().getRealName();
	vector<string> files = rooms.back().getFileInfoFromDir();
	vector<string> folders = rooms.back().getFolderInfoFromDir();
	
	lock3File(files, dir_in);
	files = rooms.back().getFileInfoFromDir();
	
	//make monster and sav it in vec
	//objects.push_back(&Monster(false, files[0], 10, 10, 30));
	for (int i = 1; i < files.size(); i++)
	{
		
		Monster* temp = new Monster(true,dir_in + "//" + files[i], files[i], 10, 10, 50);
		rooms.back().objects.push_back(temp);
		every_monster_in_world.push_back(temp);
		cout << temp->getName() << endl;
		int x = getRandomX();
		int y = getRandomY();
		rooms.back().blocksInRoom[y][x].can_walk = false;
		rooms.back().blocksInRoom[y][x].isExit = false;
		rooms.back().blocksInRoom[y][x].obj_on_block = rooms.back().objects.back();
		rooms.back().blocksInRoom[y][x].object_display = 'X';
		
		//lock the file
	}
	
	if (files.size() >= 1)
	{
		NPC* temp = new NPC(files[0], index);
		rooms.back().objects.push_back(temp);
		int x = getRandomX();
		int y = getRandomY();
		rooms.back().blocksInRoom[y][x].can_walk = false;
		rooms.back().blocksInRoom[y][x].isExit = false;
		rooms.back().blocksInRoom[y][x].obj_on_block = rooms.back().objects.back();
		rooms.back().blocksInRoom[y][x].object_display = 'N';
	}
	
	
	rooms.back().objects.push_back(new Folder(myself));
	rooms.back().blocksInRoom[0][10].can_walk = false;
	rooms.back().blocksInRoom[0][10].isExit = false;
	rooms.back().blocksInRoom[0][10].obj_on_block = rooms.back().objects.back();
	rooms.back().blocksInRoom[0][10].object_display = '^';
	cout << index;
	if (index <= 1)
	{
		
		if (folders.size() == 0)
		{
			return;
		}
		Folder* temp = new Folder(folders[0]);
		cout << temp->getName() << endl;
		rooms.back().objects.push_back(temp);
		int x = getRandomX();
		int y = getRandomY();
		rooms.back().blocksInRoom[y][x].can_walk = false;
		rooms.back().blocksInRoom[y][x].isExit = false;
		rooms.back().blocksInRoom[y][x].obj_on_block = rooms.back().objects.back();
		rooms.back().blocksInRoom[y][x].object_display = 'F';
		//for (int i = 0; i < folders.size(); i++)
		//{
		//	Folder* temp = new Folder(folders[i]);
		//	cout << temp->getName() << endl;
		//	rooms.back().objects.push_back(temp);
		//	int x = getRandomX();
		//	int y = getRandomY();
		//	rooms.back().blocksInRoom[y][x].can_walk = false;
		//	rooms.back().blocksInRoom[y][x].isExit = false;
		//	rooms.back().blocksInRoom[y][x].obj_on_block = rooms.back().objects.back();
		//	rooms.back().blocksInRoom[y][x].object_display = 'F';
		//}
	}
	
	index++;
	if (folders.size() == 0)
	{
		return;
	}
	if (folders.size() != 0)
	{
		string temp_name = rooms.back().folder_room_name;
		createRoomRecurr(folders[0], index, temp_name);
	}
	
	/*if (folders.size() >= 2)
	{
		createRoomRecurr(folders[1], index, temp_name);

	}*/
}
void Dungeon::createMap()
{
	//
	//       0
	//      / \
	//     1   1
    //    /\   /\
	//   2  2  2  2
	//
	system("cls");
	cout << "\n\nNow I am locking some of your files by changing their filename extension" << endl << endl;
	cout << "       0 <-- this is the folder where you put the dun.exe, i will lock 3 files here" << endl;
	cout << "      / \\" << endl;
	cout << "     1   1  <-- i will pick two folders in the directory where you put dun.exe, get in there, and lock 3 files" << endl;
	cout << "    /\\   /\\" << endl;
	cout << "   2  2  2  2 <-- pick 2 foldes from the upper layer and also lock some files" << endl;
	cout << "\n\nThe monsters appear in the game are all your files" << endl;
	cout << "files will be unlocked after killing them" << endl;
	cout << "Once you kill the boss, all the file will be unlocked and return to you" << endl;
	cout << "Good Luck!" << endl;
	system("pause");
	system("cls");
	rooms.push_back(Room(true, 0, "."));
	//get infos
	//vector<string> files;
	//vector<string> folders;
	vector<string> files = rooms[0].getFileInfoFromDir();
	vector<string> folders = rooms[0].getFolderInfoFromDir();
	lock3File(files, ".");
	files = rooms[0].getFileInfoFromDir();
	if (folders.size() == 0)
	{
		cout << "Requires more than 2 folders";
		return;
	}
	cout << files.size() << endl;
	cout << folders.size();
	
	//make monster and sav it in vec
	//objects.push_back(&Monster(false, files[0], 10, 10, 30));
	for (int i = 1; i < files.size(); i++)
	{

		Monster* temp = new Monster(true, ".//" + files[i], files[i], 10, 10, 30);
		rooms.back().objects.push_back(temp);
		every_monster_in_world.push_back(temp);
		int x = getRandomX();
		int y = getRandomY();
		rooms[0].blocksInRoom[y][x].can_walk = false;
		rooms[0].blocksInRoom[y][x].isExit = false;
		rooms[0].blocksInRoom[y][x].obj_on_block = rooms[0].objects.back();
		rooms[0].blocksInRoom[y][x].object_display = 'X';
		cout << "\"" << files[i] << "\" is inflected" << endl;
		//lock the file
	}
	NPC* temp = new NPC(files[0], 0);
	rooms.back().objects.push_back(temp);
	int x = getRandomX();
	int y = getRandomY();
	rooms[0].blocksInRoom[y][x].can_walk = false;
	rooms[0].blocksInRoom[y][x].isExit = false;
	rooms[0].blocksInRoom[y][x].obj_on_block = rooms.back().objects.back();
	rooms[0].blocksInRoom[y][x].object_display = 'N';

	for (int i = 0; i < 2; i++)
	{
		Folder* temp = new Folder(folders[i]);
		rooms.back().objects.push_back(temp);
		int x = getRandomX();
		int y = getRandomY();
		rooms[0].blocksInRoom[y][x].can_walk = false;
		rooms[0].blocksInRoom[y][x].isExit = false;
		rooms[0].blocksInRoom[y][x].obj_on_block = rooms[0].objects.back();
		rooms[0].blocksInRoom[y][x].object_display = 'F';
		cout << folders[i] << endl;
		if (folders.size() == 1)
			break;
	}
	
	Item* da_item = new Item("Long_Sword", 10, 0, 0, 100);
	rooms[0].blocksInRoom[4][4].can_walk = false;
	rooms[0].blocksInRoom[4][4].isExit = false;
	rooms[0].blocksInRoom[4][4].obj_on_block = da_item;
	rooms[0].blocksInRoom[4][4].object_display = 'I';
	Item* da_item1 = new Item("Top_Hat", 0, 10, 10, 200);
	rooms[0].blocksInRoom[4][3].can_walk = false;
	rooms[0].blocksInRoom[4][3].isExit = false;
	rooms[0].blocksInRoom[4][3].obj_on_block = da_item1;
	rooms[0].blocksInRoom[4][3].object_display = 'I';
	Item* da_key = new Item("Key", 0, 0, 0, 0);
	rooms[0].blocksInRoom[7][3].can_walk = false;
	rooms[0].blocksInRoom[7][3].isExit = false;
	rooms[0].blocksInRoom[7][3].obj_on_block = da_key;
	rooms[0].blocksInRoom[7][3].object_display = 'K';
	// make two 1 layer rooms
	if (folders.size() >= 1)
	{
		cout << "here";
		createRoomRecurr(folders[0], 1, ".");
	}
		//createRoomRecurr(folders[0], 1, ".");
	if (folders.size() >= 2)
		createRoomRecurr(folders[1], 1, ".");
	rooms.push_back(Room(false, 0, "secret_room"));
	rooms.back().blocksInRoom[6][6].can_walk = false;
	rooms.back().blocksInRoom[6][6].isExit = false;
	rooms.back().blocksInRoom[6][6].object_display = '#';
	rooms.back().blocksInRoom[6][6].obj_on_block = new Statue;
	rooms.back().blocksInRoom[0][10].can_walk = false;
	rooms.back().blocksInRoom[0][10].isExit = false;
	rooms.back().blocksInRoom[0][10].object_display = '^';
	rooms.back().blocksInRoom[0][10].obj_on_block = new Folder(".");
	rooms[0].blocksInRoom[9][9].can_walk = false;
	rooms[0].blocksInRoom[9][9].isExit = false;
	rooms[0].blocksInRoom[9][9].object_display = '*';
	rooms[0].blocksInRoom[9][9].obj_on_block = new Folder("secret_room", true);
	Boss* da_boss = new Boss(every_monster_in_world);
	rooms.back().objects.push_back(da_boss);
	rooms[0].blocksInRoom[8][18].can_walk = false;
	rooms[0].blocksInRoom[8][18].isExit = false;
	rooms[0].blocksInRoom[8][18].obj_on_block = da_boss;
	rooms[0].blocksInRoom[8][18].object_display = 'B';
}

void Dungeon::clearAndPrintMap()
{
	system("cls");
	rooms;
	for (int i = 0; i < 10; i++)
	{
		cout << endl;
		for (int j = 0; j < 20; j++)
		{
			cout << player.currentRoom->blocksInRoom[i][j].object_display;
		}
	}
	cout << endl << "This is folder " << player.currentRoom->folder_room_name << endl;
	cout << endl;
	cout << "In this room :\n";
	for (int i = 0; i < player.currentRoom->getObjects().size(); i++)
	{
		cout << player.currentRoom->getObjects()[i]->getName();
		if (player.currentRoom->getObjects()[i]->getTag() == "Monster")
		{
			cout << "  <--- INFECTED";
		}
		cout << endl;
		
	}
	cout << "Enter \"wasd\" to move, c to save and e to open backpack :";
	return;
}