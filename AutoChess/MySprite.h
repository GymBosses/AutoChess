#ifndef SPRITE
#define SPRITE
#include <SFML/Graphics.hpp>

struct MySprite
{
	sf::Sprite mysprite;
	MySprite(std::string path);
	MySprite();
	void set_pos(int x, int y);
};

#endif
