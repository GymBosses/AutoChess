#ifndef BATTLE
#define BATTLE
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "MySprite.h"
#include "Computer.h"
#include "User.h"
#include "MyText.h"

class Battle
{
	bool end_game = true;
	sf::RenderWindow* window;
	int scrX, scrY;
	User temp_player;
	Computer temp_comp;
public:
	Battle(sf::RenderWindow* win, int X, int Y, User temp_pl, Computer temp_cp);
	int start_battle();
};

#endif