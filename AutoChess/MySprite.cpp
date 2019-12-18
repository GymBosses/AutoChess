#include <SFML/Graphics.hpp>
#include <string>
#include "MySprite.h"

MySprite::MySprite(const std::string &path, int px, int py)
{
	x = px;
	y = py;
	texture.loadFromFile(path);
	sprite.setTexture(texture);
	sprite.setPosition(px, py);
}

void MySprite::set_pos(int x, int y)
{
	sprite.setPosition(x, y);
}
//set image full screen
void MySprite::full_screen(int scrX, int scrY)
{
	sprite.setScale( //увеличиваем изображение на весь экран
		scrX / sprite.getLocalBounds().width,
		scrY / sprite.getLocalBounds().height);
}

void MySprite::set_color(int r, int g, int b, int t)
{
	sf::Color col = sf::Color(r, g, b, t);
	sprite.setColor(col);
}

sf::Sprite MySprite::get_sprite()
{
	return sprite;
}