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
	Player player;
	Sprite showcase[4];
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

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

		if (!battle && Mouse::isButtonPressed(Mouse::Left))
		{
			Mouse ms;
			float x = ms.getPosition(window).x;
			float y = ms.getPosition(window).y;
			if (player_choice == -1) {
				for (int i = 0; i < 4; i++)
				{
					if (x <= showcase[i].getPosition().x + 292.0f &&
						x >= showcase[i].getPosition().x &&
						y <= showcase[i].getPosition().y + 400.0f &&
						y >= showcase[i].getPosition().y)
					{
						showcase[i].setPosition(x - 146, y - 200);
						player_choice = i;
					}
				}
			}
			else
			{
				showcase[player_choice].setPosition(x - 146, y - 200);
			}
		}
		else if (player_choice >= 0)
		{
			if (showcase[player_choice].getPosition().y < int(0.75 * scrY) &&
				showcase[player_choice].getPosition().y > int(0.25 * scrY) &&
				num_heroes_on_field < 3)
			{
				float x = player_field[num_heroes_on_field];
				float y = player_field[3];
				showcase[player_choice].setPosition(x, y);
				num_heroes_on_field++;
			} 
			player_choice = -1;
		}

		window.clear();
		window.draw(background_sprite);
		if (!battle) 
		{	
			for (int i = 0; i < 4; i++)
			{
				window.draw(showcase[i]);
			}
		}
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