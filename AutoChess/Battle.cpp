#include "Battle.h"

Battle::Battle(sf::RenderWindow* win, int X, int Y, User temp_pl, Computer temp_cp)
{
	window = win;
	temp_player = temp_pl;
	temp_comp = temp_cp;
	scrX = X;
	scrY = Y;
}

int Battle::start_battle()
{
	MySprite died("image/died.jpg", scrX, scrY);

	MySprite background("image/pubg+cats.jpg", scrX, scrY); //image background
	background.full_screen(window->getSize().x, window->getSize().y);
	background.set_color(255, 255, 255, 128);

	MyText characteristic[12];
	for (int i = 0; i < 12; i++)
	{
		characteristic[i].set_scale(scrX);
	}

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

	sf::Clock clock;
	sf::Clock turn_clock;
	bool turn = true;
	float time = 0.0;
	float time_turn = 0.0;

	while (end_game)
	{
		time = clock.getElapsedTime().asSeconds();
		time_turn = turn_clock.getElapsedTime().asSeconds();

		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) //close the window when you click on "Close" (or not, I don’t know)
			{
				window->close();
				return 0;
			}
		}

		bool check_comp = temp_comp.all_died();
		bool check_player = temp_player.all_died();

		window->clear();
		window->draw(background.sprite);
		for (int i = 0; i < 3; i++)
		{
			if (temp_player.heroes[i].hero_died())
			{
				temp_player.heroes[i].set_texture(died.sprite);
				window->draw(temp_player.get_item(i));
			}
			else window->draw(temp_player.get_item(i));
			if (temp_comp.heroes[i].hero_died())
			{
				temp_comp.heroes[i].set_texture(died.sprite);
				window->draw(temp_comp.get_item(i));
			}
			else window->draw(temp_comp.get_item(i));
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
				characteristic[i].set_pos(pos_hero.x + 210 * (scrX / 3000.0), pos_hero.y - 100 * (scrX / 3000.0));
			}
			else
			{
				characteristic[i].change_text(temp.get_attack(num));
				characteristic[i].set_pos(pos_hero.x, pos_hero.y - 100 * (scrX / 3000.0));
			}
			window->draw(characteristic[i].get_text());
		}
		if (time >= 1.5 && !(check_comp || check_player))
		{
			if (turn)
			{
				temp_player.attack_player(&temp_comp);
				turn = false;
			}
			else
			{
				temp_comp.attack_player(&temp_player);
				turn = true;
			}
			clock.restart();
		}

		if ((check_comp || check_player) || time_turn >= 40.0)
		{
			int rnd = rand() % 3;
			if (check_comp)
			{
				window->draw(won[rnd].sprite);
			}
			if (check_player)
			{
				window->draw(lost[rnd].sprite);
			}
			time = 0;
			time_turn = 0;
			clock.restart(); window->display();
			while (time <= 2)
			{
				time = clock.getElapsedTime().asSeconds();
			}
			if (check_comp) return 1;
			if (check_player) return 2;
			return 0;
			end_game = false;
		}
		window->display();
	}
	return 0;
}