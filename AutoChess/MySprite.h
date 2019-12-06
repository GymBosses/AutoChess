#ifndef SPRITE
#define SPRITE
#include <SFML/Graphics.hpp>

class MySprite
{
	int x, y; //position
public:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Sprite get_sprite();
	MySprite(const std::string &path, int px = 0, int py = 0);
	void set_pos(int x, int y);
	void full_screen(int scrx, int scry);
	sf::Texture get_texture();
	void set_color(int r, int g, int b, int t);
};

#endif
