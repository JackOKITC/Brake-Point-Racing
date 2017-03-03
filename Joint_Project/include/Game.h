#pragma once
#ifndef GAME_H
#define GAME_H

#include "SFML\Graphics.hpp"
#include <iostream>

class Game
{
public:
	Game(sf::Font & font);
	~Game();

	void run();

private:

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow & window);

	sf::RenderWindow m_window;
	sf::Font m_font;

};
#endif // !GAME_H