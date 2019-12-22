#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>
#include "Battleground.h"


Battleground::Battleground(sf::Sprite* allHeroes, int* player_field)
{
	for (int i = 1; i < 15; i++)
	{
		all_heroes[i] = allHeroes[i];
	}
	for (int i = 0; i < 4; i++)
	{
		position[i] = player_field[i];
		if (i <= 2)
		{
			heroes[i].setPosition(position[i], player_field[3]);
		}
	}
	player_choice = -1;
}

void Battleground::set_hero(int number)
{
	for (int i = 0; i < 3; i++)
	{
		if (heroes[i].getTexture() == NULL)
		{
			heroes[i].setTexture(*all_heroes[number].getTexture());
			heroes[i].setScale(all_heroes[number].getScale());
			return;
		}
	}
}

bool Battleground::check_full_bg()
{
	for (int i = 0; i < 3; i++)
	{
		if (heroes[i].getTexture() == NULL)
		{
			return false;
		}
	}
	return true;
}

void Battleground::sell_hero()
{
	sf::Sprite temp;
	temp.setPosition(position[player_choice], position[3]);
	heroes[player_choice] = temp;
}

bool Battleground::check_point(int num, sf::Vector2i pos)
{
	return heroes[num].getGlobalBounds().contains(pos.x, pos.y) && player_choice == -1;
}

void Battleground::set_pl_ch(int num)
{
	player_choice = num;
}

sf::Vector2f Battleground::get_pos()
{
	return heroes[player_choice].getPosition();
}

void Battleground::move_item(sf::Vector2f pos)
{
	heroes[player_choice].setPosition(pos.x, pos.y);
}

void Battleground::set_pos(int x, int y)
{
	heroes[player_choice].setPosition(x, y);
}

sf::Sprite Battleground::get_item(int num)
{
	return heroes[num];
}

bool Battleground::check_item_on_field(int scrY)
{
	return heroes[player_choice].getPosition().y < int(0.30 * scrY);
}
