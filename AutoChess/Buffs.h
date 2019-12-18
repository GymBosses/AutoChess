#ifndef _BUFFS_
#define _BUFFS_
#include <SFML/Graphics.hpp>
#include "Player.h"

class Buffs
{
public:
	//Buffs a player's heroes
	void Buff(Player* pl);
	//Hero buffs other heroes, not_buff - number of this hero
	void BuffHeroes(Player* pl, int plus_at, int plus_hl, int not_buff);
};

#endif