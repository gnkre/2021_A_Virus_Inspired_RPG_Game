#include "Item.h"
#include "Player.h"

Item::Item()
{
    setName("NULL");
    attack = 0;
    defense = 0;
    health = 0;
    value = 0;
    setTag("Item");
}

Item::Item(string name_in, int atk_in, int def_in, int hp_in, int value_in)
{
    setTag("Item");
    setName(name_in);
    health = hp_in;
    attack = atk_in;
    defense = def_in;
    value = value_in;
}
bool Item::interactwith(Player* plr_in)
{
    if (getName().find("Health_Potion") != std::string::npos)
    {
        plr_in->currentHealth = plr_in->currentHealth + this->health;
        if (plr_in->currentHealth > plr_in->maxHealth)
        {
            plr_in->currentHealth = plr_in->maxHealth;
        }
        return false;
    }
    else if (getName() == "Damage_Potion")
    {
        cout << "This potion can only be used on monster to make damage." << endl;
        system("pause");
    }
    else if (getName().find("Sword") != string::npos)
    {
        if (plr_in->left_hand.getName() == this->getName())
        {
            plr_in->attack = plr_in->attack - plr_in->left_hand.attack;
            plr_in->left_hand = Item();
        }
        else if (plr_in->right_hand.getName() == this->getName())
        {
            plr_in->attack = plr_in->attack - plr_in->right_hand.attack;
            plr_in->right_hand = Item();
        }
        //clear the screen and ask where to hold
        system("cls");
        cout << endl << endl << "Which hand do you want to hold this weapon?" << endl;
        cout << "a.Left hand\nb.Right hand\n";
        char temp = '\0';
        cin >> temp;
        if (temp == 'a')
        {
            if (plr_in->left_hand.getName() != "NULL")
            {
                plr_in->attack = plr_in->attack - plr_in->left_hand.attack;
            }
            plr_in->left_hand = *this;
            plr_in->attack = plr_in->attack + attack;
        }
        else if (temp == 'b')
        {
            if (plr_in->right_hand.getName() != "NULL")
            {
                plr_in->attack = plr_in->attack - plr_in->right_hand.attack;
            }
            plr_in->right_hand = *this;
            plr_in->attack = plr_in->attack + attack;
        }
        return true;
    }
    else if (getName().find("Hat") != std::string::npos)
    {
        if (plr_in->head.getName() == "NULL")
        {
            plr_in->head = *this;
            plr_in->maxHealth = plr_in->maxHealth + this->health;

        }
        else if (plr_in->head.getName() == this->getName())
        {
            plr_in->maxHealth = plr_in->maxHealth - plr_in->head.health;
            plr_in->head = Item();
        }
        else if (plr_in->head.getName() != this->getName())
        {
            plr_in->maxHealth = plr_in->maxHealth - plr_in->head.health;
            plr_in->maxHealth = plr_in->maxHealth + this->health;
            plr_in->head = *this;
            if (plr_in->currentHealth > plr_in->maxHealth)
            {
                plr_in->currentHealth = plr_in->maxHealth;
            }

        }
        return true;
    }
    else if (getName().find("Armor") != std::string::npos)
    {
        if (plr_in->body.getName() == "NULL")
        {
            plr_in->body = *this;
            plr_in->defense = plr_in->defense + this->defense;

        }
        else if (plr_in->body.getName() == this->getName())
        {
            
            plr_in->defense = plr_in->defense - plr_in->body.defense;
            plr_in->body = Item();
        }
        else if (plr_in->body.getName() != this->getName())
        {
            plr_in->defense = plr_in->defense - plr_in->body.defense;
            plr_in->defense = plr_in->defense + this->defense;
            plr_in->body = *this;
            

        }
        return true;
    }
    else if (getName().find("Key") != string::npos)
    {
        return true;
    }
    return true;
}
bool Item::triggerEvent(Object* obj_in)
{
    if (obj_in->getTag() == "Player")
    {
        Player* player = dynamic_cast<Player*>(obj_in);
        player->triggerEvent(this);
    }
    return false;
}

int Item::getAttack()
{
    return attack;
}

int Item::getDefense()
{
    return defense;
}

int Item::getHealth()
{
    return health;
}

void Item::setHealth(int hp_in)
{
    health = hp_in;
    return;
}

void Item::setDefense(int def_in)
{
    defense = def_in;
    return;
}

void Item::setAttack(int atk_in)
{
    attack = atk_in;
    return;
}

