#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

int main()
{
	RenderWindow window(VideoMode(1920, 1920), "Game 0.001"); 

	Texture background_texture;
	background_texture.loadFromFile("image/pubg+cats.jpg");
	Sprite background_sprite;
	background_sprite.setTexture(background_texture);
	background_sprite.setScale(
		window.getSize().x / background_sprite.getLocalBounds().width,
		window.getSize().y / background_sprite.getLocalBounds().height);
	background_sprite.setColor(Color(255, 255, 255, 128));

	Image hero;
	hero.loadFromFile("image/Ассасин.jpg");
	Texture herotexture;
	herotexture.loadFromImage(hero);
	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setPosition(50, 50);

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			Mouse ms;
			float x = ms.getPosition(window).x;
			float y = ms.getPosition(window).y;
			if (x <= herosprite.getPosition().x + 288.0f &&
				x >= herosprite.getPosition().x &&
				y <= herosprite.getPosition().y + 400.0f &&
				y >= herosprite.getPosition().y) 
			{
			herosprite.setPosition(x - 144, y - 200);
			}
		}

		window.clear();
		window.draw(background_sprite);
		window.draw(herosprite);
		window.display();
	}

	return 0;
}