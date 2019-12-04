#ifndef HERO
#define HERO
#include <SFML/Graphics.hpp>

class Hero
{
	sf::Sprite hero;
	int cost;
	int number = 0;
	bool taunt;
	bool hero_already_attacked = false;
public:
	int health;
	int attack_val;
	int get_cost();
	int get_number();
	void set_texture(sf::Sprite sp, int cost_hero = -1, int number_hero = -1);
	int attack();
	void attack_this_hero(int attack_vl);
	void buff_hero(int up_attack, int up_health);
	void set_cost_num(int cost_hero, int num_hero);
	bool hero_died();
	void set_position(sf::Vector2f pos);

	void refresh_attack();
	bool hero_attacked();
	std::string get_attack();
	std::string get_health();
	sf::Sprite get_sprite();
	void set_red_color();
	void set_green_color();
	void return_color();
};

#endif
