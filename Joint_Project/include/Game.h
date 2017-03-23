#ifndef GAME_H
#define GAME_H

/// <summary>
/// Author: Peter Daly, John O'Grady, Jack O'Kelly, D.J. O'Leary
/// Version: 1.0
/// Created: 03/03/2017
/// </summary>

#include "SFML\Graphics.hpp"
#include "Xbox360Controller.h"
#include "Widget.h"
#include "Menu.h"
#include "Options.h"
#include "Play.h"
#include "Garage.h"
#include "Splash.h"
#include "PreRace.h"
#include "EndScreen.h"
#include "GameState.h"
#include "Credits.h"
#include <iostream>
#include "SFML\Audio.hpp"

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

	GameState *m_currentGameState;	// Stores the current game state
	Xbox360Controller m_controller;	// stores the controller object
	LevelData m_level;	// Stores the level object

	sf::View DefaultView;	// a view variable allowing us to reset the view

	// Objects for all the screens and relevant classes
	Menu *m_menuScreen;
	Garage *m_upgradeScreen;
	Options *m_optionsScreen;
	Splash *m_splashScreen;
	Play *m_playScreen;
	PreRace *m_preRaceScreen;
	EndScreen *m_endScreen;
	Player *m_player;
	Credits *m_credits;

	// Music variables
	sf::SoundBuffer sBuffer;
	sf::Sound music;

	sf::Clock m_clock;
};
#endif // !GAME_H