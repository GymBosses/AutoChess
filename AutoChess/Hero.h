#ifndef HERO
#define HERO
#include <SFML/Graphics.hpp>

class Hero
{
	sf::Sprite sprite_hero;
	int health;
	int attack_val;
	int number;
public:
	Hero();
	Hero(sf::Sprite hero);
	int attack();
	int hero_attacked(int attack_vl);
	void buff_hero(int up_attack, int up_health);
	bool hero_died();
	std::string get_attack();
	std::string get_health();
};

#endif
