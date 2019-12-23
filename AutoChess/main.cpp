#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "MySprite.h"
#include "Player.h"
#include "Shop.h"
#include "Battleground.h"
#include "MySprite.h"
#include "MyText.h"
#include "Computer.h"
#include "User.h"
#include "Buffs.h"
////Size cards = (292, 400)

const int scrX = sf::VideoMode::getDesktopMode().width; //Screen sizes (changes to fit your screen, you need to test)
const int scrY = sf::VideoMode::getDesktopMode().height;
bool battle = false;   //Responsible for the game mode : fight(true) or purchase of characters
sf::Vector2f oldPos;   //Before moving the sprite, remember its old position

//sets the points (x1, x2 ... xn, y) where the sprites (x1, y) (x2, y) of the store and the player�s field are located
void set_position(int* store_postion, float plot, int len);
bool move_from_bg;     //We take a card from the battleground (true) or from the store (false)

int main()
{
	sf::RenderWindow window(sf::VideoMode(scrX, scrY), "Game 0.001");//Render Window, where is the game
	sf::Texture herotexture[15];
	sf::Sprite heroes[15];
	//-----------------------------
	for (int i = 1; i <= 14; i++)
	{
		std::string full_path = "image/" + std::to_string(i) + ".jpg"; //file path jpg
		herotexture[i - 1].loadFromFile(full_path);					   //load texture from file
		heroes[i].setTexture(herotexture[i - 1]);					   //set texture
		heroes[i].setScale(scrX / 3000.0, scrY / 2000.0);
	}
	//----------------------------------------
	//------------------------------SET_STORE_POSITION AND PLAYER_FIELD
	int store_position[5];                 //points (x1, x2, x3, y) where the cards will be located in the store
	set_position(store_position, 0.75, 5);
	int player_field[4];				   //similarly on the field
	set_position(player_field, 0.50, 4);
	int comp_field[4];
	set_position(comp_field, 0.10, 4);
	//------------------------------ SET BATTLEGROUND AND OTHER IMAGE
	MySprite background("image/pubg+cats.jpg", scrX, scrY); //image background
	background.full_screen(window.getSize().x, window.getSize().y);
	background.set_color(255, 255, 255, 128);
	//-------------------------------------------------------------------------
	MySprite refresh("image/refresh.png", scrX, scrY, int(0.03 * scrX), int(0.78 * scrY)); //refresh image
	MySprite levelup("image/levelup.png", scrX, scrY, int(0.85 * scrX), int(0.1 * scrY));
	MySprite start_game("image/startgame.png", scrX, scrY, int(0.45 * scrX), int(0.11 * scrY));
	MySprite died("image/died.jpg", scrX, scrY);
	//-----------------------------------------------------------------------WONLOSE
	MySprite won[3]; //Massive for created win/lose windows
	MySprite lost[3];
	for (int i = 0; i < 3; i++)
	{
		won[i].create_sprite("image/win" + std::to_string(i) + ".jpg", scrX, scrY, (scrX) / 2 - 200, (scrY / 2 - 50));
	}
	for (int i = 0; i < 3; i++)
	{
		lost[i].create_sprite("image/lose" + std::to_string(i) + ".jpg", scrX, scrY, (scrX) / 2 - 200, (scrY / 2 - 50));
	}
	//--------------------------------------------------------------------------
	bool isMove = false;
	float dx, dy;
	User player;	//Player
	User temp_player;
	Computer comp(heroes, comp_field);  //Computer
	Computer temp_comp = comp;
	Shop shop(heroes, store_position); //store
	Buffs bf;
	Battleground bg_player(heroes, player_field); //battlefield
	//-----------------------------The text with the amount of resources the player has	

	MyText gold("Your gold: " + player.get_amount_gold());
	//POWER///////////////////////////////////////////////////////////////////
	MyText play("PLAY");
	play.set_scale(scrX);
	play.set_pos(int(scrX * 0.45), int(scrY * 0.01));
	MyText shop_lvl("Your shop level: " + std::to_string(player.store_level));
	shop_lvl.set_scale(scrX);
	shop_lvl.set_pos(int(scrX * 0.75), int(scrY * 0.01));
	MyText shop_cost("Store upgrade cost- " + player.upgrade_cost());
	shop_cost.set_scale(scrX);
	shop_cost.set_pos(int(scrX * 0.7), int(scrY * 0.23));
	MyText total_score("Total score: " + std::to_string(player.score) + ":" + std::to_string(comp.score));
	total_score.set_scale(scrX);
	total_score.set_pos(int(scrX * 0.01), int(scrY * 0.01));
	//-----------------------------------------------------------------------
	gold.set_scale(scrX);
	gold.set_pos(int(scrX * 0.01), int(scrY * 0.7));
	MyText characteristic[12];
	for (int i = 0; i < 12; i++)
	{
		characteristic[i].set_scale(scrX);
	}
	sf::Clock clock;
	sf::Clock turn_clock;
	bool turn = true;
	float time = 0.0;
	float time_turn = 0.0;
	comp.set_heroes();
	while (window.isOpen())
	{
		time = clock.getElapsedTime().asSeconds();
		time_turn = turn_clock.getElapsedTime().asSeconds();

		if (!battle && !shop.store_full)	//if store is empty
		{
			int max_level = player.num_max_level_heroes(); //store level
			shop.set_heroes(max_level);
		}

		sf::Vector2i pos = sf::Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) //close the window when you click on "Close" (or not, I don�t know)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && !battle)
			{
				if (event.key.code == sf::Mouse::Left) //obviously 
				{
					for (int i = 0; i < 4; i++)
					{
						if (shop.check_point(i, pos))		//clicked on someone from the store
						{
							isMove = true;
							move_from_bg = false;
							shop.set_pl_ch(i);				//the number of the hero from the mazagin that the player chose
							sf::Vector2f t = shop.get_pos();
							dx = pos.x - t.x;
							dy = pos.y - t.y;
							oldPos = t;
							break;//����
						}
						else if (i != 3 && bg_player.check_point(i, pos)) //clicked on someone from the battlefield
						{
							isMove = true;
							move_from_bg = true;		//similarly higher
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

			if (event.type == sf::Event::MouseButtonReleased && !battle) //releasing the mouse button
			{
				if (event.key.code == sf::Mouse::Left)// not right
				{
					if (isMove) //we move something
					{
						if (!move_from_bg) { //from store
							if (!bg_player.check_full_bg() && shop.check_item_on_field(scrY))
							{//is there a place on the field and in the right place have we moved (0.3 * scrY <y <0.7 * scrY)
								int hero_number;
								hero_number = shop.get_num_hero();
								if (player.buy_hero(hero_number)) //can we buy, if yes - buy (need to be divided into 2 methods)
								{
									gold.change_text("Your gold: " + player.get_amount_gold());
									shop.delete_item();				//delete from the store
									bg_player.set_hero(hero_number);//add to the playing field
								}
								else shop.move_item(oldPos);//if there is no gold - return the sprite
							}
							else shop.move_item(oldPos);
						}
						//Sell heroes from battleground
						else if (move_from_bg && bg_player.check_item_on_field(scrY))
						{
							int k = oldPos.x;
							int index = k / (int(scrX / 4) - 146) - 1; //what is the score (from left to right) sprite (idk)
							bg_player.sell_hero();
							player.sell_hero(index);	//sell by serial number
							gold.change_text("Your gold: " + player.get_amount_gold());
						}
						else
						{
							bg_player.move_item(oldPos); //return back
						}
						shop.set_pl_ch(-1); //set player choice -1 (none, empty)
						bg_player.set_pl_ch(-1);
						isMove = false;
					}

					if (refresh.sprite.getGlobalBounds().contains(pos.x, pos.y))//store update, delivery of new heroes
					{
						if (player.refresh()) //is there enough money (need to be divided into 2 methods), if so, then -1 gold
						{
							shop.refresh();
							gold.change_text("Your gold: " + player.get_amount_gold());
						}
					}

					if (levelup.sprite.getGlobalBounds().contains(pos.x, pos.y)) //up level
					{
						if (player.up_level())
						{
							shop.set_heroes(player.num_max_level_heroes());
							gold.change_text("Your gold: " + player.get_amount_gold());
							shop_lvl.change_text("Your shop level- " + std::to_string(player.store_level));
							shop_cost.change_text("Store upgrade cost- " + player.upgrade_cost());

						}
						comp.up_level();
					}

					if (start_game.sprite.getGlobalBounds().contains(pos.x, pos.y))
					{
						battle = true;
						isMove = false;
						for (int i = 0; i < 3; i++)
						{
							if (bg_player.get_item(i).getTexture() == NULL) continue;
							player.set_sprite_hero(bg_player.get_item(i), bg_player.get_item(i).getPosition(), i);
						}
						temp_comp = comp;
						temp_player = player;
						bf.Buff(&temp_comp);
						bf.Buff(&temp_player);
						clock.restart();
						turn_clock.restart();
						time = 0;
						time_turn = 0;
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
		window.draw(background.get_sprite());
		if (!battle)
		{	//drawing of all sprites, some empty, errors are possible (but they are not)
			for (int i = 0; i < 3; i++)
			{
				window.draw(shop.get_item(i));
				window.draw(bg_player.get_item(i));
			}
			window.draw(shop.get_item(3));
			window.draw(refresh.sprite);
			window.draw(levelup.sprite);
			window.draw(start_game.sprite);
			window.draw(gold.get_text());
			//-------------------------------POWER
			window.draw(shop_lvl.get_text());
			window.draw(shop_cost.get_text());
			window.draw(total_score.get_text());
			window.draw(play.get_text());
			//---------------------------------
		}
		if (battle)
		{
			bool check_comp = temp_comp.all_died();
			bool check_player = temp_player.all_died();
			for (int i = 0; i < 3; i++)
			{
				if (temp_player.heroes[i].hero_died())
				{
					temp_player.heroes[i].set_texture(died.sprite);
					window.draw(temp_player.get_item(i));
				}
				else window.draw(temp_player.get_item(i));
				if (temp_comp.heroes[i].hero_died())
				{
					temp_comp.heroes[i].set_texture(died.sprite);
					window.draw(temp_comp.get_item(i));
				}
				else window.draw(temp_comp.get_item(i));
			}
			for (int i = 0; i < 12; i++)
			{
				int num;
				Player temp;
				if (i < 6)
				{
					num = i / 2;
					temp = temp_player;
				}
				else
				{
					num = (i - 6) / 2;
					temp = temp_comp;
				}
				sf::Vector2f pos_hero = temp.get_item(num).getPosition();
				if (i % 2 == 1)
				{
					characteristic[i].change_text(temp.get_health(num));
					characteristic[i].set_pos(pos_hero.x + 210 * (scrX/3000.0), pos_hero.y - 100*(scrX/3000.0));
				}
				else
				{
					characteristic[i].change_text(temp.get_attack(num));
					characteristic[i].set_pos(pos_hero.x, pos_hero.y - 100 * (scrX/3000.0));	
				}
				window.draw(characteristic[i].get_text());
			}
			if (time >= 1.5 && !(check_comp || check_player))
			{
				if (turn)
				{
					std::cout << "PLAYER" << std::endl;
					temp_player.attack_player(&temp_comp);
					turn = false;
				}
				else
				{
					std::cout << "COMPUTER" << std::endl;
					temp_comp.attack_player(&temp_player);
					turn = true;
				}
				clock.restart();
			}
			if (comp.score == 10 || player.score == 10)
			{
				int rnd = rand() % 3;
				if (check_comp)
				{
					window.draw(won[rnd].sprite);
				}
				if (check_player)
				{
					window.draw(lost[rnd].sprite);
				}
				while (time <= 2)
				{
					time = clock.getElapsedTime().asSeconds();
				}
				window.close();
			}

			if ((check_comp || check_player) || time_turn >= 60.0)
			{
				battle = false;
				int rnd = rand() % 3;
				if (time_turn >= 60.0)
				{
					player.victory();
					comp.victory();
				}
				if (check_comp)
				{
					window.draw(won[rnd].sprite);
					player.victory();
					comp.set_heroes();
				}
				if (check_player)
				{
					window.draw(lost[rnd].sprite);
					comp.victory();
				}
				player.end_battle();
				gold.change_text("Your gold: " + player.get_amount_gold());
				shop.refresh();
				time = 0;
				time_turn = 0;
				clock.restart(); window.display();
				while (time <= 2)
				{
					time = clock.getElapsedTime().asSeconds();
				}
			}
		}

		window.display();

	}
	return 0;
}

//sets the coordinates on the screen depending on the resolution and the number of points
void set_position(int* store_position, float plot, int len)
{
	len = len - 1;
	for (int i = 0; i < len; i++)
	{
		store_position[i] = (i + 1) * int(scrX / (len + 1)) - 146 * (scrX / 3000.0);//coordinate x
	}
	store_position[len] = int(scrY * plot); //'y' coordinates, everyone has one 
}