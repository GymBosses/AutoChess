#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <string>

//using namespace sf;
//using namespace std;


sf::Sprite Player::get_item(int num)
{
	return heroes[num].get_sprite();
}

bool Player::buy_hero(int hero_number)
{
	int cost = 0;
	if (hero_number <= 5)
	{
		cost = 1;
	}
	else if (hero_number <= 9)
	{
		cost = 2;
	}
	else if (hero_number <= 12)
	{
		cost = 3;
	}
	else if (hero_number <= 14)
	{
		cost = 4;
	}
	if (golds - cost < 0)
	{
		return false;
	}
	if (count_heroes < 3)
	{
		for (int i = 0; i < 3; i++)
		{
			if (!heroes[i].hero_died())
			{
				heroes[i].set_cost_num(cost, hero_number);
				golds = golds - cost;
				count_heroes++;
				return true;
			}
		}
	}
	return false;
}

int Player::num_max_level_heroes()
{
	switch (store_level)
	{
	case 1:
		return 5;
		break;
	case 2:
		return 9;
		break;
	case 3:
		return 12;
		break;
	case 4:
		return 14;
		break;
	}
	store_level = 4;
	return 14;
}

void Player::sell_hero(int number)
{
	int hero_number = heroes[number].get_number();
	int cost = 0;
	if (hero_number <= 5)
	{
		cost = 1;
	}
	else if (hero_number <= 9)
	{
		cost = 2;
	}
	else if (hero_number <= 12)
	{
		cost = 3;
	}
	else if (hero_number <= 14)
	{
		cost = 4;
	}
	golds = golds + cost;
	heroes[number].set_cost_num(0, 0);
	count_heroes--;
}