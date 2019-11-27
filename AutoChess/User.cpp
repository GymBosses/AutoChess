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

//void User::attack_player(Computer* pl)
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
