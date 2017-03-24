#ifndef GARAGE_H
#define GARAGE_H

/// <summary>
/// Authors: John O'Grady, DJ O'Leary
/// Version: 1.0
/// Created: 16/02/2017
/// </summary>

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
	/// <summary>
	/// Constructor that takes 4 arguments, them being:
	/// font which stores the font that will be used to draw text to the screen,
	/// currencyFont which stores the font that will be used to draw text to the screen,
	/// gameState is a pointer to the object in game.cpp,
	/// player is a pointer the player object.
	/// </summary>
	/// <param name="font"></param>
	/// <param name="currencyFont"></param>
	/// <param name="gameState"></param>
	/// <param name="player"></param>
	Garage(sf::Font font, sf::Font currencyFont, GameState *gameState, Player * player);
	~Garage();	// De-constructor for the garage screen.

	/// <summary>
	/// Takes 2 arguments, them being:
	/// controller which is a reference to the controller object in game.cpp,
	/// dt is the time between updates.
	/// 
	/// This is also where any other method that needs to be called frequently is called.
	/// </summary>
	/// <param name="controller"></param>
	/// <param name="dt"></param>
	void update(Xbox360Controller & controller, sf::Time dt);
	void render(sf::RenderWindow & window);	// Where everything is drawn to the game window.

	void checkSelection(GamePadState m_state, Xbox360Controller m_controller);	// Function to check which button is selected
	void checkButton(GamePadState m_state, Xbox360Controller m_controller);	// Function to check if the selected button is clicked
	void updateUI(); // used to update the currentlly displayed stats/upgrades onscreen

private:

	GameState *m_gameState;	// Pointer to the object in game.cpp.
	Player *m_player;	// Pointer to the player object.
	bool m_transitionToNext = false;	// Represents whether the player is selecting a car or upgrading one.
	sf::Texture m_backgroundTex;	// Stores the background texture.
	sf::Sprite m_backgroundSprite;	// Represents the background in the game world.
	sf::Font m_textFont, m_currencyFont;	// Used to draw text to the screen.

	Xbox360Controller * m_controller;

	// stat elements
	std::string m_strings[5] = { "Brakes", "Handling", "Acceleration", "Medals: ", "Cost: " }; 	// strings to apply to labels
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

	// integers to keep track of how much each stat of each car has been upgraded
	int carOneUpgradeLevels[3];
	int carTwoUpgradeLevels[3];
	int carThreeUpgradeLevels[3];

	// variables for the upgrade purchasing system
	Label * m_currency;
	Label* m_cost;
	int m_upgrdCost;
};
#endif // !GARAGE
