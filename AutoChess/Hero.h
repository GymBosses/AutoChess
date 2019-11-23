#ifndef HERO
#define HERO
#include <SFML/Graphics.hpp>

class Hero
{
	sf::Sprite hero;
	int cost;
	int health;
	int attack_val;
	int number;
	bool taunt;
public:
	int get_cost();
	int get_number();
	void set_texture(sf::Sprite sp, int cost_hero = -1, int number_hero = -1);
	int attack();
	void hero_attacked(int attack_vl);
	void buff_hero(int up_attack, int up_health);
	void set_cost_num(int cost_hero, int num_hero);
	bool hero_died();
	void set_position(sf::Vector2f pos);
	std::string get_attack();
	std::string get_health();
	sf::Sprite get_sprite();
};

#endif
