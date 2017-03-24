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
	/// <summary>
	/// Constructor that takes 2 arguments, them being:
	/// font which stores the font that will be used to draw text to the screen,
	/// titleFont which stores the font that will be used to draw text to the screen.
	/// </summary>
	/// <param name="font"></param>
	/// <param name="titleFont"></param>
	Game(sf::Font & font, sf::Font & titleFont);
	~Game();	// The De-constructor for the Game object.

	void run();

private:
	/// <summary>
	/// Takes a arguments, it being:
	/// deltaTime
	/// This is also where any other method that needs to be called frequently is called.
	/// </summary>
	/// <param name="deltaTime"></param>
	void update(sf::Time deltaTime);
	void render(sf::RenderWindow & window);
	
	GameState m_screen = GameState::SPLASH_STATE;

	sf::RenderWindow m_window;	// The game window.
	sf::Font m_font;	// Used to draw text to the screen.
	sf::Font m_titleFont;	// Used to draw text to the screen.

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