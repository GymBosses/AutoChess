#ifndef BG
#define BG
#include <SFML/Graphics.hpp>

class Battleground
{
	//Pictures of all the characters in the game
	sf::Sprite all_heroes[15];
	//Heroes Purchased
	sf::Sprite heroes[3];
	//The position of the heroes on the field
	int position[4]; //x1, x2, x3, y 
	//The number of the hero that the player chose
	int player_choice;
public:
	Battleground(sf::Sprite* allHeroes, int* player_field);
	//Put the hero on the field, put on a free space from left to right
	void set_hero(int number);
	//Deletes the hero the player has selected.
	void sell_hero();
	//Returns false if the field is not completely filled
	bool check_full_bg();
	//Does this point (Vector2i) fall on the hero’s card number
	bool check_point(int num, sf::Vector2i pos);
	//Set player_choice 
	void set_pl_ch(int num);
	//Set the position of the hero the player has chosen
	void set_pos(int x, int y);
	//Move sprite to specified position(Vector2f)
	void move_item(sf::Vector2f pos);
	//Get the position of the hero chosen by the player
	sf::Vector2f get_pos();
	//Get the sprite of the hero chosen by the player
	sf::Sprite get_item(int num);
	//Returns true if the sprite of the hero selected by the player is in the heroes sale field
	bool check_item_on_field(int scrY);
};

#endif