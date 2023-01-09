#include "GameCharacter.h"

GameCharacter::GameCharacter()
{
    name = "NULL";
}

GameCharacter::GameCharacter(string name, string tag, int max_hp_in, int atk_in, int def_in)
{
    name = name;
    maxHealth = max_hp_in;
    currentHealth = max_hp_in;
    attack = atk_in;
    defense = def_in;
    setName(name);
    setTag(tag);
}

bool GameCharacter::checkIsDead()
{
    if (currentHealth == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int GameCharacter::takeDamage(int damage_in)
{
    currentHealth = currentHealth - damage_in;
    return currentHealth;
}

int GameCharacter::getAttack()
{
    return attack;
}

int GameCharacter::getDefense()
{
    return defense;
}

int GameCharacter::getCurrentHealth()
{
    return currentHealth;
}

int GameCharacter::getMaxHealth()
{
    return maxHealth;
}

void GameCharacter::setDefense(int def_in)
{
    defense = def_in;
    return;
}

void GameCharacter::setCurrentHealth(int cur_hp_in)
{
    if (cur_hp_in >= maxHealth)
    {
        currentHealth = maxHealth;
    }
    else
        currentHealth = cur_hp_in;
    return;
}

void GameCharacter::setAttack(int atk_in)
{
    attack = atk_in;
    return;
}

void GameCharacter::setMaxHealth(int max_hp_in)
{
    maxHealth = max_hp_in;
    return;
}
