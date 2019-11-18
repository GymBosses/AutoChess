#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <string>
#include "Player.h"
#include "Shop.h"
//Size cards = (292, 400)
using namespace sf;
using namespace std;

const int scrX = 3000;
const int scrY = 2000;
bool battle = false;
bool store_full = false;
int player_choice = -1;
int num_heroes_on_field = 0;
Vector2f oldPos;
void set_position(int* store_postion, float plot, int len);

int main()
{
	RenderWindow window(VideoMode(scrX, scrY), "Game 0.001");
	Sprite heroes[15];
	Texture herotexture[14];
	//-----------------------------SET_IMAGES
	for (int i = 1; i <= 14; i++)
	{
		string full_path = "image/" + to_string(i) + ".jpg";
		herotexture[i - 1].loadFromFile(full_path);
		heroes[i].setTexture(herotexture[i - 1]);
	}
	//----------------------------------------
	//------------------------------SET_STORE_POSITION AND PLAYER_FIELD
	int store_position[5];
	set_position(store_position, 0.75, 5);
	int player_field[4];
	set_position(player_field, 0.50, 4);
	//------------------------------SET_BATTLEGROUND_IMAGE
	Texture background_texture;
	background_texture.loadFromFile("image/pubg+cats.jpg");
	Sprite background_sprite;
	background_sprite.setTexture(background_texture);
	background_sprite.setScale(
		window.getSize().x / background_sprite.getLocalBounds().width,
		window.getSize().y / background_sprite.getLocalBounds().height);
	background_sprite.setColor(Color(255, 255, 255, 128));
	//------------------------------------------
	//На всякий случай
	bool isMove = false;
	float dx, dy;
	//-----------------------------SET_TEXT_GOLD
	Font font;
	font.loadFromFile("font/Alata-Regular.ttf");
	Text gold;
	gold.setFont(font);
	gold.setFillColor(Color::White);
	gold.setCharacterSize(80);
	gold.setPosition(int(scrX*0.01), int(scrY*0.7));
	//------------------------------------------
	Player player;
	Shop shop(heroes);
	gold.setString("Your gold: " + player.get_amount_gold());
	while (window.isOpen())
	{
		if (!battle && !shop.store_full)
		{
			int max_level = player.num_max_level_heroes();
			shop.set_heroes(max_level);
			shop.set_pos_all_items(store_position);
		}

		Vector2i pos = Mouse::getPosition(window);

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonPressed)
			{
				if (event.key.code == Mouse::Left)
				{
					for (int i = 0; i < 4; i++)
					{
						if (shop.check_point(i, pos))
						{
							isMove = true;
							dx = pos.x - shop.get_pos(i).x;
							dy = pos.y - shop.get_pos(i).y;
							if (player_choice == -1) oldPos = shop.get_pos(i);
							player_choice = i;
						}
					}
				}
			}

			if (event.type == Event::MouseButtonReleased)
			{
				if (event.key.code == Mouse::Left)
				{
					if (isMove)
					{
						if (shop.check_item_on_field(player_choice, scrX, scrY) &&
							oldPos.y > int(0.70 * scrY) &&
							num_heroes_on_field < 3)
						{
							int hero_number;
							hero_number = shop.get_num_hero(player_choice);
							if (player.buy_hero(hero_number))
							{
								gold.setString("Your gold: " + player.get_amount_gold());
								float x = player_field[num_heroes_on_field];
								float y = player_field[3];
								shop.move_item(player_choice, Vector2f(x, y));
								num_heroes_on_field++;
							}
							else shop.move_item(player_choice, oldPos);
						}
						else if (shop.get_pos(player_choice).y < int(0.30 * scrY) &&
							oldPos.y < int(0.70 * scrY) && oldPos.y > int(0.30 * scrY))
						{
							int k = oldPos.x;
							int index = k / (int(scrX / 4) - 146) - 1;
							player.sell_hero(index);
							shop.delete_item(player_choice);
							num_heroes_on_field--;
							gold.setString("Your gold: " + player.get_amount_gold());
						}
						else shop.move_item(player_choice, oldPos);
						player_choice = -1;
						isMove = false;
					}
				}
			}
		}

		if (isMove) shop.move_item(player_choice, Vector2f(pos.x - dx, pos.y - dy));

		window.clear();
		window.draw(background_sprite);
		if (!battle) 
		{	
			for (int i = 0; i < 4; i++)
			{
				window.draw(shop.get_item(i));
			}
		}
		window.draw(gold);
		window.display();
	}

	return 0;
}

void set_position(int* store_position, float plot, int len)
{
	len = len - 1;
	for (int i = 0; i < len; i++)
	{
		store_position[i] = (i + 1) * int(scrX / (len + 1)) - 146;
	}
	store_position[len] = int(scrY * plot);
}