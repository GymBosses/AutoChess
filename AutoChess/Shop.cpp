#include <SFML/Graphics.hpp>
#include "Shop.h"
#include <iostream>
#include <Windows.h>
#include <string>

using namespace sf;
using namespace std;

Shop::Shop(Sprite* heroes)
{
	for (int i = 1; i < 15; i++)
	{
		all_heroes[i] = heroes[i];
	}
}

void Shop::set_heroes(int max_level_shop)
{
	int temp_hero;
	max_level = max_level_shop;
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		temp_hero = rand() % max_level + 1;
		showcase[i] = all_heroes[temp_hero];
	}
	store_full = true;
}

void Shop::refresh()
{
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		showcase[i].setTexture(*all_heroes[i].getTexture());
	}
	store_full = true;
}

void Shop::set_pos_all_items(int* store_position)
{
	for (int i = 0; i < 4; i++)
	{
		showcase[i].setPosition(store_position[i], store_position[4]);
	}
}

Vector2f Shop::get_pos(int num)
{
	return showcase[num].getPosition();
}

void Shop::set_pos(int num, int x, int y)
{
	showcase[num].setPosition(x, y);
}

bool Shop::check_point(int num, Vector2i pos)
{
	if (showcase[num].getGlobalBounds().contains(pos.x, pos.y))
	{
		return true;
	}
	return false;
}

Sprite Shop::get_item(int num)
{
	return showcase[num];
}

void Shop::move_item(int num, Vector2f pos)
{
	showcase[num].setPosition(pos.x, pos.y);
}

bool Shop::check_item_on_field(int num, int scrX, int scrY)
{
	if (showcase[num].getPosition().y < int(0.70 * scrY) &&
		showcase[num].getPosition().y > int(0.30 * scrY))
	{
		return true;
	}
	return false;
}

int Shop::get_num_hero(int num)
{
	for (int i = 1; i < 15; i++)
	{
		if (showcase[num].getTexture() == all_heroes[i].getTexture())
		{
			return i;
		}
	}
}