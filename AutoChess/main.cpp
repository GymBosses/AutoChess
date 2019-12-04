#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include "Player.h"
#include "Shop.h"
#include "Battleground.h"
#include "MySprite.h"
#include "Computer.h"
#include "User.h"
////Size cards = (292, 400)

const int scrX = 3000; //������� ������(������ ��� ���� �����, ����� �����������)
const int scrY = 2000;
bool battle = false;   //�������� �� ����� ����: ���(true) ��� ������� ����������
sf::Vector2f oldPos;   //����� ���, ��� ����������� ������, ���������� ��� ������ �������

//����� �����(x1, x2...xn, y), ��� ������������� �������(x1,y)(x2,y) �������� � ���� ������
void set_position(int* store_postion, float plot, int len);
bool move_from_bg;     //���� �������� �� ������������(true) ��� � ��������(false)

int main()
{
	sf::RenderWindow window(sf::VideoMode(scrX, scrY), "Game 0.001");//��������� ���� ����
	sf::Sprite heroes[15];			//���� ����� ������ �� ����(�� 1 �� 14, ��� [0] - ������)
	sf::Texture herotexture[14];
	//-----------------------------
	for (int i = 1; i <= 14; i++)
	{
		std::string full_path = "image/" + std::to_string(i) + ".jpg"; //���� � ����� jpg
		herotexture[i - 1].loadFromFile(full_path);					   //��������� �������� 
		heroes[i].setTexture(herotexture[i - 1]);					   //������������� �������� � ������
	}
	//----------------------------------------
	//------------------------------SET_STORE_POSITION AND PLAYER_FIELD
	int store_position[5];                 //����� (x1, x2, x3, y), ��� ����� ����������� �������� � ��������
	set_position(store_position, 0.75, 5);
	int player_field[4];				//���������� �� ����
	set_position(player_field, 0.50, 4);
	int comp_field[4];
	set_position(comp_field, 0.10, 4);
	//------------------------------ ��������� ����������
	sf::Texture background_texture;
	background_texture.loadFromFile("image/pubg+cats.jpg");
	sf::Sprite background_sprite;
	background_sprite.setTexture(background_texture);
	background_sprite.setScale( //����������� ����������� �� ���� �����
		window.getSize().x / background_sprite.getLocalBounds().width,
		window.getSize().y / background_sprite.getLocalBounds().height);
	background_sprite.setColor(sf::Color(255, 255, 255, 128)); //50% ������������
	//------------------------------------------������ ���������� �������� � ��������� ������ �������
	//REFRESH/////////////////////////////////////////////////////
	sf::Texture refresh_texture;
	refresh_texture.loadFromFile("image/refresh.png");
	sf::Sprite refresh;
	refresh.setTexture(refresh_texture);
	refresh.setPosition(int(0.05 * scrX), int(0.80 * scrY));
	//UP LEVEL////////////////////////////////////////////////////
	sf::Texture levelup_texture;
	levelup_texture.loadFromFile("image/levelup.png");
	sf::Sprite levelup;
	levelup.setTexture(levelup_texture);
	levelup.setPosition(int(0.80 * scrX), int(0.05 * scrY));
	//START GAME//////////////////////////////////////////////////
	sf::Texture start_game_texture;
	start_game_texture.loadFromFile("image/startgame.png");
	sf::Sprite start_game;
	start_game.setTexture(start_game_texture);
	start_game.setPosition(int(0.9 * scrX), int(0.5 * scrY));
	///////////////////////////////////////////////////////////
	bool isMove = false;
	float dx, dy;
	//-----------------------------����� � ����������� �������� � ������
	sf::Font font;
	font.loadFromFile("font/Alata-Regular.ttf");
	sf::Text gold;
	sf::Text characteristic[12];
	for (int i = 0; i < 12; i++)
	{
		characteristic[i].setFont(font);
		characteristic[i].setFillColor(sf::Color::White);
		characteristic[i].setCharacterSize(80);
	}
	gold.setFont(font);
	gold.setFillColor(sf::Color::White);
	gold.setCharacterSize(80);
	gold.setPosition(int(scrX * 0.01), int(scrY * 0.7)); //��� ���� ��������, ���� ���������
	//CATS IS DIED//////////////////////
	sf::Texture died_texture;
	died_texture.loadFromFile("image/died.jpg");
	sf::Sprite died;
	died.setTexture(died_texture);
	//YOU WIN///////////////////////////
	sf::Texture win_texture;
	win_texture.loadFromFile("image/win.png");
	sf::Sprite win;
	win.setTexture(win_texture);
	win.setPosition((scrX) / 2 - 200, (scrY) / 2 - 50);
	//YOU LOSE//////////////////////////
	sf::Texture lose_texture;
	lose_texture.loadFromFile("image/lose.png");
	sf::Sprite lose;
	lose.setTexture(lose_texture);
	lose.setPosition((scrX) / 2 - 200, (scrY) / 2 - 50);
	////////////////////////////////////
	//------------------------------------------
	User player;	//Player
	User temp_player;
	Computer comp(heroes, comp_field);  //Computer
	Computer temp_comp = comp;
	Shop shop(heroes, store_position); //������� �����
	Battleground bg_player(heroes, player_field); //������� ����
	gold.setString("Your gold: " + player.get_amount_gold()); //���������� � text ������
	sf::Clock clock;
	bool turn = true;
	float time = 0;
	comp.set_heroes();
	while (window.isOpen())
	{
		time = clock.getElapsedTime().asSeconds();
		if (!battle && !shop.store_full)	//���� ������� ����
		{
			int max_level = player.num_max_level_heroes(); //������� �������
			shop.set_heroes(max_level);
		}

		sf::Vector2i pos = sf::Mouse::getPosition(window);

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) //��������� ���� ��� ������� �� "�������" (��� ���, �� ����)
				window.close();

			if (event.type == sf::Event::MouseButtonPressed && !battle)
			{
				if (event.key.code == sf::Mouse::Left) //��������
				{
					for (int i = 0; i < 4; i++)
					{
						if (shop.check_point(i, pos))		//������ �� ����-�� �� ��������
						{
							isMove = true;
							move_from_bg = false;
							shop.set_pl_ch(i);				//����� ����� �� ��������, ������� ������ �����
							sf::Vector2f t = shop.get_pos();
							dx = pos.x - t.x;
							dy = pos.y - t.y;
							oldPos = t;
							break;//����
						}
						else if (i != 3 && bg_player.check_point(i, pos)) //������ �� ����-�� �� ������� ����
						{
							isMove = true;
							move_from_bg = true;		//���������� ����
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

			if (event.type == sf::Event::MouseButtonReleased && !battle) //���������� ������ ����
			{
				if (event.key.code == sf::Mouse::Left)// �� ������
				{
					if (isMove) //�� ���-�� ������� ������
					{
						if (!move_from_bg) { //�� ��������
							if (!bg_player.check_full_bg() && shop.check_item_on_field(scrY))
							{//���� �� ����� �� ���� � � ��������� �� ����� �� ����������(0.3*scrY < y < 0.7*scrY)
								int hero_number;
								hero_number = shop.get_num_hero();
								if (player.buy_hero(hero_number)) //����� �� ������, ���� �� - ��������(����� ��������� �� 2 ������)
								{
									gold.setString("Your gold: " + player.get_amount_gold());
									shop.delete_item();				//������� �� ��������
									bg_player.set_hero(hero_number);//��������� � ������� ����
								}
								else shop.move_item(oldPos);//���� ��� ����� - ���������� ������
							}
							else shop.move_item(oldPos);
						}
						//������ ����� �� battleground
						else if (move_from_bg && bg_player.check_item_on_field(scrY))
						{
							int k = oldPos.x;
							int index = k / (int(scrX / 4) - 146) - 1; //���, ����������. ����� �� �����(����� �������) ������
							bg_player.sell_hero();		//����� ������ ���� delete, �� ��� ��� ���
							player.sell_hero(index);	//������ �� ����������� ������
							gold.setString("Your gold: " + player.get_amount_gold());
						}
						else
						{
							bg_player.move_item(oldPos); //���������� �������
						}
						shop.set_pl_ch(-1); //������������� ����� ������ -1 (������������)
						bg_player.set_pl_ch(-1);
						isMove = false;
					}

					if (refresh.getGlobalBounds().contains(pos.x, pos.y))//���������� ��������, ����� ����� ������
					{
						if (player.refresh()) //������� �� �����(����� ��������� �� 2 ������), ���� ��, �� -1 ����
						{
							shop.refresh();
							gold.setString("Your gold: " + player.get_amount_gold());
						}
					}

					if (levelup.getGlobalBounds().contains(pos.x, pos.y)) //��������� ������ ��������
					{
						if (player.up_level())
						{
							shop.set_heroes(player.num_max_level_heroes());
							gold.setString("Your gold: " + player.get_amount_gold());
						}
						comp.up_level();
					}

					if (start_game.getGlobalBounds().contains(pos.x, pos.y))
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
						clock.restart();
						time = 0;
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
		window.draw(background_sprite);
		if (!battle)
		{	//������� ���� ��������, �������� ������, �������� ������(�� �� ���)
			for (int i = 0; i < 3; i++)
			{
				window.draw(shop.get_item(i));
				window.draw(bg_player.get_item(i));
			}
			window.draw(shop.get_item(3));
			window.draw(refresh);
			window.draw(levelup);
			window.draw(start_game);
			window.draw(gold);
		}
		if (battle)
		{
			for (int i = 0; i < 3; i++)
			{
				if (temp_player.heroes[i].hero_died())
				{
					temp_player.heroes[i].set_texture(died);
					window.draw(temp_player.get_item(i));
				}
				else window.draw(temp_player.get_item(i));
				if (temp_comp.heroes[i].hero_died())
				{
					temp_comp.heroes[i].set_texture(died);
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
					characteristic[i].setString(temp.get_health(num));
					characteristic[i].setPosition(pos_hero.x + 210, pos_hero.y - 100);
				}
				else
				{
					characteristic[i].setString(temp.get_attack(num));
					characteristic[i].setPosition(pos_hero.x, pos_hero.y - 100);
				}
				window.draw(characteristic[i]);
			}
			if (time >= 1)
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
			bool check_comp = temp_comp.all_died();
			bool check_player = temp_player.all_died();
			if (check_comp || check_player)
			{
				battle = false;
				if (check_comp)
				{
					window.draw(win);
					player.victory();
				}
				if (check_player)
				{
					window.draw(lose);
					comp.victory();
				}
				window.display();
				shop.refresh();
				time = 0;
				clock.restart();
				while (time <= 2)
				{
					time = clock.getElapsedTime().asSeconds();
				}
				comp.set_heroes();
			}
			if (comp.score == 3 || player.score == 3)
			{
				if (check_comp)
				{
					window.draw(win);
				}
				if (check_player)
				{
					window.draw(lose);
				}
				while (time <= 2)
				{
					time = clock.getElapsedTime().asSeconds();
				}
				window.close();
			}
		}
		window.display();

	}
	return 0;
}

//������� ��� ��� ��������� �����(������������� ���������� �� ������ � ����������� �� ���������� � ���������� �����
void set_position(int* store_position, float plot, int len)
{
	len = len - 1;
	for (int i = 0; i < len; i++)
	{
		store_position[i] = (i + 1) * int(scrX / (len + 1)) - 146;//���������� x
	}
	store_position[len] = int(scrY * plot); //���������� y, ��� � ���� ����(��� ������� �� ����� ������ ����)
}