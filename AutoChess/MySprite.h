#ifndef SPRITE
#define SPRITE
#include <SFML/Graphics.hpp>

class MySprite
{
	int x, y; //position
public:
	sf::Texture texture;
	sf::Sprite sprite; //sfml sprite
	MySprite();
	sf::Sprite get_sprite();
	//set sptite from file path and set position, if this need
	MySprite(const std::string& path, int scrX = 3000, int scrY = 2000, int px = 0, int py = 0);
	//set position srpite
	void set_pos(int x, int y);
	//full screen display
	void full_screen(int scrx, int scry);
	//set color sprite
	void set_color(int r, int g, int b, int t);
	//create sprite
	void create_sprite(const std::string& path, int scrX = 3000, int scrY = 2000, int px = 0, int py = 0);
};

#endif
