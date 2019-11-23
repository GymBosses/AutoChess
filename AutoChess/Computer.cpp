#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Computer.h"

Computer::Computer(sf::Sprite* stock_heroes, int* field_position)
{
	for (int i = 1; i < 15; i++)
	{
		all_heroes[i] = stock_heroes[i];
	}
	for (int i = 0; i < 3; i++)
	{
		heroes[i].set_position(sf::Vector2f(field_position[i], field_position[3]));
	}
}

void Computer::set_heroes()
{
	int temp_hero;
	int max_level = num_max_level_heroes();
	srand(time(NULL));
	for (int i = 0; i < 3; i++)
	{
		temp_hero = rand() % max_level + 1;
		heroes[i].set_texture(all_heroes[temp_hero]);
	}
}