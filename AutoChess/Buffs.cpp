#include <SFML/Graphics.hpp>
#include <string>
#include "Player.h"
#include "Buffs.h"

void Buffs::Buff(Player* pl)
{
	for (int i = 0; i < 3; i++)
	{
		pl->heroes[i].max_health = pl->heroes[i].health;
		int number = pl->heroes[i].get_number();
		switch (number)
		{ 
		case 1:
			BuffHeroes(pl, 1, 1, i);
			break;
		case 5:
			BuffHeroes(pl, 0, 2, i);
			break;
		case 7:
			BuffHeroes(pl, 2, 0, i);
			break;
		case 8:
			BuffHeroes(pl, 1, 2, i);
			break;
		}
	}
}

void Buffs::BuffHeroes(Player* pl, int plus_at, int plus_hl, int not_buff)
{
	for (int i = 0; i < 3; i++)
	{
		if (i == not_buff) continue;
		pl->heroes[i].health += plus_hl;
		pl->heroes[i].max_health = pl->heroes[i].health;
		pl->heroes[i].attack_val += plus_at;
	}
}