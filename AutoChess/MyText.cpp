#include "MyText.h"

MyText::MyText(const std::string& str)
{
	font.loadFromFile("font/Alata-Regular.ttf");
	text.setFont(font);
	text.setString(str);
	text.setFillColor(sf::Color::White);
}

sf::Text MyText::get_text()
{
	return text;
}

void MyText::change_text(const std::string& str)
{
	text.setString(str);
}

void MyText::set_pos(int x, int y)
{
	text.setPosition(x, y);
}

void MyText::set_scale(float sc)
{
	text.setCharacterSize(80 * (sc / 3000));
}