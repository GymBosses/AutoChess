#ifndef _H_
#define _H_

class Player
{
	int heroes[3];
	int buffs;
	int count_heroes = 0;
	int golds;
	int store_level = 1;
public:
	bool buy_hero(int hero_number);
	void sell_hero(int number);
	int num_max_level_heroes(); //Returns the maximum hero number depending on the player’s level
};

#endif