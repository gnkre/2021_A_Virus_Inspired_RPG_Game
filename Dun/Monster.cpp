#include "Monster.h"

Monster::Monster()
{
    setName("NULL");
}


void Monster::unlock()
{
    
    rename(real_name.c_str(), real_name.substr(0, real_name.find(".zzzzzzzzz")).c_str());
    return;
}
Monster::Monster(bool is_infected, string real_name_in, string name_in, int atk_in, int def_in, int max_hp_in)
{
    setName(name_in);
    real_name = real_name_in;
    setTag("Monster");
    setAttack(atk_in);
    setDefense(def_in);
    setMaxHealth(max_hp_in);
    setCurrentHealth(max_hp_in);
    is_infected = is_infected;
    pixels[0] = { "-----------" };
    pixels[1] = { "|         |" };
    pixels[2] = { "|  X.X    |" };
    pixels[3] = { "|         |" };
    pixels[4] = { "|         |" };
    pixels[5] = { "|         |" };
    pixels[6] = { "-----------" };
}
bool Monster::checkIfIsDead()
{
    if (currentHealth <= 0)
    {
        // TODO : deal with the change name function
        return true;
    }
    return false;
}
bool Monster::triggerEvent(Object* obj_in)
{
    if (obj_in->getTag() == "Player")
    {
        Player* player = dynamic_cast<Player*>(obj_in);

        drawMonster();
        while (player->triggerEvent(this) == true)
        {
            drawMonster();
            //player func will deal w/ the blood of monster
            //player->triggerEvent(this);
            player->drawPlayer();
            cout << "=======================================" << endl;
            updateMonsterAppearence();
            if (checkIfIsDead() == true)
            {
                cout << "You defeat the inflected file, \nthe file is now avaliable for you." << endl;
                unlock();
                player->currentRoom->blocksInRoom[player->deal_Y][player->deal_X].object_display = ' ';
                player->currentRoom->blocksInRoom[player->deal_Y][player->deal_X].can_walk = true;
                Object* temptr = player->currentRoom->blocksInRoom[player->deal_Y][player->deal_X].obj_on_block;

                for (auto itr = player->currentRoom->objects.begin(); itr != player->currentRoom->objects.end(); itr++)
                {
                    if (temptr == *itr)
                    {
                        player->currentRoom->objects.erase(itr);
                        break;
                    }
                }
                player->currentRoom->blocksInRoom[player->deal_Y][player->deal_X].obj_on_block = nullptr;

                char temp = '\0';
                cin >> temp;
                break;
            }
            player->currentHealth = player->currentHealth - attack;
            drawMonster();
            player->drawPlayer();
            cout << "=======================================" << endl;
            cout << "Inflected \"" << getName() << "\" made " << attack << " points damage to " << "[" << player->getName() << "]" << endl;
            cout << "Enter any key to continue.";
            char temp;
            cin >> temp;
            player->checkIfPlayerIsDead();
            drawMonster();
        }
    }
    return true;
}
void Monster::updateMonsterAppearence()
{
    if (getCurrentHealth() > 40)
    {
        return;
    }
    else if (getCurrentHealth() <= 40 && getCurrentHealth() >= 20)
    {
        pixels[1][1] = 'X';
        pixels[1][8] = 'X';
        pixels[4][6] = 'X';
        pixels[5][2] = 'X';
        pixels[5][9] = 'X';
    }
    else if (getCurrentHealth() < 20)
    {
        pixels[1][5] = 'X';
        pixels[2][7] = 'X';
        pixels[3][2] = 'X';
        pixels[3][9] = 'X';
        pixels[4][4] = 'X';
        pixels[5][5] = 'X';
    }
    return;
}

Boss::Boss(vector<Monster*> ever)
{
    every = ever;
    pixels[0] = { "                                                __----~~~~~~~~~~~------____" };
    pixels[1] = { "                                   .  .   ~~//====......          __--~ ~~ " };
    pixels[2] = { "                   -.            \_|//     |||\\  ~~~~~~::::... /~         " };
    pixels[3] = { "                   -.            \_|//     |||\\  ~~~~~~::::... /~         " };
    pixels[4] = { "                ___-==_       _-~o~  \/    |||  \\            _/~~-        " };
    pixels[5] = { "        __---~~~.==~||\=_    -_--~/_-~|-   |\\   \\        _/~             " };
    pixels[6] = { "    _-~~     .=~    |  \\-_    '-~7  /-   /  ||    \      /                " };
    pixels[7] = { "  .~       .~       |   \\ -_    /  /-   /   ||      \   /                 " };
    pixels[8] = { " /  ____  /         |     \\ ~-_/  /|- _/   .||       \ /                  " };
    pixels[9] = { " |~~    ~~|--~~~~--_ \     ~==-/   | \~--===~~        .\                   " };
    pixels[10] = { "          '         ~-|      /|    |-~\~~       __--~~                     " };
    pixels[11] = { "                      |-~~-_/ |    |   ~\_   _-~            /\             " };
    pixels[12] = { "                           /  \     \__   \/~                \__           " };
    pixels[13] = { "                       _--~ _/ | .-~~____--~-/                  ~~==.      " };
    pixels[14] = { "                      ((->/~   '.|||' -_|    ~~-/ ,              . _||     " };
    pixels[15] = { "                                 -_     ~\      ~~---l__i__i__i--~~_/      " };
    pixels[16] = { "                                 _-~-__   ~)  \--______________--~~        " };
    pixels[17] = { "                               //.-~~~-~_--~- |-------~~~~~~~~             " };
    pixels[18] = { "                                      //.-~~~--\)                          " };

    setName("The Virus");
    setTag("Boss");
    
    setMaxHealth(50);
    setCurrentHealth(50);
    setAttack(30);
    setDefense(10);
}

Boss::Boss(int hp, vector<Monster*> ever)
{
    every = ever;
    pixels[0] = { "                                                __----~~~~~~~~~~~------____" };
    pixels[1] = { "                                   .  .   ~~//====......          __--~ ~~ " };
    pixels[2] = { "                   -.            \_|//     |||\\  ~~~~~~::::... /~         " };
    pixels[3] = { "                   -.            \_|//     |||\\  ~~~~~~::::... /~         " };
    pixels[4] = { "                ___-==_       _-~o~  \/    |||  \\            _/~~-        " };
    pixels[5] = { "        __---~~~.==~||\=_    -_--~/_-~|-   |\\   \\        _/~             " };
    pixels[6] = { "    _-~~     .=~    |  \\-_    '-~7  /-   /  ||    \      /                " };
    pixels[7] = { "  .~       .~       |   \\ -_    /  /-   /   ||      \   /                 " };
    pixels[8] = { " /  ____  /         |     \\ ~-_/  /|- _/   .||       \ /                  " };
    pixels[9] = { " |~~    ~~|--~~~~--_ \     ~==-/   | \~--===~~        .\                   " };
    pixels[10] = { "          '         ~-|      /|    |-~\~~       __--~~                     " };
    pixels[11] = { "                      |-~~-_/ |    |   ~\_   _-~            /\             " };
    pixels[12] = { "                           /  \     \__   \/~                \__           " };
    pixels[13] = { "                       _--~ _/ | .-~~____--~-/                  ~~==.      " };
    pixels[14] = { "                      ((->/~   '.|||' -_|    ~~-/ ,              . _||     " };
    pixels[15] = { "                                 -_     ~\      ~~---l__i__i__i--~~_/      " };
    pixels[16] = { "                                 _-~-__   ~)  \--______________--~~        " };
    pixels[17] = { "                               //.-~~~-~_--~- |-------~~~~~~~~             " };
    pixels[18] = { "                                      //.-~~~--\)                          " };

    setName("The Virus");
    setTag("Boss");
    setCurrentHealth(hp);
    setMaxHealth(50);
    setAttack(30);
    setDefense(10);
}
void Boss::unlockAll()
{
    for (vector<Monster*>::iterator itr = every.begin(); itr != every.end(); itr++)
    {
        (*(*itr)).unlock();
    }
    return;
}

void Boss::drawBoss()
{
    system("cls");
    //cout << endl << endl;
    cout << "==============================================================================" << endl;
    cout << "                                                       [The Virus]" << endl;

    cout << "\t\t\tATK: " << attack << "   DEF: " << defense << "   HP: " << currentHealth << endl;

    for (int i = 0; i < 19; i++)
    {
        cout << "                       " << pixels[i] << endl;
    }
    return;
}

bool Boss::triggerEvent(Object* obj_in)
{
    if (obj_in->getTag() == "Player")
    {
        Player* player = dynamic_cast<Player*>(obj_in);
        drawBoss();
        while (player->triggerEvent(this) == true)
        {
            drawBoss();
            //player func will deal w/ the blood of monster
            //player->triggerEvent(this);
            player->drawPlayer();
            cout << "==============================================================================" << endl;
            //updateMonsterAppearence();
            if (currentHealth <= 0)
            {
                system("cls");
                cout << "You defeat the boss, \n all the file is now avaliable for you.\n Congrats!!\n Enter any key to continue" << endl;
                unlockAll();
                char temp = '\0';
                cin >> temp;
                exit(0);
                break;
            }
            player->currentHealth = player->currentHealth - attack;
            drawBoss();
            player->drawPlayer();
            cout << "==============================================================================" << endl;
            cout << "Inflected \"" << getName() << "\" made " << attack << " points damage to " << "[" << player->getName() << "]" << endl;
            cout << "Enter any key to continue.";
            
            char temp;
            cin >> temp;
            player->checkIfPlayerIsDead();
            drawBoss();
        }
    }
    return true;
}


void Monster::drawMonster()
{
    system("cls");
    //cout << endl << endl;
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
    cout << "\t\t\tATK: " << attack << "   DEF: " << defense << "   HP: " << currentHealth << endl;

    for (int i = 0; i < 7; i++)
    {
        cout << "                       " << pixels[i] << endl;
    }
    return;
}