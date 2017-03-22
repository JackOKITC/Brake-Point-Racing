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
#include "PreRace.h"
#include "EndScreen.h"
#include "GameState.h"
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

	GameState *m_currentGameState;
	Xbox360Controller m_controller;
	LevelData m_level;

	sf::View DefaultView;

	Menu *m_menuScreen;
	Garage *m_upgradeScreen;
	Options *m_optionsScreen;
	Splash *m_splashScreen;
	Play *m_playScreen;
	PreRace *m_preRaceScreen;
	EndScreen *m_endScreen;
	Player *m_player;


	sf::SoundBuffer sBuffer;
	sf::Sound music;

	sf::Clock m_clock;
};
#endif // !GAME_H