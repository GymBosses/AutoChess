#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include <string>
#include "Player.h"
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
	Sprite showcase[4];
	gold.setString("Your gold: " + player.get_amount_gold());
	while (window.isOpen())
	{
		if (!battle & !store_full)
		{
			int max_level = player.num_max_level_heroes();
			int temp_hero;
			srand(time(NULL));
			for (int i = 0; i < 4; i++)
			{
				temp_hero = rand() % max_level + 1;
				showcase[i] = heroes[temp_hero];
				showcase[i].setPosition(store_position[i], store_position[4]);
			}
			store_full = true;
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
						if (showcase[i].getGlobalBounds().contains(pos.x, pos.y))
						{
							isMove = true;
							dx = pos.x - showcase[i].getPosition().x;
							dy = pos.y - showcase[i].getPosition().y;
							if (player_choice == -1) oldPos = showcase[i].getPosition();
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
						if (showcase[player_choice].getPosition().y < int(0.70 * scrY) &&
							showcase[player_choice].getPosition().y > int(0.30 * scrY) &&
							oldPos.y > int(0.70 * scrY) &&
							num_heroes_on_field < 3)
						{
							int hero_number;
							for (int i = 1; i < 15; i++)
							{
								if (showcase[player_choice].getTexture() == heroes[i].getTexture())
								{
									hero_number = i;
									break;
								}
							}
							if (player.buy_hero(hero_number))
							{
								gold.setString("Your gold: " + player.get_amount_gold());
								float x = player_field[num_heroes_on_field];
								float y = player_field[3];
								showcase[player_choice].setPosition(x, y);
								num_heroes_on_field++;
							}
							else showcase[player_choice].setPosition(oldPos);
						}
						else if (showcase[player_choice].getPosition().y < int(0.30 * scrY) &&
							oldPos.y < int(0.70 * scrY) && oldPos.y > int(0.30 * scrY))
						{
							int k = oldPos.x;
							int index = k / (int(scrX / 4) - 146) - 1;
							player.sell_hero(index);
							gold.setString("Your gold: " + player.get_amount_gold());
						}
						else
						{
							showcase[player_choice].setPosition(oldPos);
						}
						player_choice = -1;
						isMove = false;
					}
				}
			}
		}

		if (isMove) showcase[player_choice].setPosition(pos.x - dx, pos.y - dy);

		window.clear();
		window.draw(background_sprite);
		if (!battle) 
		{	
			for (int i = 0; i < 4; i++)
			{
				window.draw(showcase[i]);
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