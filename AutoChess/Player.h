#ifndef _H_
#define _H_
#include "Hero.h"
//using namespace std;

class Player
{
public:
	Hero heroes[3];
	int count_heroes = 0;
    int golds = 300;
    int store_level = 1;

	bool buy_hero(int hero_number);
	void sell_hero(int number);
	int num_max_level_heroes(); //Returns the maximum hero number depending on the player’s level
	sf::Sprite get_item(int num);
	std::string get_health(int num);
	std::string get_attack(int num);
};

#endif