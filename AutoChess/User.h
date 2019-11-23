#ifndef USER
#define USER
#include <SFML/Graphics.hpp>
#include "Player.h"

class User : public Player
{
public:
	void set_sprite_hero(sf::Sprite sp, sf::Vector2f pos, int num);
	bool refresh();
	std::string get_amount_gold();
	bool up_level();
};

#endif