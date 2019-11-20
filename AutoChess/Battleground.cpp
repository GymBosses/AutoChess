#include <SFML/Graphics.hpp>
#include <Windows.h>
#include <string>
#include "Battleground.h"

//using namespace sf;
//using namespace std;

Battleground::Battleground(sf::Sprite* heroes)
{
	for (int i = 1; i < 15; i++)
	{
		all_heroes[i] = heroes[i];
	}
}