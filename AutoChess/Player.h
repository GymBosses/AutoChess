#ifndef _H_
#define _H_
#include "Hero.h"
//using namespace std;

class Player
{
public:
	Hero heroes[3];
	int count_heroes = 0;
	int golds = 3;
	int store_level = 1;
	int score = 0;
	//increases the score by one
	void victory();
	//increases gold by three
	void end_battle();
	//return score
	std::string get_score();
	//set hero_already_attacked of heroes on thue 
	void refresh_attack();
	//buy hero by number of hero
	bool buy_hero(int hero_number);
	//sell the hero by his serial number
	void sell_hero(int number);
	//return number of hero, who has a taunt
	int have_taunt();
	//return true, if all heroes died
	bool all_died();
	//Returns the maximum hero number depending on the player’s level
	int num_max_level_heroes();
	//attack other player
	void attack_player(Player* pl);
	//reduce the hero's health by attack_val, num - number hero on the list 
	void get_hit(int num, int attack_val);
	//return sprite
	sf::Sprite get_item(int num);
	//return health by string
	std::string get_health(int num);
	//return attack by string
	std::string get_attack(int num);
};

#endif