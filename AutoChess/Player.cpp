#include <SFML/Graphics.hpp>
#include "Player.h"
using namespace sf;

bool Player::buy_hero(int hero_number)
{
	if (hero_number <= 5)
	{
		if (golds >= 1)
		{
			if (count_heroes <= 3)
			{
				heroes[count_heroes++] = hero_number;
				return true;
			}
		}
	}
	else if (hero_number <= 9)
	{
		if (golds >= 2)
		{
			if (count_heroes <= 3)
			{
				heroes[count_heroes++] = hero_number;
				return true;
			}
		}
	}
	else if (hero_number <= 12)
	{
		if (golds >= 3)
		{
			if (count_heroes <= 3)
			{
				heroes[count_heroes++] = hero_number;
				return true;
			}
		}
	}
	else if (hero_number <= 14)
	{
		if (golds >= 4)
		{
			if (count_heroes <= 3)
			{
				heroes[count_heroes++] = hero_number;
				return true;
			}
		}
	}
	return false;
}

void Player::sell_hero(int number)
{
	if (number >= 1 && count_heroes <= number)
	{
		heroes[number] = 0; 
	}
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