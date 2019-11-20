#include <SFML/Graphics.hpp>
#include "Shop.h"
#include <iostream>
#include <Windows.h>
#include <string>

//using namespace sf;
//using namespace std;

Shop::Shop(sf::Sprite* heroes)
{
	for (int i = 1; i < 15; i++)
	{
		all_heroes[i] = heroes[i];
	}
	player_choice = -1;
	store_full = false;
	max_level = 0;
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
	int temp_hero;
	srand(time(NULL));
	for (int i = 0; i < 4; i++)
	{
		temp_hero = rand() % max_level + 1;
		showcase[i].setTexture(*all_heroes[temp_hero].getTexture());
	}
	store_full = true;
}

void Shop::set_pl_ch(int num)
{
	player_choice = num;
}

void Shop::set_pos_all_items(int* store_position)
{
	for (int i = 0; i < 4; i++)
	{
		showcase[i].setPosition(store_position[i], store_position[4]);
	}
}

sf::Vector2f Shop::get_pos()
{
	return showcase[player_choice].getPosition();
}

void Shop::set_pos(int x, int y)
{
	showcase[player_choice].setPosition(x, y);
}

bool Shop::check_point(int num, sf::Vector2i pos)
{
	return showcase[num].getGlobalBounds().contains(pos.x, pos.y) && player_choice == -1;
}

sf::Sprite Shop::get_item(int num)
{
	return showcase[num];
}

void Shop::move_item(sf::Vector2f pos)
{
	showcase[player_choice].setPosition(pos.x, pos.y);
}

bool Shop::check_item_on_field(int scrX, int scrY)
{
	return showcase[player_choice].getPosition().y < int(0.70 * scrY) &&
		showcase[player_choice].getPosition().y > int(0.30 * scrY);
}

int Shop::get_num_hero()
{
	for (int i = 1; i < 15; i++)
	{
		if (showcase[player_choice].getTexture() == all_heroes[i].getTexture())
		{
			return i;
		}
	}
}
//Delete this method
void Shop::delete_item()
{
	showcase[player_choice].setColor(sf::Color::Transparent);
}