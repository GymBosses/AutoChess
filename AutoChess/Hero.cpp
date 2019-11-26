#include <SFML/Graphics.hpp>
#include <string>
#include "Hero.h"

void Hero::set_texture(sf::Sprite sp, int cost_hero, int number_hero)
{
	hero.setTexture(*sp.getTexture());
	health = 10;
	attack_val = 10;
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

void Hero::attack_this_hero(int attack_vl)
{
	health -= attack_vl;
}

bool Hero::hero_died()
{
	if (health > 0) return false;
	sf::Sprite temp;
	hero = temp;
	return true;
}

int Hero::get_number()
{
	return number;
}

int Hero::get_cost()
{
	return cost;
}

std::string Hero::get_attack()
{
	return std::to_string(attack_val);
}

std::string Hero::get_health()
{
	return std::to_string(health);
}

sf::Sprite Hero::get_sprite()
{
	return hero;
}

void Hero::set_position(sf::Vector2f pos)
{
	hero.setPosition(pos);
}

void Hero::set_cost_num(int cost_hero, int num_hero)
{
	if (cost_hero == 0)
	{
		sf::Sprite temp;
		hero = temp;
	}
	cost = cost_hero;
	number = num_hero;
}

bool Hero::hero_attacked()
{
	return hero_already_attacked;
}

void Hero::refresh_attack()
{
	hero_already_attacked = false;
}