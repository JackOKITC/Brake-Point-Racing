#ifndef MENU_H
#define MENU_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Widget.h"

class Menu
{
public:
	Menu(sf::Font & font);
	~Menu();

	void update();
	void render(sf::RenderWindow & window);

	bool changeGameState();

private:
	bool m_changeState;

	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

	sf::Font m_font;

	std::string m_string;

	Button *m_button;
};
#endif // !MENU_H
