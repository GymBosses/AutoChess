#ifndef BG
#define BG
#include <SFML/Graphics.hpp>
//using namespace sf;
//using namespace std;

class Battleground
{
	sf::Sprite all_heroes[15];
public:
	Battleground(sf::Sprite* heroues);
};

#endif