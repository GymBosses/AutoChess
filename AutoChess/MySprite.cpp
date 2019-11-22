#include <SFML/Graphics.hpp>
#include <string>
#include "MySprite.h"

MySprite::MySprite(std::string path)
{
	sf::Texture texture;
	texture.loadFromFile(path);
	mysprite.setTexture(texture);
}

void MySprite::set_pos(int x, int y)
{
	mysprite.setPosition(x, y);
}