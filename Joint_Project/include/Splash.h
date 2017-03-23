#ifndef SPLASH_H
#define SPLASH_H

/// <summary>
/// Author: Jack O'Kelly
/// Version: 1.0
/// Created: 08/03/2017
/// </summary>

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Xbox360Controller.h"
#include "GameState.h"
#include <sstream>
#include <Thor\Resources.hpp>
#include <Aurora/Config.hpp>
#include "ResourceManager.h"

class Splash
{
	const sf::Time TIME_PER_UPDATE = sf::microseconds(1000); // Initialising the TIME_PER_UPDATE variable for the splash transition.

public:

	Splash(GameState *gameState, sf::Font font);	// Constructor for the splash object.
	~Splash();	// Deconstructor for the splash object.

	/// <summary>
	/// Update method that updates the splash object,
	/// When given the controller and time passed.
	/// </summary>
	void update(Xbox360Controller * controller, sf::Time dt);

	/// <summary>
	/// Render method that renders the splash object,
	/// Based on the current Render Window
	/// </summary>
	void render(sf::RenderWindow & window);

private:

	GameState *m_state;	// A pointer to the current gamestate
	
	bool m_transitionToNext = false;	// Stores the bool which decides when to begin the transition to the menu
	bool m_startPressed = false;	// Stores the bool which turns true when start is pressed
	bool m_highlight = true;	// Stores the bool which stores when a button is highlighted
	
	int alpha;	// Used to store a changeable alpha value used with sf::Color()
	int b;	// Used to store a changeable B (RGB) value used with sf::Color()

	int charSize;	// Used to store the character size for sf::Text, so it can be changed depending on m_highlight
	
	sf::Time currentTime;	// Stores the current time

	sf::Font m_font;	// Variable used to store a font

	// Text variables
	sf::Text m_text;
	sf::Text m_startText;
	sf::Text m_licenseText;

	// Background variables
	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

	Xbox360Controller * m_controller;	// Pointer to the controller object

};
#endif // !SPLASH_H
