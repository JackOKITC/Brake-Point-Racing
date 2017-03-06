#ifndef GAME_H
#define GAME_H

#include "SFML\Graphics.hpp"
#include "Xbox360Controller.h"
#include "Widget.h"
#include <iostream>

enum GameState
{
	Splash,
	Menu,
	Play,
	Options,
	Credits
};

class Game
{
public:
	Game(sf::Font & font);
	~Game();

	void run();

private:

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow & window);

	void setGameState(GameState gameState);

	sf::RenderWindow m_window;
	sf::Font m_font;

	GameState m_currentGameState;

	Xbox360Controller m_controller;
};
#endif // !GAME_H