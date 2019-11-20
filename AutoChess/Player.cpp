#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <Windows.h>
#include <string>

//using namespace sf;
//using namespace std;

bool Player::buy_hero(int hero_number)
{
	int minus = 0;
	if (hero_number <= 5)
	{
		minus = 1;
	}
	else if (hero_number <= 9)
	{
		minus = 2;
	}
	else if (hero_number <= 12)
	{
		minus = 3;
	}
	else if (hero_number <= 14)
	{
		minus = 4;
	}
	if (golds - minus < 0)
	{
		return false;
	}
	if (count_heroes < 3)
	{
		for (int i = 0; i < 3; i++)
		{
			if (heroes[i] == 0)
			{
				heroes[i] = hero_number;
				golds = golds - minus;
				count_heroes++;
				return true;
			}
		}
	}
	return false;
}

void Player::sell_hero(int number)
{
	int hero_number = heroes[number];
	int minus;
	if (hero_number <= 5)
	{
		minus = 1;
	}
	else if (hero_number <= 9)
	{
		minus = 2;
	}
	else if (hero_number <= 12)
	{
		minus = 3;
	}
	else if (hero_number <= 14)
	{
		minus = 4;
	}
	golds = golds + minus;
	heroes[number] = 0;
	count_heroes--;
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

void Player::up_level()
{
	if (store_level == 4) return;
	store_level++;
}

std::string Player::get_amount_gold()
{
	std::string gold = std::to_string(golds);
	return gold;
}