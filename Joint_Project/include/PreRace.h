#ifndef  PRERACE_H
#define  PRERACE_H

/// <summary>
/// Author: Peter Daly
/// Version: 1.0
/// Created: 20/03/2017
/// </summary>

#include <SFML\Graphics.hpp>
#include "GameState.h"
#include "Widget.h"
#include "Player.h"
#include "ResourceManager.h"
#include "SFML\Audio.hpp"

enum class raceSelection	// Enum for the buttons
{
	MapPrev,
	MapNext,
	CarPrev,
	CarNext,
	Race,
	Back
};

class PreRace
{
public: 
	/// <summary>
	/// Constructor that takes 3 arguments, them being:
	/// font which store the font that will be used to draw all the text to the screen,
	/// gameState is a pointer to the object in game.cpp,
	/// player is a pointer the player object.
	/// </summary>
	/// <param name="font"></param>
	/// <param name="gameState"></param>
	/// <param name="player"></param>
	PreRace(sf::Font font, GameState *gameState, Player *player);
	~PreRace();	// De-constructor for the prerace screen.

	/// <summary>
	/// Takes 2 arguments, them being:
	/// m_state which represents the current state of the game,
	/// m_controller which references the object in game.cpp.
	/// This is also where any other method that needs to be called frequently is called.
	/// </summary>
	/// <param name="m_state"></param>
	/// <param name="m_controller"></param>
	void update(GamePadState m_state, Xbox360Controller & m_controller);
	void render(sf::RenderWindow & window);	// Where everything is drawn to the game window.

	void checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller);	// Function to check which button is selected
	void selectedButton(GamePadState m_state, Xbox360Controller m_controller);	// Function to check if the selected button is clicked

	raceSelection m_buttonSelected = raceSelection::MapPrev; // The button enum which starts on the first option

	bool m_whichLabel;	// Represents which label is highlighted.

private: 
	Player *m_player;	// Pointer the player object.
	GameState *m_gameState;	// Pointer to the object in game.cpp,
	sf::Font m_font;	// Used to draw all the text to the screen,

	// Button and label objects from widget.cpp.
	Button *m_rightButton[2];
	Button *m_leftButton[2];
	Button *m_backButton;
	Button *m_raceButton;
	Label *m_grassLabel;
	Label *m_icyLabel;
	Label *m_carLabel;

	Widget *widgets[9];

	std::string m_leftString = "Previous";
	std::string m_rightString = "Next";
	std::string m_backString = "Back";
	std::string m_raceString = "Race";
	std::string m_grassString = "Grassy Plains";
	std::string m_icyString = "Icy Wasteland";
	std::string m_carTypes[3] = { "Model Seahawk", "Model Typhoon", "Model Baracula" };
	
	int m_currentCar;	// Currently selected car.
	int m_currentBtn = 0;	// Currently selected button.
	const int WIDGET_COUNT = 7;	// Total number of widgets on screen.
};
#endif // ! PRERACE_H

