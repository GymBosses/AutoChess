#include <SFML/Graphics.hpp>
#include <string>
#include "MySprite.h"

MySprite::MySprite(std::string path, int x, int y)
{
	sf::Texture texture;
	texture.loadFromFile(path);
	sprite.setTexture(texture);
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

sf::Texture MySprite::get_texture()
{
	return *sprite.getTexture();
}