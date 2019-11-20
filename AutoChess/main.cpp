#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <string>
#include "Player.h"
#include "Shop.h"
#include "Battleground.h"
////Size cards = (292, 400)

const int scrX = 3000;
const int scrY = 2000;
bool battle = false;
bool store_full = false;
int num_heroes_on_field = 0;
sf::Vector2f oldPos;
void set_position(int* store_postion, float plot, int len);

int main()
{
	sf::RenderWindow window(sf::VideoMode(scrX, scrY), "Game 0.001");
	sf::Sprite heroes[15];
	sf::Texture herotexture[14];
	//-----------------------------SET_IMAGES
	for (int i = 1; i <= 14; i++)
	{
		std::string full_path = "image/" + std::to_string(i) + ".jpg";
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
	sf::Texture background_texture;
	background_texture.loadFromFile("image/pubg+cats.jpg");
	sf::Sprite background_sprite;
	background_sprite.setTexture(background_texture);
	background_sprite.setScale(
		window.getSize().x / background_sprite.getLocalBounds().width,
		window.getSize().y / background_sprite.getLocalBounds().height);
	background_sprite.setColor(sf::Color(255, 255, 255, 128));
	//------------------------------------------
	//На всякий случай
	bool isMove = false;
	float dx, dy;
	//-----------------------------SET_TEXT_GOLD
	sf::Font font;
	font.loadFromFile("font/Alata-Regular.ttf");
	sf::Text gold;
	gold.setFont(font);
	gold.setFillColor(sf::Color::White);
	gold.setCharacterSize(80);
	gold.setPosition(int(scrX*0.01), int(scrY*0.7));
	//------------------------------------------
	Player player;
	Shop shop(heroes);
	Battleground bg(heroes);
	gold.setString("Your gold: " + player.get_amount_gold());
	while (window.isOpen())
	{
		if (!battle && !shop.store_full)
		{
			int max_level = player.num_max_level_heroes();
			shop.set_heroes(max_level);
			shop.set_pos_all_items(store_position);
		}

		sf::Vector2i pos = sf::Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					for (int i = 0; i < 4; i++)
					{
						if (shop.check_point(i, pos))
						{
							isMove = true;
							shop.set_pl_ch(i);
							dx = pos.x - shop.get_pos().x;
							dy = pos.y - shop.get_pos().y;
							oldPos = shop.get_pos();
						}
					}
				}
			}

			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (event.key.code == sf::Mouse::Left)
				{
					if (isMove)
					{
						if (shop.check_item_on_field(scrX, scrY) &&
							oldPos.y > int(0.70 * scrY) &&
							num_heroes_on_field < 3)
						{
							int hero_number;
							hero_number = shop.get_num_hero();
							if (player.buy_hero(hero_number))
							{
								gold.setString("Your gold: " + player.get_amount_gold());
								float x = player_field[num_heroes_on_field];
								float y = player_field[3];
								shop.move_item(sf::Vector2f(x, y));
								num_heroes_on_field++;
							}
							else shop.move_item(oldPos);
						}
						else if (shop.get_pos().y < int(0.30 * scrY) &&
							oldPos.y < int(0.70 * scrY) && oldPos.y > int(0.30 * scrY))
						{
							int k = oldPos.x;
							int index = k / (int(scrX / 4) - 146) - 1;
							player.sell_hero(index);
							shop.delete_item();
							num_heroes_on_field--;
							gold.setString("Your gold: " + player.get_amount_gold());
						}
						else shop.move_item(oldPos);
						shop.set_pl_ch(-1);
						isMove = false;
					}
				}
			}
		}

		if (isMove) shop.move_item(sf::Vector2f(pos.x - dx, pos.y - dy));
		//Sprite kok;
		window.clear();
		window.draw(background_sprite);
		//	window.draw(kok);
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