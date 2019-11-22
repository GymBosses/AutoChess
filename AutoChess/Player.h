#ifndef _H_
#define _H_
#include "Hero.h"
//using namespace std;

class Player
{
	Hero heroes[3];
	int count_heroes = 0;
	int golds = 300;
	int store_level = 1;
public:
	bool buy_hero(int hero_number);
	void sell_hero(int number);
	int num_max_level_heroes(); //Returns the maximum hero number depending on the player’s level
	bool up_level();
	std::string get_amount_gold();
	bool refresh();
};

#endif