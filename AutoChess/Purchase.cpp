#include "Purchase.h"

Purchase::Purchase(int scrX, int scrY)
{
	sf::RenderWindow window(sf::VideoMode(scrX, scrY), "AutoChess");//Render Window, where is the game
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
	set_position(store_position, 0.75, 5, scrX, scrY);
	int player_field[4];				   //similarly on the field
	set_position(player_field, 0.50, 4, scrX, scrY);
	int comp_field[4];
	set_position(comp_field, 0.10, 4, scrX, scrY);
	//------------------------------ SET BATTLEGROUND AND OTHER IMAGE
	MySprite background("image/pubg+cats.jpg", scrX, scrY); //image background
	background.full_screen(window.getSize().x, window.getSize().y);
	background.set_color(255, 255, 255, 128);
	//-------------------------------------------------------------------------
	MySprite refresh("image/refresh.png", scrX, scrY, int(0.03 * scrX), int(0.78 * scrY)); //refresh image
	MySprite levelup("image/levelup.png", scrX, scrY, int(0.85 * scrX), int(0.1 * scrY));
	MySprite start_game("image/startgame.png", scrX, scrY, int(0.45 * scrX), int(0.11 * scrY));
	MySprite died("image/died.jpg", scrX, scrY);
	
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
	MyText total_score("Total score: 0 : 0");
	total_score.set_scale(scrX);
	total_score.set_pos(int(scrX * 0.01), int(scrY * 0.01));
	//-----------------------------------------------------------------------
	gold.set_scale(scrX);
	gold.set_pos(int(scrX * 0.01), int(scrY * 0.7));
	
	Endgame end;
	
	comp.set_heroes();
	while (window.isOpen())
	{
		

		if (!shop.store_full)	//if store is empty
		{
			int max_level = player.num_max_level_heroes(); //store level
			shop.set_heroes(max_level);
		}

		sf::Vector2i pos = sf::Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) //close the window when you click on "Close" (or not, I don’t know)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed)
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
							break;//áðèê
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

			if (event.type == sf::Event::MouseButtonReleased) //releasing the mouse button
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
						window.clear();
						Battle battle(&window, scrX, scrY, temp_player, temp_comp);
						switch (battle.start_battle())
						{
						case 1:
							player.victory();
							comp.set_heroes();
							break;
						case 2:
							comp.victory();
							break;
						default:
							player.victory();
							comp.victory();
							break;
						}
						if (end.check_end(&player, &comp))
						{
							end.end_game(&window, &background, comp, player);
						}
						total_score.change_text("Total score: " + player.get_score() + " : " + comp.get_score());
						player.end_battle();
						gold.change_text("Your gold: " + player.get_amount_gold());
						shop.refresh();
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
		window.draw(background.get_sprite());//drawing of all sprites, some empty, errors are possible (but they are not)
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
		window.display();
	}
	return;
}
//sets the coordinates on the screen depending on the resolution and the number of points
void Purchase::set_position(int* store_position, float plot, int len, int scrX, int scrY)
{
	len = len - 1;
	for (int i = 0; i < len; i++)
	{
		store_position[i] = (i + 1) * int(scrX / (len + 1)) - 146 * (scrX / 3000.0);//coordinate x
	}
	store_position[len] = int(scrY * plot); //'y' coordinates, everyone has one 
}