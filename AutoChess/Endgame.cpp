#include "Endgame.h"

bool Endgame::check_end(User* player, Computer* comp)
{
	player_win = player->score == 10;
	return comp->score == 10 || player->score == 10;
}

void Endgame::end_game(sf::RenderWindow* window, MySprite* background, Computer comp, User player)
{
	int scrX = window->getSize().x;
	int scrY = window->getSize().y;
	MyText score("END GAME\n\n	SCORE\n	 " + player.get_score() + "  :  " + comp.get_score());
	score.set_scale(scrX*2);
	score.set_pos(scrX / 2.0 - int(400 * (scrX / 3000.0)), scrY / 2.0 - int(500*(scrY / 2000.0)));


	while (window->isOpen())
	{
		sf::Event event;
		while (window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed) //close the window when you click on "Close" (or not, I don’t know)
			{
				window->close();
				return;
			}
		}

		window->clear();
		window->draw(background->sprite);
		window->draw(score.get_text());
		window->display();
	}


}