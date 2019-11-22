#include <SFML/Graphics.hpp>
#include <string>
#include "Hero.h"

Hero::Hero(sf::Sprite hero)
{
	sprite_hero = hero;
}

int Hero::attack()
{
	return attack_val;
}

void Hero::buff_hero(int up_attack, int up_health)
{
	attack_val += up_attack;
	health += up_health;
}

void Hero::hero_attacked(int attack_vl)
{
	health -= attack_vl;
}

bool Hero::hero_died()
{
	return health <= 0;
}

std::string Hero::get_attack()
{
	return std::to_string(attack_val);
}

std::string Hero::get_health()
{
	return std::to_string(health);
}