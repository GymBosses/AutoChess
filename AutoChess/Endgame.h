#ifndef END
#define END
#include <SFML/Graphics.hpp>
#include "Computer.h"
#include "User.h"
#include "MySprite.h"
#include "MyText.h"

class Endgame
{
	bool player_win;
public:
	Endgame() {};
	bool check_end(User* user, Computer* comp);
	void end_game(sf::RenderWindow* window, MySprite* background, Computer comp, User player);
};

#endif