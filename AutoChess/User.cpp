#include <SFML/Graphics.hpp>
#include "Player.h"
#include "User.h"

void User::set_sprite_hero(sf::Sprite sp, sf::Vector2f pos, int num)
{
	heroes[num].set_texture(sp);
	heroes[num].set_position(pos);
}

bool User::refresh()
{
	if (golds == 0)
	{
		return false;
	}
	return golds--;
}

std::string User::get_amount_gold()
{
	std::string gold = std::to_string(golds);
	return gold;
}


bool User::up_level()
{
	int minus;
	switch (store_level)
	{
	case 1:
		minus = 3;
		break;
	case 2:
		minus = 4;
		break;
	case 3:
		minus = 5;
		break;
	case 4:
		minus = 6;
		break;
	default:
		return false;
	}

	if (golds - minus < 0 || store_level == 4)
	{
		return false;
	}
	store_level++;
	golds = golds - minus;
	return true;
}

std::string User::upgrade_cost()
{
	switch (store_level)
	{
	case 1:
		return "3";
	case 2:
		return "4";
	default:
		return "5";
	}
	return "";
}
