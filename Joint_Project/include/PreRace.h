#ifndef  PRERACE_H
#define  PRERACE_H

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
	PreRace(sf::Font font, GameState *gameState, Player *player);
	~PreRace();

	void update(GamePadState m_state, Xbox360Controller & m_controller);
	void render(sf::RenderWindow & window);

	void checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller);	// Function to check which button is selected
	void selectedButton(GamePadState m_state, Xbox360Controller m_controller);	// Function to check if the selected button is clicked

	raceSelection m_buttonSelected = raceSelection::MapPrev; // The button enum which starts on the first option

	bool m_whichLabel;

private: 
	Player *m_player;
	GameState *m_gameState;
	sf::Font m_font;

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
	
	int m_currentCar;
	int m_currentBtn = 0;
	const int WIDGET_COUNT = 7;
};
#endif // ! PRERACE_H

