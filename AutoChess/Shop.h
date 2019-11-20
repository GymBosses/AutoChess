#ifndef SHOP
#define SHOP
#include <SFML/Graphics.hpp>
//using namespace sf;
//using namespace std;

class Shop
{
	sf::Sprite all_heroes[15];
	int max_level;
	sf::Sprite showcase[4];
	int player_choice;
public:
	Shop(sf::Sprite* heroes);
	bool store_full;
	void set_heroes(int max_level);
	void refresh();
	void set_pos_all_items(int* store_position);
	sf::Vector2f get_pos();
	void set_pos(int x, int y);
	bool check_point(int num, sf::Vector2i pos);
	void move_item(sf::Vector2f pos);
	sf::Sprite get_item(int num);
	bool check_item_on_field(int scrX, int scrY);
	int get_num_hero();
	void delete_item();
	void set_pl_ch(int num);
};

#endif
