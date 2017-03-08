#ifndef GAME_H
#define GAME_H

#include "SFML\Graphics.hpp"
#include "Xbox360Controller.h"
#include "Widget.h"
#include "Menu.h"
#include "Options.h"
#include "Play.h"
#include "Splash.h"
#include "GameState.h"
#include <iostream>

class Game
{
public:
	Game(sf::Font & font, sf::Font & titleFont);
	~Game();

	void run();

	void checkGameStateChange();

private:

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow & window);
	
	GameState m_screen = GameState::SPLASH_STATE;

	sf::RenderWindow m_window;
	sf::Font m_font;
	sf::Font m_titleFont;

	GameState m_currentGameState;

	Xbox360Controller m_controller;

	Splash *m_splashScreen;
	Menu *m_menuScreen;
};
#endif // !GAME_H