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
	// Function to construct the end screen
	EndScreen(sf::Font font, GameState *gameState);

	// Function to de-construct the end screen
	~EndScreen();

	// Function to update the end screen
	void update(Xbox360Controller & controller, sf::Time dt, int position);

	// Function to draw everything in the end screen
	void render(sf::RenderWindow & window);

	void checkButton(GamePadState m_state, Xbox360Controller m_controller);	// Function to check if the selected button is clicked

private: 
	GameState * m_gameState;
	Button * m_backButton;
	std::string m_backString = "Back";
	sf::Font m_font;
	sf::View m_view;
	int m_position;
	std::stringstream ss;
	Label * m_label;
};
#endif // !ENDSCREEN_H

