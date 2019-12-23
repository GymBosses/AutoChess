#ifndef USER
#define USER
#include <SFML/Graphics.hpp>
#include "Player.h"

class User : public Player
{
public:
	void set_sprite_hero(sf::Sprite sp, sf::Vector2f pos, int num);
	//refresh store
	bool refresh();
	//return value of the gold by string
	std::string get_amount_gold();
	//up store level
	bool up_level();
	//void attack_player(Computer* pl);
	//return cost that need for up store
	std::string upgrade_cost();
};

#endif