#ifndef MENU_H
#define MENU_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Widget.h"
#include "GameState.h"
#include "Xbox360Controller.h"
#include "ResouceManager.h"

enum class button	// Enum for the buttons
{
	Play,
	Garage,
	Options,
	Exit
};

class Menu
{
	const sf::Time TIME_PER_UPDATE;

public:
	Menu(sf::Font & font, GameState *gameState);
	~Menu();

	void update(GamePadState m_state, Xbox360Controller & m_controller, sf::Time deltaTime);
	void render(sf::RenderWindow & window);

	void checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller);	// Function to check which button is selected
	void selectedButton(GamePadState m_state, Xbox360Controller m_controller);	// Function to check if the selected button is clicked


private:
	GameState *m_gameState;
	const int LABEL_COUNT = 4;
	int m_currentLab;

	bool m_timeStop;
	bool m_transitionStop;

	sf::Time m_time;

	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

#pragma region Convex Lines
	
	sf::ConvexShape m_raceLine;
	sf::ConvexShape m_garLine;
	sf::ConvexShape m_optLine;
	sf::ConvexShape m_exitLine;

	sf::Color m_select = sf::Color(225, 30, 30);
	sf::Color m_unselect = sf::Color(170, 50, 50);

#pragma endregion
	sf::Font m_font;
	button m_buttonSelected = button::Play; // The button enum which starts on the play button

	std::string m_strings[4] = { "Race", "Garage", "Options", "Exit" };

	Label *m_labels[4];
};
#endif // !MENU_H
