#ifndef MYTEXT
#define MYTEXT
#include <SFML/Graphics.hpp>


class MyText
{
	sf::Font font;
	sf::Text text;
public:
	//MyText();
	MyText(const std::string& str = "");
	sf::Text get_text();
	void change_text(const std::string& std);
	void set_pos(int x, int y);
	void set_scale(float sc);
};

#endif