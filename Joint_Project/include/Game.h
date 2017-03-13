#ifndef GAME_H
#define GAME_H

#include "SFML\Graphics.hpp"
#include "Xbox360Controller.h"
#include "Widget.h"
#include "Menu.h"
#include "Options.h"
#include "Play.h"
#include "Garage.h"
#include "Splash.h"
#include "GameState.h"
#include <iostream>
#include "ResouceManager.h"

class Game
{
public:
	Game(sf::Font & font, sf::Font & titleFont);
	~Game();

	void run();


private:
	

	void update(sf::Time deltaTime);
	void render(sf::RenderWindow & window);
	
	GameState m_screen = GameState::SPLASH_STATE;

	sf::RenderWindow m_window;
	sf::Font m_font;
	sf::Font m_titleFont;

	GameState *m_currentGameState;

	Xbox360Controller m_controller;

	Menu *m_menuScreen;
	Garage *m_upgradeScreen;
	Options *m_optionsScreen;
	Splash *m_splashScreen;
	Play *m_playScreen;
};
#endif // !GAME_H