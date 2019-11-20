#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Player.h"
#include "Shop.h"
#include "Battleground.h"
////Size cards = (292, 400)

const int scrX = 3000;
const int scrY = 2000;
bool battle = false;
sf::Vector2f oldPos;
void set_position(int* store_postion, float plot, int len);
bool move_from_bg;

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
	sf::Texture refresh_texture;
	refresh_texture.loadFromFile("image/refresh.png");
	sf::Sprite refresh;
	refresh.setTexture(refresh_texture);
	refresh.setPosition(int(0.05 * scrX), int(0.80 * scrY));
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
	Shop shop(heroes, store_position);
	Battleground bg_player(heroes, player_field);
	gold.setString("Your gold: " + player.get_amount_gold());
	while (window.isOpen())
	{
		if (!battle && !shop.store_full)
		{
			int max_level = player.num_max_level_heroes();
			shop.set_heroes(max_level);
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
							move_from_bg = false;
							shop.set_pl_ch(i);
							sf::Vector2f t = shop.get_pos();
							dx = pos.x - t.x;
							dy = pos.y - t.y;
							oldPos = t;
							break;
						}
						else if (i != 3 && bg_player.check_point(i, pos))
						{
							isMove = true;
							move_from_bg = true;
							bg_player.set_pl_ch(i);
							sf::Vector2f t = bg_player.get_pos();
							dx = pos.x - t.x;
							dy = pos.y - t.y;
							oldPos = t;
							break;
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
						//Buy hero from shop
						if (!move_from_bg) {
							if (!bg_player.check_full_bg() && shop.check_item_on_field(scrY))
							{
								int hero_number;
								hero_number = shop.get_num_hero();
								if (player.buy_hero(hero_number))
								{
									gold.setString("Your gold: " + player.get_amount_gold());
									shop.delete_item();
									bg_player.set_hero(hero_number);
								}
								else shop.move_item(oldPos);
							}
							else shop.move_item(oldPos);
						}
						//Sell hero from battleground
						else if (move_from_bg && bg_player.check_item_on_field(scrY))
						{
							int k = oldPos.x;
							int index = k / (int(scrX / 4) - 146) - 1;
							bg_player.sell_hero();
							player.sell_hero(index);
							gold.setString("Your gold: " + player.get_amount_gold());
						}
						else
						{
							bg_player.move_item(oldPos);
						}
						shop.set_pl_ch(-1);
						bg_player.set_pl_ch(-1);
						isMove = false;
					}

					if (refresh.getGlobalBounds().contains(pos.x, pos.y))
					{
						if (player.refresh())
						{
							shop.refresh();
							gold.setString("Your gold: " + player.get_amount_gold());
						}
					}
				}
			}
		}

		if (isMove)
		{
			sf::Vector2f to_move(pos.x - dx, pos.y - dy);
			if (move_from_bg)
			{
				bg_player.move_item(to_move);
			}
			else shop.move_item(to_move);
		}
		window.clear();
		window.draw(background_sprite);
		if (!battle) 
		{	
			for (int i = 0; i < 3; i++)
			{
				window.draw(shop.get_item(i));
				window.draw(bg_player.get_item(i));
			}
			window.draw(shop.get_item(3));
			window.draw(refresh);
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
//такой вот код значит