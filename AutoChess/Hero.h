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
	/*You can make these parameters private in order to
	preserve the principle of encapsulation, but for now they will be public*/
	int max_health;
	int health;
	int attack_val;

	int get_cost();
	int get_number();
	void set_texture(sf::Sprite sp, int cost_hero = -1, int number_hero = -1);
	int attack(); //Not needed yet(but used somewhere)
	//Decreases health by attack_vl
	void attack_this_hero(int attack_vl);
	//Increases hero health and attack
	void buff_hero(int up_attack, int up_health);
	void set_cost_num(int cost_hero, int num_hero);
	//If hero died - return true
	bool hero_died();
	void set_position(sf::Vector2f pos);
	//Set hero_already_attacked = false
	void refresh_attack();
	//return hero_already_attacked
	bool hero_attacked();
	//return attack by string
	std::string get_attack();
	//return health by string
	std::string get_health();
	//return sprite of the hero
	sf::Sprite get_sprite();
	//set sprite color to red
	void set_red_color();
	//set sprite color to red
	void set_green_color();
	//set stpite color to normal
	void return_color();
};

#endif
