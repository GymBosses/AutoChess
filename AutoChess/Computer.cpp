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
		heroes[i].set_cost_num(store_level, temp_hero);
	}
}

void Computer::up_level()
{
	store_level += 1;
	set_heroes();
}
//void Computer::attack_player(User* pl)
//{
//	Hero* p = &heroes[0];
//	bool all_attacked = true;
//	for (int i = 0; i < 3; i++)
//	{
//		if (!heroes[i].hero_attacked())
//		{
//			p = &heroes[i];
//			all_attacked = false;
//			break;
//		}
//	}
//	if (all_attacked)
//	{
//		refresh_attack();
//	}
//	int target;
//	srand(time(NULL));
//	target = pl->have_taunt();
//	if (target == -1) target = rand() % 3;
//	pl->get_hit(target, p->attack());
//}