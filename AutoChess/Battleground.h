#ifndef BG
#define BG
#include <SFML/Graphics.hpp>
//using namespace sf;
//using namespace std;

class Battleground
{
	sf::Sprite all_heroes[15];
	sf::Sprite heroes[3];
	int position[4]; //x1, x2, x3, y 
	int player_choice;
public:
	Battleground(sf::Sprite* allHeroes, int* player_field);
	void set_hero(int number);
	void sell_hero();
	bool check_full_bg();
	bool check_point(int num, sf::Vector2i pos);
	void set_pl_ch(int num);
	void set_pos(int x, int y);
	void move_item(sf::Vector2f pos);
	sf::Vector2f get_pos();
	sf::Sprite get_item(int num);
	bool check_item_on_field(int scrY);
};

#endif