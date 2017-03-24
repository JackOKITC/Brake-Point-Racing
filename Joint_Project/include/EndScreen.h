#ifndef ENDSCREEN_H
#define ENDSCREEN_H

/// <summary>
/// Author: Peter Daly
/// Version: 1.0
/// Created: 22/03/2017
/// </summary>

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Xbox360Controller.h"
#include "ResourceManager.h"
#include "GameState.h"
#include "Widget.h"
#include <sstream>

class EndScreen
{
public: 
	/// <summary>
	/// Constructor that has 2 arguments, them being:
	/// font stores the font that will be used to draw the text to the screen.
	/// gameState is a pointer to the gameState variable in Game.cpp.
	/// </summary>
	/// <param name="font"></param>
	/// <param name="gameState"></param>
	EndScreen(sf::Font font, GameState *gameState);

	~EndScreen();	// Function to de-construct the end screen

	void update(Xbox360Controller & controller, sf::Time dt, int position);	// Function to update the end screen

	void render(sf::RenderWindow & window);	// Function to draw everything in the end screen

	void checkButton(GamePadState m_state, Xbox360Controller m_controller);	// Function to check if the selected button is clicked

private: 
	GameState * m_gameState;	// A pointer to the object in game.cpp
	Button * m_backButton;	// A pointer to a button.
	std::string m_backString = "Back";	// The String that will be passed to the button.
	sf::Font m_font;	// Stores the font used to draw the text on the game window.
	sf::View m_view;	// The view of the game world.
	int m_position;	// Stores the position of the text.
	std::stringstream ss;	// Stores and displays text to the screen.
	Label * m_label;	// Pointer to a label.
};
#endif // !ENDSCREEN_H

