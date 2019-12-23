#include <SFML/Graphics.hpp>
#include "Purchase.h"
////Size cards = (292, 400)

const int scrX = sf::VideoMode::getDesktopMode().width; //Screen sizes (changes to fit your screen, you need to test)
const int scrY = sf::VideoMode::getDesktopMode().height;


int main()
{
	Purchase start_game(scrX, scrY);

	return 0;
}