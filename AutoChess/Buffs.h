#ifndef _BUFFS_
#define _BUFFS_
#include <SFML/Graphics.hpp>
#include "Player.h"

class Buffs
{
public:
	void Buff(Player* pl);
	void BuffHeroes(Player* pl, int plus_at, int plus_hl, int not_buff);
};

#endif