#include <SFML/Graphics.hpp>
#include "Player.h"
#include <iostream>
#include <string>
#include "User.h"
#include "Computer.h"

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
			if (heroes[i].get_number() == 0)
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

std::string Player::get_health(int num)
{
	return heroes[num].get_health();
}

std::string Player::get_attack(int num)
{
	return heroes[num].get_attack();
}

int Player::have_taunt()
{
	for (int i = 0; i < 3; i++)
	{
		if (heroes[i].get_number() == 11 || heroes[i].get_number() == 12)
		{
			return i;
		}
	}
	return -1;
}

void Player::get_hit(int num, int attack_val)
{
	heroes[num].attack_this_hero(attack_val);
	heroes[num].hero_died();  //изменить hero_dies() 
}

void Player::refresh_attack()
{
	for (int i = 0; i < 3; i++)
	{
		heroes[i].refresh_attack();
	}
}
//Надо думать, как сократить----------------------------------------------------------------
void Player::attack_player(Player* pl)
{
	Hero* p = &heroes[0];
	int a = 0;
	bool all_attacked = true;
	for (int i = 0; i < 3; i++)
	{
		if (heroes[i].hero_died())
		{
			continue;
		}
		if (!heroes[i].hero_attacked())
		{
			a = i;
			p = &heroes[i];
			all_attacked = false;
			break;
		}
	}
	if (all_attacked)
	{
		refresh_attack();
		for (int i = 0; i < 3; i++)
		{
			if (!heroes[i].hero_died())
			{
				p = &heroes[i];
				a = i;
				break;
			}
		}
	}
	int target;
	srand(time(NULL));
	target = pl->have_taunt();
	while (target == -1)
	{
		target = rand() % 3;
		if (pl->heroes[target].health <= 0)
		{
			target = -1;
		}
	}
	std::cout << "Attakyet hero pod nomerom: " << a << std::endl;
	std::cout << "Hero, kotorogo ataky10t: " << target << std::endl;
	pl->get_hit(target, p->attack());
}

bool Player::all_died()
{
	for (int i = 0; i < 3; i++)
	{
		if (!heroes[i].hero_died())
		{
			return false;
		}
	}
	return true;
}

