#include <SFML/Graphics.hpp>
#include <string>
#include "Hero.h"

void Hero::set_texture(sf::Sprite sp, int cost_hero, int number_hero)
{
	hero.setTexture(*sp.getTexture());
	//set_cost_num(cost_hero, number_hero);
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
	if (number == 1 || number == 5 || number == 9 || number == 10)
	{
		health = 3;
		attack_val = 1;
	}
	else if (number == 2)
	{
		health = 1;
		attack_val = 3;
	}
	else if (number == 3 || number == 4 || number == 7)
	{
		health = 2;
		attack_val = 1;
	}
	else switch (number)
	{
	case 6:
		health = 3;
		attack_val = 2;
		break;
	case 8:
		health = 2;
		attack_val = 2;
		break;
	case 11:
		health = 6;
		attack_val = 1;
		break;
	case 12:
		health = 4;
		attack_val = 2;
		break;
	case 13:
		health = 5;
		attack_val = 4;
		break;
	case 14:
		health = 7;
		attack_val = 2;
		break;
	}
}

bool Hero::hero_attacked()
{
	if (hero_already_attacked)
	{
		return hero_already_attacked;
	}
	else
	{
		hero_already_attacked = true;
		return !hero_already_attacked;
	}
}

void Hero::refresh_attack()
{
	hero_already_attacked = false;
}

void Hero::set_red_color()
{
	hero.setColor(sf::Color(255, 100, 100));
}

void Hero::set_green_color()
{
	hero.setColor(sf::Color(100, 255, 100));
}

void Hero::return_color()
{
	hero.setColor(sf::Color(255, 255, 255));
}