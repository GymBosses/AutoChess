#ifndef PUR
#define PUR
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "MySprite.h"
#include "Player.h"
#include "Shop.h"
#include "Battleground.h"
#include "MySprite.h"
#include "MyText.h"
#include "Computer.h"
#include "User.h"
#include "Buffs.h"
#include "Battle.h"
#include "Endgame.h"

class Purchase
{
	bool move_from_bg = false;  //We take a card from the battleground (true) or from the store (false)
	sf::Vector2f oldPos;   //Before moving the sprite, remember its old position

public:
	Purchase(int scrX, int scrY);
	void set_position(int* store_position, float plot, int len, int scrX, int scrY);
};

#endif