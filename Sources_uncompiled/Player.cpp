#include "Player.h"
#include "NPC.h"
Player::Player()
{
    setName("NULL");
    setTag("Player");
    setAttack(87);
    setCurrentHealth(87);
    setDefense(87);
    setMaxHealth(87);
    does_player_has_all_abilities = 3;
    abilities[0].name_of_ability = "Normal_Attack";
    abilities[0].weight_attack = 1;
    abilities[0].higher_player_def = 0;
    abilities[0].higher_player_attack = 0;

    abilities[1].name_of_ability = "Protect";
    abilities[1].higher_player_def = 10;
    abilities[1].weight_attack = 0;
    abilities[1].higher_player_attack = 0;

    abilities[2].name_of_ability = "Higher_Player_Attack";
    abilities[2].weight_attack = 0;
    abilities[2].higher_player_attack = 20;
    abilities[2].higher_player_def = 0;

    abilities[3].name_of_ability = "2X_Heavy_Attack";
    abilities[3].higher_player_attack = 0;
    abilities[3].higher_player_def = 0;
    abilities[3].weight_attack = 2;

    currentRoom = nullptr; 
    previousRoom = nullptr;
    appear[0] = { " |\\___/|" };
    appear[1] = { " )     (" };
    appear[2] = { "=\\     /=" };
    appear[3] = { "  )===(" };
    appear[4] = { " /     \\" };
    appear[5] = { " | ^   |" };
    appear[6] = { "/  \\\\   \\" };
    appear[7] = { "\\   ||  /" };
    appear[8] = { " \\__||_/" };

    appear_front[0] = { " |\\___/|" };
    appear_front[1] = { " ) . . (" };
    appear_front[2] = { "=\\  ^  /=" };
    appear_front[3] = { "  )===(" };
    appear_front[4] = { " /     \\" };
    appear_front[5] = { " |     |" };
    appear_front[6] = { "/       \\" };
    appear_front[7] = { "\\       /" };
    appear_front[8] = { " \\_____/" };
    /*appear[0] = {"----------"};
    appear[1] = { "|        |" };
    appear[2] = { "|        |" };
    appear[3] = { "|        |" };*/
}
// TODO: player have ability boolean
Player::Player(string name_in, int atk_in, int def_in, int hp, int max_hp_in)
{
    does_player_has_all_abilities = 3;
    abilities[0].name_of_ability = "Normal_Attack";
    abilities[0].weight_attack = 1;
    abilities[0].higher_player_def = 0;
    abilities[0].higher_player_attack = 0;

    abilities[1].name_of_ability = "Heal";
    abilities[1].higher_player_def = 0;
    abilities[1].weight_attack = 0;
    abilities[1].higher_player_attack = 0;

    abilities[2].name_of_ability = "Higher_Player_Attack";
    abilities[2].weight_attack = 0;
    abilities[2].higher_player_attack = 20;
    abilities[2].higher_player_def = 0;

    abilities[3].name_of_ability = "2X_Heavy_Attack";
    abilities[3].higher_player_attack = 0;
    abilities[3].higher_player_def = 0;
    abilities[3].weight_attack = 2;
    currentHealth = hp;
    setName(name_in);
    setTag("Player");
    setAttack(atk_in);
    setCurrentHealth(max_hp_in);
    setDefense(def_in);
    setMaxHealth(max_hp_in);
    appear[0] = { " |\\___/|" };
    appear[1] = { " )     (" };
    appear[2] = { "=\\     /=" };
    appear[3] = { "  )===(" };
    appear[4] = { " /     \\" };
    appear[5] = { " | ^   |" };
    appear[6] = { "/  \\\\   \\" };
    appear[7] = { "\\   ||  /" };
    appear[8] = { " \\__||_/" };

    appear_front[0] = { " |\\___/|" };
    appear_front[1] = { " ) . . (" };
    appear_front[2] = { "=\\  ^  /=" };
    appear_front[3] = { "  )===(" };
    appear_front[4] = { " /     \\" };
    appear_front[5] = { " |     |" };
    appear_front[6] = { "/       \\" };
    appear_front[7] = { "\\       /" };
    appear_front[8] = { " \\_____/" };
    currentRoom = nullptr;
    previousRoom = nullptr;
    
}

void Player::updatePlayerAppear()
{
    if (getCurrentHealth() < 80)
    {
        appear[1][2] = 'X';
        appear[2][6] = 'X';
        appear[3][4] = 'X';
    }
}
void Player::increaseStates(int atk_in, int def_in, int max_hp_in)
{
    setAttack(atk_in);
    setMaxHealth(max_hp_in);
    setDefense(def_in);
    return;
}

void Player::changeRoom(Room* next)
{
    previousRoom = currentRoom;
    currentRoom = next;
    return;
}

char Player::showStatus(int cursor)
{
    system("cls");
    printf("This is the status and backpack system");
    cout << endl << endl << endl;
    int left_space = 0;
    if (left_hand.getName() != "NULL")
        left_space = left_hand.getName().size();
    else
        left_space = 4;
    for (int k = 0; k < left_space + 4; k++)
    {
        cout << ' ';
    }
    cout << " [" << head.getName() << ']' << endl;
    for (int i = 0; i < 9; i++)
    {
        if (i != 4)
        {
            for (int k = 0; k < left_space + 4; k++)
            {
                cout << ' ';
            }
        }
        else if (i == 4)
        {
            cout << "  [" << left_hand.getName() << ']';
        }
        cout << appear_front[i];
        if (i == 4)
        {
            cout << " [" << right_hand.getName() << ']';
        }
        cout << endl;
    }
    for (int k = 0; k < left_space + 4; k++)
    {
        cout << ' ';
    }
    cout << " [" << body.getName() << ']' << endl;
    cout << endl << endl;
    cout << "    [" << getName() << "]" << endl;
    cout << "    > Health:" << getCurrentHealth() << "/" << getMaxHealth() << endl;
    cout << "    > Attack: " << getAttack() << endl;
    cout << "    > Defense: " << getDefense() << endl;
    cout << "    > Money: $" << o_ka_ne << endl;
    cout << "    > Items:" << endl;
    if (inventory.size() != 0)
    {
        cursor = cursor % inventory.size();
        for (int i = 0; i < inventory.size(); i++)
        {
            if (i == cursor)
            {
                printf("  ---> ");
            }
            else
            {
                printf("       ");
            }
            cout << "[" << getInventory()[i].getName();
            printf("] : ATK + %d, DEF + %d, HP + %d", getInventory()[i].getAttack(), getInventory()[i].getDefense(), getInventory()[i].getHealth());
            cout << endl;
        }
    }
    else
    {
        printf("    Empty inventory!");
    }
    cout << endl << "Enter w and s to control cursor, enter x to use, r to exit backpack." << endl;
    char input;
    cin >> input;
    if (input == 'x')
    {
        if (inventory[cursor].interactwith(this) == false)
        {
            inventory.erase(inventory.begin() + cursor);
        }
        input = 's';
    }
    return input;
}

bool Player::triggerEvent(Object* obj_in)
{
    if (obj_in->getTag() == "Folder")
    {
        Folder* fld = dynamic_cast<Folder*>(obj_in);
        string temp = fld->folder_name;
        for (int i = 0; i < (*room_of_plr).size(); i++)
        {
            if ((*room_of_plr)[i].folder_room_name == temp)
            {
                previousRoom = currentRoom;
                currentRoom = &(*room_of_plr)[i];
                return true;
            }
        }
    }
    else if (obj_in->getTag() == "Monster")
    {
        // things dat monster already does : draw monster
        drawPlayer();
        cout << "=======================================" << endl;
        // ask wat to do
        cout << "What do you want to do?" << endl;
        Monster* mnst = dynamic_cast<Monster*>(obj_in);
        for (int i = 0; i < does_player_has_all_abilities; i++)
        {
            cout << i << ". " << abilities[i].name_of_ability << endl;
        }
        cout << "p. Use Potions" << endl;
        cout << "r. Retreat" << endl;


        char what = '\0';
        cin >> what;
        if (what == 'r')
        {
            return false;
        }
        else if (what == 'p')
        {
            bool is_there_damage_potion = false;
            system("cls");
            int i = 0;
            for (i = 0; i < inventory.size(); i++)
            {
                if (inventory[i].getName() == "Damage_Potion")
                {
                    cout << i << ". Damage Potion : make 20 pts damage" << endl;
                    is_there_damage_potion = true;
                }
            }
            if (is_there_damage_potion == false)
            {
                cout << "No potions which can be used on monsters" << endl;
                system("pause");
                return true;
            }
            int select = -87;
            cout << endl << "Enter index to select." << endl;
            cin >> select;
            inventory.erase(inventory.begin() + select);
            mnst->setCurrentHealth(mnst->getCurrentHealth() - 20);
            mnst->updateMonsterAppearence();
            mnst->drawMonster();
            drawPlayer();
            cout << "=======================================" << endl;
            cout << "Made " << 20 << " points damage to \"" << mnst->getName() << "\"" << endl;
            cout << "Enter any key to continue.";
            char temp;
            cin >> temp;
            return true;

        }
        else if (what == '0')
        {
            mnst->setCurrentHealth(mnst->getCurrentHealth() - attack);
            mnst->updateMonsterAppearence();
            mnst->drawMonster();
            drawPlayer();
            cout << "=======================================" << endl;
            cout << "Made " << attack << " points damage to \"" << mnst->getName() << "\"" << endl;
            cout << "Enter any key to continue.";
            char temp;
            cin >> temp;
            return true;
        }
        else if (what == '1')
        {
            setCurrentHealth(currentHealth + 5);
            mnst->drawMonster();
            drawPlayer();
            cout << "=======================================" << endl;
            cout << "Player's HP increased by 5" << endl;
            cout << "Enter any key to continue.";
            char temp;
            cin >> temp;
            return true;
        }
        else if (what == '2')
        {
            setAttack(getAttack() + 10);
            mnst->drawMonster();
            drawPlayer();
            cout << "=======================================" << endl;
            cout << "Player's ATK increased by 10" << endl;
            cout << "Enter any key to continue.";
            char temp;
            cin >> temp;
            return true;

        }
        else if (what == '3')
        {
            mnst->setCurrentHealth(mnst->getCurrentHealth() - attack*2);
            mnst->updateMonsterAppearence();
            mnst->drawMonster();
            cout << "=======================================" << endl;
            cout << "Made " << attack*2 << " points damage to \"" << mnst->getName() << "\"" << endl;
            cout << "Enter any key to continue.";
            char temp;
            cin >> temp;
            return true;

        }
    }
    else if (obj_in->getTag() == "Item")
    {
        //erase obj from room obj and give plyr obj
        Item* new_item = dynamic_cast<Item*>(obj_in);
        inventory.insert(inventory.begin(), *new_item);
        currentRoom->blocksInRoom[deal_Y][deal_X].can_walk = true;
        currentRoom->blocksInRoom[deal_Y][deal_X].object_display = ' ';
        currentRoom->blocksInRoom[deal_Y][deal_X].obj_on_block = nullptr;
        for (int i = 0; i < currentRoom->objects.size(); i++)
        {
            if (currentRoom->objects.at(i) == obj_in)
            {
                currentRoom->objects.erase(currentRoom->objects.begin() + i);
            }
        }
        
        //setAttack(getAttack() + new_item->getAttack());
        //setDefense(getDefense() + new_item->getDefense());
        system("cls");
        cout << "Player [" << getName() << "] gets item [" << obj_in->getName() << "] !!" << endl;
        cout << "\n\nATK: " << new_item->getAttack() << "\nDEF: " << new_item->getDefense() << "\nHP: " << new_item->getHealth() << endl;
        cout << "Item is now in your inventory" << endl << "Enter any key to continue :";
        char c;
        cin >> c;
    }
    else if (obj_in->getTag() == "Boss")
    {
    // things dat monster already does : draw monster
    drawPlayer();
    cout << "=======================================" << endl;
    // ask wat to do
    cout << "What do you want to do?" << endl;
    Boss* mnst = dynamic_cast<Boss*>(obj_in);
    for (int i = 0; i < does_player_has_all_abilities; i++)
    {
        cout << i << ". " << abilities[i].name_of_ability << endl;
    }
    cout << "r. Retreat" << endl;
    char what = '\0';
    cin >> what;
    if (what == 'r')
    {
        return false;
    }
    else if (what == 'F')
    {
        mnst->unlockAll();
    }
    else if (what == '0')
    {
        mnst->setCurrentHealth(mnst->getCurrentHealth() - attack);
        
        mnst->drawBoss();
        drawPlayer();
        cout << "=======================================" << endl;
        cout << "Made " << attack << " points damage to \"" << mnst->getName() << "\"" << endl;
        cout << "Enter any key to continue.";
        char temp;
        cin >> temp;
        return true;
    }
    else if (what == '1')
    {
        setCurrentHealth(currentHealth + 5);
        mnst->drawBoss();
        drawPlayer();
        cout << "=======================================" << endl;
        cout << "Player's HP increased by 5" << endl;
        cout << "Enter any key to continue.";
        char temp;
        cin >> temp;
        return true;
    }
    else if (what == '2')
    {
        setAttack(getAttack() + 10);
        mnst->drawBoss();
        drawPlayer();
        cout << "=======================================" << endl;
        cout << "Player's ATK increased by 10" << endl;
        cout << "Enter any key to continue.";
        char temp;
        cin >> temp;
        return true;

    }
    else if (what == '3')
    {
        mnst->setCurrentHealth(mnst->getCurrentHealth() - attack * 2);
        //mnst->updateMonsterAppearence();
        mnst->drawBoss();
        cout << "=======================================" << endl;
        cout << "Made " << attack * 2 << " points damage to \"" << mnst->getName() << "\"" << endl;
        cout << "Enter any key to continue.";
        char temp;
        cin >> temp;
        return true;

    }
    }
    else if (obj_in->getTag() == "Item")
    {
    //erase obj from room obj and give plyr obj
    Item* new_item = dynamic_cast<Item*>(obj_in);
    inventory.insert(inventory.begin(), *new_item);
    currentRoom->blocksInRoom[deal_Y][deal_X].can_walk = true;
    currentRoom->blocksInRoom[deal_Y][deal_X].object_display = ' ';
    currentRoom->blocksInRoom[deal_Y][deal_X].obj_on_block = nullptr;
    for (int i = 0; i < currentRoom->objects.size(); i++)
    {
        if (currentRoom->objects.at(i) == obj_in)
        {
            currentRoom->objects.erase(currentRoom->objects.begin() + i);
        }
    }

    //setAttack(getAttack() + new_item->getAttack());
    //setDefense(getDefense() + new_item->getDefense());
    system("cls");
    cout << "Player [" << getName() << "] gets item [" << obj_in->getName() << "] !!" << endl;
    cout << "\n\nATK: " << new_item->getAttack() << "\nDEF: " << new_item->getDefense() << "\nHP: " << new_item->getHealth() << endl;
    cout << "Item is now in your inventory" << endl << "Enter any key to continue :";
    char c;
    cin >> c;
    }

    else if (obj_in->getTag() == "NPC")
    {
        // things dat monster already does : draw monster
        drawPlayer();
        cout << "========================================================" << endl;
        // ask wat to do
        NPC* npc = dynamic_cast<NPC*>(obj_in);
        cout << "[" << npc->getName() << "] : " << npc->script[0];

        char what = '\0';
        cin >> what;
        if (what == 'r')
        {
            return false;
        }
        else if (what == 'c')
        {
            cout << "[" << npc->getName() << "] : " << npc->script[2] << endl;
            cin >> what;
            if (what == 'b')
            {
                cout << "[" << npc->getName() << "] : " << npc->script[3] << endl;
                cin >> what;
                if (what == 'r')
                {
                    return false;
                }
            }
            else if (what == 'a')
            {
                cout << "[" << npc->getName() << "] : " << npc->script[4] << endl;
                // get new ablitiy
                does_player_has_all_abilities = 4;
                cin >> what;
                if (what == 'r')
                {
                    return false;
                }
            }
            return true;
        }
        else if (what == 's')
        {
            int cursor = 0;
            char temmp = '\0';
            while (1)
            {                
                npc->drawNPC();
                drawPlayer();
                cout << "===============================================" << endl;
                npc->listCommodity(cursor);
                cout << "You have : $" << o_ka_ne;
                cout << endl << "Enter w and s to control cursor, x to buy item and r to cancel\n";
                cin >> temmp;
                if (temmp == 'w')
                {
                    cursor--;
                }
                else if (temmp == 's')
                {
                    cursor++;
                }
                else if (temmp == 'x')
                {
                    npc->buyDaItem(cursor, this);
                }
                else if (temmp == 'r')
                {
                    break;
                }
            }
        }
    }
    return true;
}
void Player::checkIfPlayerIsDead()
{
    if (currentHealth <= 0)
    {
        cout << "Player [" << getName() << "] is dead, game over!";
        exit(0);
    }
    return;
    
}
void Player::drawPlayer()
{
    cout << "     " << '[' << getName() << ']' << endl;
    cout << "  ATK: " << attack << "   DEF: " << defense << "   HP: " << currentHealth << endl;
    cout << "  HP: [";
    for (int i = 0; i < currentHealth / 10; i++)
    {
        cout << '=';
    }
    for (int i = 0; i < 10 - (currentHealth / 10); i++)
    {
        cout << ' ';
    }
    cout << "]" << endl;
    for (int i = 0; i < 9; i++)
    {
        cout << "   " << appear[i] << endl;
    }
    return;
}
/*
     ^
   //
  //
 //
//
            
          |\__/|
          ) . .(       
         =\  ^ /=         ^   ^
           )===(          //  \\
          /     \        //    \\
          |     |       //      \\
         /       \     //        \\
         \       / ====O===== ====O=====
          \_____/     //           \\
*/                    
void Player::setCurrentRoom(Room* cur_room_in)
{
    currentRoom = cur_room_in;
    return;
}

void Player::setPreviousRoom(Room* prev_room_in)
{
    previousRoom = prev_room_in;
    return;
}

bool Player::setRoomXY(int x, int y)
{
    if (currentRoom->blocksInRoom[y][x].can_walk == true)
    {
        currentRoom->blocksInRoom[player_room_Y][player_room_X].obj_on_block = nullptr;
        currentRoom->blocksInRoom[player_room_Y][player_room_X].can_walk = true;
        currentRoom->blocksInRoom[player_room_Y][player_room_X].object_display = ' ';
        player_room_X = x;
        player_room_Y = y;
        currentRoom->blocksInRoom[y][x].obj_on_block = this;
        currentRoom->blocksInRoom[y][x].can_walk = false;
        currentRoom->blocksInRoom[y][x].object_display = 'P';
        return true;
    }
    else
    {
        if (currentRoom->blocksInRoom[y][x].obj_on_block != nullptr)
        {
            deal_X = x;
            deal_Y = y;
            currentRoom->blocksInRoom[y][x].obj_on_block->triggerEvent(this);

        }
        return false;
    }
}

void Player::setInventory(vector<Item> inventory_in)
{
    inventory = inventory_in;
    return;
}

Room* Player::getCurrentRoom()
{
    return currentRoom;
}

Room* Player::getPreviousRoom()
{
    return previousRoom;
}

vector<Item> Player::getInventory()
{
    return inventory;
}