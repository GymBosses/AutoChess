#ifndef COMP
#define COMP
#include <SFML/Graphics.hpp>
#include "Player.h"

class Computer : public Player
{
	sf::Sprite all_heroes[15];
public:
	Computer(sf::Sprite* stock_heroes, int* field_position);
	void set_heroes();
	void change_deck();
	void up_level();
	void attacked(int attack);
};

#endif