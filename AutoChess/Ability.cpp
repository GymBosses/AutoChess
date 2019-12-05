#include "Ability.h"

void Ability::SpellAbility(Hero* attacked_pl, Hero* attacking_pl, int num_attacked, int num_attacking)
{
	int number = attacking_pl[num_attacking].get_number();
	switch (number)
	{
	case 2:
		doubleAttack(attacked_pl, attacking_pl[num_attacking].attack_val, num_attacked);
		break;
	case 3:
		AttackAllHeroes(attacked_pl, 1);
		break;
	case 4:
		HealAllFriend(attacking_pl, 3);
		break;
	case 7:
		DeBuffs(attacked_pl);
		break;
	case 10:
		AttackAllHeroes(attacked_pl, 2);
	default:
		break;
	}
}

void Ability::doubleAttack(Hero* attacked_pl, int attack_vl, int num_attacked)
{
	if (!attacked_pl[num_attacked].hero_died()) attacked_pl[num_attacked].attack_this_hero(attack_vl);
}

void Ability::AttackAllHeroes(Hero* attacked_pl, int attack_vl)
{
	for (int i = 0; i < 3; i++)
	{
		if (!attacked_pl[i].hero_died())
		{
			attacked_pl[i].attack_this_hero(attack_vl);
		}
	}
}

void Ability::HealAllFriend(Hero* attacking_pl, int health_vl)
{
	for (int i = 0; i < 3; i++)
	{
		if (!attacking_pl[i].hero_died())
		{
			int restore = attacking_pl[i].max_health - attacking_pl[i].health;
			if (restore > health_vl) restore = health_vl;
			attacking_pl[i].health += restore;
		}
	}
}

void Ability::DeBuffs(Hero* attacked_pl)
{
	for (int i = 0; i < 3; i++)
	{
		if (!attacked_pl[i].hero_died())
		{
			attacked_pl[i].attack_val -= 1;
			attacked_pl[i].health -= 1;
		}
	}
}
//void HealAllFriend(Player* attacking_pl, int health_vl);
//void DeBuffs(Player* attacked_pl);