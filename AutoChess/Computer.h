#ifndef COMP
#define COMP
#include <SFML/Graphics.hpp>
#include "Player.h"

class Computer : public Player
{
	sf::Sprite all_heroes[15];
public:
	Computer() {};
	Computer(sf::Sprite* stock_heroes, int* field_position);
	//Randomly sets heroes
	void set_heroes();
	//Not used
	void change_deck();
	//Improves store level. If the user improves the store, then the computer too (you can improve this moment)
	void up_level();
	//Idk
	void attacked(int attack);
	//void attack_player(User* pl);
};

#endif