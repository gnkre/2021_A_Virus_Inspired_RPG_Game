// Dun.cpp : 此檔案包含 'main' 函式。程式會於該處開始執行及結束執行。
//

#include <iostream>
#include <string>
#include <vector>
#include "Dungeon.h"
#include "Item.h"
#include "Monster.h"
#include "NPC.h"
#include "Player.h"

using namespace std;

int main() 
{
	string mode[3];
	mode[0] = "Play New Game";
	mode[1] = "Load Game";
	mode[2] = "Exit";
	int cursor = 0;
	char temp = '\0';
	/*
$$$$$$$\                                                              
$$  __$$\                                                             
$$ |  $$ |$$\   $$\ $$$$$$$\   $$$$$$\   $$$$$$\   $$$$$$\  $$$$$$$\  
$$ |  $$ |$$ |  $$ |$$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ $$  __$$\ 
$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ /  $$ |$$$$$$$$ |$$ /  $$ |$$ |  $$ |
$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$   ____|$$ |  $$ |$$ |  $$ |
$$$$$$$  |\$$$$$$  |$$ |  $$ |\$$$$$$$ |\$$$$$$$\ \$$$$$$  |$$ |  $$ |
\_______/  \______/ \__|  \__| \____$$ | \_______| \______/ \__|  \__|
                              $$\   $$ |                              
                              \$$$$$$  |                              
                               \______/                               
*/
	while (1)
	{
		cursor %= 3;
		system("cls");
		cout << "$$$$$$$\\  "<<endl;
		cout << "$$  __$$\\" << endl;
		cout << "$$ |  $$ |$$\\   $$\\ $$$$$$$\\   $$$$$$\\   $$$$$$\\   $$$$$$\\  $$$$$$$\\  " << endl;
		cout << "$$ |  $$ |$$ |  $$ |$$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ $$  __$$\\ " << endl;
		cout << "$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ /  $$ |$$$$$$$$ |$$ /  $$ |$$ |  $$ |" << endl;
		cout << "$$ |  $$ |$$ |  $$ |$$ |  $$ |$$ |  $$ |$$   ____|$$ |  $$ |$$ |  $$ |" << endl;
		cout << "$$$$$$$  |\\$$$$$$  |$$ |  $$ |\\$$$$$$$ |\\$$$$$$$\\ \\$$$$$$  |$$ |  $$ |" << endl;
		cout << "\\_______/  \\______/ \\__|  \\__| \\____$$ | \\_______| \\______/ \\__|  \\__|" << endl;
		cout << "                              $$\\   $$ |                              " << endl;
		cout << "                              \\$$$$$$  |                              " << endl;
		cout << "                               \\______/                               " << endl;
		cout <<"\tWelcome to Dungeon.\n\tselect game mode\n\n\n w and s to control cursor, x to enter\n";
		for (int i = 0; i < 3; i++)
		{
			if (i == cursor)
			{
				cout << " --> ";
			}
			else
			{
				cout << "     ";
			}
			cout << mode[i] << endl;
		}
		cin >> temp;
		if (temp == 's')
		{
			cursor++;
		}
		else if (temp == 'w')
		{
			cursor--;
		}
		else if (temp == 'x' && cursor == 0)
		{
			Dungeon dungeon = Dungeon();
			dungeon.runDungeon();
		}
		else if (temp == 'x' && cursor == 1)
		{
			Dungeon dungeon = Dungeon(true);
			dungeon.runDungeon();
		}
		else if (temp == 'x' && cursor == 2)
		{
			exit(0);
		}
	}
    
    return 0;
}


// 執行程式: Ctrl + F5 或 [偵錯] > [啟動但不偵錯] 功能表
// 偵錯程式: F5 或 [偵錯] > [啟動偵錯] 功能表

// 開始使用的提示: 
//   1. 使用 [方案總管] 視窗，新增/管理檔案
//   2. 使用 [Team Explorer] 視窗，連線到原始檔控制
//   3. 使用 [輸出] 視窗，參閱組建輸出與其他訊息
//   4. 使用 [錯誤清單] 視窗，檢視錯誤
//   5. 前往 [專案] > [新增項目]，建立新的程式碼檔案，或是前往 [專案] > [新增現有項目]，將現有程式碼檔案新增至專案
//   6. 之後要再次開啟此專案時，請前往 [檔案] > [開啟] > [專案]，然後選取 .sln 檔案
