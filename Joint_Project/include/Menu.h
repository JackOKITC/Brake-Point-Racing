#ifndef MENU_H
#define MENU_H

/// <summary>
/// Author: John O'Grady, Jack O'Kelly
/// Version: 1.0
/// Created: 08/03/2017
/// </summary>

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Widget.h"
#include "GameState.h"
#include "Xbox360Controller.h"
#include "ResourceManager.h"

enum class button	// Enum for the buttons
{
	Play,
	Garage,
	Options,
	Credits,
	Exit
};

class Menu
{
	const sf::Time TIME_PER_UPDATE;	// The TIME_PER_UPDATE variable for the menu transition.

public:
	Menu(sf::Font & font, GameState *gameState);	// The constructor for the menu object
	~Menu();	// The deconstructor for the menu object

	/// <summary>
	/// Update method which updates based on the current GameState,
	/// The controller object, and the time passed
	/// </summary>
	void update(GamePadState m_state, Xbox360Controller & m_controller, sf::Time deltaTime);

	/// <summary>
	/// The render method which renders based on the
	/// current Render Window and the Clock
	/// </summary>
	void render(sf::RenderWindow & window, sf::Clock clock);

	void checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller);	// Function to check which button is selected
	void selectedButton(GamePadState m_state, Xbox360Controller m_controller);	// Function to check if the selected button is clicked

private:
	GameState *m_gameState;	// Pointer to the current gamestate
	
	// Label variables
	const int LABEL_COUNT = 5;
	int m_currentLab;

	bool m_timeStop;	// bool stored which tells when time is stopped
	bool m_transitionStop;	// Bool stored which tells when transition stops

	sf::Time m_time;	// Time variable

	// Background texture variables
	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

	// Flag texture variables
	sf::Texture m_flagTex;
	sf::Sprite m_flagSprite;

	/// <summary>
	/// all the convex line variables used in the indicators that show
	/// when a label is selected
	/// </summary>
#pragma region Convex Lines
	
	sf::ConvexShape m_raceLine;
	sf::ConvexShape m_garLine;
	sf::ConvexShape m_optLine;
	sf::ConvexShape m_credLine;
	sf::ConvexShape m_exitLine;

	sf::Color m_select = sf::Color(225, 30, 30);
	sf::Color m_unselect = sf::Color(170, 50, 50);

#pragma endregion

	sf::Font m_font;	// font storage
	button m_buttonSelected = button::Play;	// The button enum which starts on the play button

	// Label variables for strings and array of labels
	std::string m_strings[5] = { "Race", "Garage", "Options", "Credits", "Exit" };
	Label *m_labels[5];
	Label *m_outline[5];

	sf::Shader m_shader;	// Stores the shader variable
};
#endif // !MENU_H
