#ifndef SHOP
#define SHOP
#include <SFML/Graphics.hpp>
using namespace sf;
using namespace std;

class Shop
{
	Sprite all_heroes[15];
	int max_level;
	Sprite showcase[4];
public:
	Shop(Sprite* heroes);
	int player_choice;
	bool store_full = false;
	void set_heroes(int max_level);
	void refresh();
	void set_pos_all_items(int* store_position);
	Vector2f get_pos(int num);
	void set_pos(int num, int x, int y);
	bool check_point(int num, Vector2i pos);
	void move_item(int num, Vector2f pos);
	Sprite get_item(int num);
	bool check_item_on_field(int num, int scrX, int scrY);
	int get_num_hero(int num);
	void delete_item(int num);
};

#endif
