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
	int score = 0;

	void victory();
	std::string get_score();
	void refresh_attack();
	bool buy_hero(int hero_number);
	void sell_hero(int number);
	int have_taunt();
	bool all_died();
	int num_max_level_heroes(); //Returns the maximum hero number depending on the player’s level
	void attack_player(Player* pl);
	//void attack_player(Computer* pl);
	//virtual void attack_player();
	void get_hit(int num, int attack_val);
	sf::Sprite get_item(int num);
	std::string get_health(int num);
	std::string get_attack(int num);
};

#endif