#include "NPC.h"

NPC::NPC()
{
	setName("NULL");
	setTag("NPC");
    commodity.push_back(Item("Health_Potion", 0, 0, 30, 200));
    commodity.push_back(Item("Short_Sword", 20, 0, 0, 100));
    commodity.push_back(Item("Iron_Armor", 0, 20, 0, 50));
    pixels[0] = { "-----------" };
    pixels[1] = { "|         |" };
    pixels[2] = { "|  ^_^    |" };
    pixels[3] = { "|         |" };
    pixels[4] = { "|         |" };
    pixels[5] = { "|         |" };
    pixels[6] = { "-----------" };
    script[0] = { "Hello, enter S to buy items and C to chat!" };
    script[1] = { "What do you want to buy!" };
    script[2] = { "This is a well-programmed and creative game, isn't it?\nI wonder what kind of cool guy made all of these\na.I totally agree with you!\nb.Nah, don't think so." };
    script[3] = { "Well, you're pretty dumb and disgusting\nI am stopping the convestation anyway.\nEnter r to quit." };
    script[4] = { "Awesome! Glad to know we're on the same page\nI am giving you the \"Heavy attack\" ablitiy!" };
}
Statue::Statue()
{
    appear[0] = { "                ,-." };
    appear[1] = { "               |* *|" };
    appear[2] = { "                \\-/   ;/_" };
    appear[3] = { "               /\\v/\\_//'" };
    appear[4] = { "              || | .-'" };
    appear[5] = { "              || |u|" };
    appear[6] = { "              ('_|_|" };
    appear[7] = { "               | | |" };
    appear[8] = { "             _,|_|_|,_" };
    appear[9] = {"            / (_,|,_) \\"};
    appear[10] = { "           /___________\\" };
    appear[11] = { "           |___________|" };
    appear[12] = { "            |Developer|" };
    appear[13] = { "            |  ERIK   |" };
    appear[14] = { "            |   NING  |" };
    appear[15] = { "           /|_________|\\" };
    appear[16] = { "          /_____________\\" };
    appear[17] = { "          |_____________|" };
}
NPC::NPC(string name_in, int index)
{
	setName(name_in);
    setTag("NPC");
	//commodity = items_of_npc;
    TODO://NPC have different commosity according to index 
    commodity.push_back(Item("Health_Potion", 0, 0, 30, 200));
    commodity.push_back(Item("Short_Sword", 20, 0, 0, 100));
    commodity.push_back(Item("Iron_Armor", 0, 20, 0, 50));
    commodity.push_back(Item("Damage_Potion", 20, 0, 0, 100));

    pixels[0] = { "-----------" };
    pixels[1] = { "|         |" };
    pixels[2] = { "|  ^_^    |" };
    pixels[3] = { "|         |" };
    pixels[4] = { "|         |" };
    pixels[5] = { "|         |" };
    pixels[6] = { "-----------" };

    script[0] = { "Hello, enter s to buy items, c to chat and r to exit!" };
    script[1] = { "What do you want to buy!" };
    script[2] = { "This is a well-programmed and creative game, isn't it? The developer must be really cool\n\na.I totally agree with you!\nb.Nah, don't think so." };
    script[3] = { "Well, you're pretty dumb and disgusting, I am stopping the convestation anyway.\n\nEnter r to quit." };
    script[4] = { "Awesome! Glad to know we're all on the same page! I am giving you a new ablitiy!\n\nEnter r to quit." };
}

bool NPC::triggerEvent(Object* obj_in)
{
    if (obj_in->getTag() == "Player")
    {
        bool temp = true;
        Player* player = dynamic_cast<Player*>(obj_in);
        drawNPC();
        
        while (player->triggerEvent(this) == true)
        {
            drawNPC();
            //player func will deal w/ the blood of monster
            if (player->triggerEvent(this) == false)
                break;
        }
    }
    return true;
}
void NPC::buyDaItem(int cursor, Player* plr_in)
{
    if (commodity.size() != 0)
    {
        cursor = cursor % commodity.size();
        if (commodity[cursor].value < plr_in->o_ka_ne)
        {
            if (commodity[cursor].getName().find("Health_Potion") != string::npos)
            {
                plr_in->inventory.push_back(commodity[cursor]);
                plr_in->o_ka_ne = plr_in->o_ka_ne - commodity[cursor].value;
                cout << plr_in->getName() << " bought " << commodity[cursor].getName() << endl;

            }
            else
            {
                plr_in->inventory.insert(plr_in->inventory.begin(), commodity[cursor]);
                plr_in->o_ka_ne = plr_in->o_ka_ne - commodity[cursor].value;
                cout << plr_in->getName() << " bought " << commodity[cursor].getName() << endl;

            }
        }
    }
    else
    {
        cout << "You don't have enough money to buy this!\n";
    }
}
vector<Item> NPC::getCommodity()
{
    return commodity;
}
void NPC::listCommodity(int cursor)
{
    if (commodity.size() != 0)
    {
        cursor = cursor % commodity.size();
        for (int i = 0; i < commodity.size(); i++)
        {
            if (i == cursor)
            {
                printf("  ---> ");
            }
            else
            {
                printf("       ");
            }
            cout << "[" << getCommodity()[i].getName();
            printf("] : ATK + %d, DEF + %d, HP + %d", getCommodity()[i].getAttack(), getCommodity()[i].getDefense(), getCommodity()[i].getHealth());
            cout << endl;
        }
    }
    return;
}
bool Statue::triggerEvent(Object* obj_in)
{
    Player* plr = dynamic_cast<Player*>(obj_in);
    system("cls");
    cout << endl;
    cout << "===============================================" << endl;
    for (int i = 0; i < 18; i++)
    {
        cout << appear[i] << endl;
    }
    plr->drawPlayer();
    cout << "===============================================" << endl;

    cout << "Cheers to developer Erik! give him higher point!\nEnter r to exit" << endl;
    char temp = '\0';
    cin >> temp;
    return true;
}
void NPC::drawNPC()
{
    system("cls");
    cout << endl << endl;
    cout << "=========================================================" << endl;

    if (getName().size() >= 15)
    {
        cout << "                   [";
        for (int i = 0; i < 15; i++)
        {
            cout << getName().at(i);
        }
        cout << "...]" << endl;
    }
    else
    {
        cout << "                       [" << getName() << ']' << endl;
    }
    for (int i = 0; i < 7; i++)
    {
        cout << "                       " << pixels[i] << endl;
    }
    return;
}