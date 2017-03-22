#ifndef GARAGE_H
#define GARAGE_H
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Xbox360Controller.h"
#include "ResourceManager.h"
#include "GameState.h"
#include "Player.h"
#include "Widget.h"

class Garage
{
	const sf::Time TIME_PER_UPDATE = sf::microseconds(1000);

public:
	Garage(sf::Font font, GameState *gameState, Player * player);
	~Garage();

	void update(Xbox360Controller & controller, sf::Time dt);
	void render(sf::RenderWindow & window);

	void checkSelection(GamePadState m_state, Xbox360Controller m_controller);	// Function to check which button is selected
	void checkButton(GamePadState m_state, Xbox360Controller m_controller);	// Function to check if the selected button is clicked

private:

	GameState *m_gameState;
	Player *m_player;
	bool m_transitionToNext = false;
	sf::Time currentTime;
	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;
	sf::Font m_font;

	Xbox360Controller * m_controller;

	// stat elements
	std::string m_strings[3] = { "Brakes", "Handling", "Acceleration" }; 	// strings to apply to labels
	Label *m_statLabel[3]; // label for each stat element of cars
	Slider *m_statValues[3]; // sliders which indicate the current "value" of the car stat
	int m_currentStat; // keeps track of the currently selected stat for upgrading

	// upgrade elements
	Bar *m_upgradeBars[3]; // creating pointer to upgrade bars which will track the current level of the upgrade
	sf::Texture m_upgradeText[3]; //upgrade Texture loaded with the resource manage
	sf::Sprite m_uprgradeSpr[3]; // sprite used to represent position and texture of each upgrade

	// car selection elements
	sf::Color m_dim = sf::Color(125, 125, 125, 255); // setting the color for being unseleted, makes the sprite slightly dimmer
	sf::Color m_highlight = sf::Color(255, 255, 255, 255); // setting the "selected" color
	sf::Texture m_carOptions[3]; // loading textures for each player car
	sf::Sprite m_cars[3]; // sprite container for each car 
	int m_currentCar; // keeps track of the currently selected car for upgrading

	// 
	int carOneUpgradeLevels[3];
	int carTwoUpgradeLevels[3];
	int carThreeUpgradeLevels[3];
};
#endif // !GARAGE
