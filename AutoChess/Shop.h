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
	int position[5]; //x1 x2 x3 x4 y
public:
	//input all string of the heroes. sets the location of the characters on the board
	Shop(sf::Sprite* heroes, int* store_position);
	//return true if store full
	bool store_full;
	//set four random heroes in the store, depending on the level of the store
	void set_heroes(int max_level);
	//refresh store
	void refresh();
	//return position hero by player_choice
	sf::Vector2f get_pos();
	//set position hero by player_choice
	void set_pos(int x, int y);
	//returns true if the point lies in the rectangle of sprite and player_choice empty(-1)
	bool check_point(int num, sf::Vector2i pos);
	//move sptite by player_choice
	void move_item(sf::Vector2f pos);
	//return sprite by number
	sf::Sprite get_item(int num = -1);
	//retunr true if the user moves the sprite to the field where the purchased heroes 
	bool check_item_on_field(int scrY);
	//return number by player_choice
	int get_num_hero();
	//set sptite.texture is empty and set position on normal
	void delete_item();
	//set player_choise
	void set_pl_ch(int num);
};

#endif
