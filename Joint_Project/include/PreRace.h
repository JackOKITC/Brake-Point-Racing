#ifndef  PRERACE_H
#define  PRERACE_H

#include <SFML\Graphics.hpp>
#include "GameState.h"
#include "Widget.h"
#include "ResourceManager.h"
#include "SFML\Audio.hpp"

enum class raceSelection	// Enum for the buttons
{
	Option1,
	Option2,
	Option3,
	Option4
};

class PreRace
{
public: 
	PreRace(sf::Font font, GameState *gameState);
	~PreRace();

	void update(GamePadState m_state, Xbox360Controller & m_controller);
	void render(sf::RenderWindow & window);

	void checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller);	// Function to check which button is selected
	void selectedButton(GamePadState m_state, Xbox360Controller m_controller);	// Function to check if the selected button is clicked

	raceSelection m_buttonSelected = raceSelection::Option4; // The button enum which starts on the first option

	bool m_whichLabel;

private: 

	GameState *m_gameState;
	sf::Font m_font;

	Button *m_rightButton;
	Button *m_leftButton;
	Button *m_backButton;
	Button *m_raceButton;
	Label *m_grassLabel;
	Label *m_icyLabel;

	Widget *widgets[6];

	std::string m_leftString = "Next";
	std::string m_rightString = "Next";
	std::string m_backString = "Back";
	std::string m_raceString = "Race";

	std::string m_grassString = "Grassy Plains";

	std::string m_icyString = "Icy Wasteland";
	
	
	int m_currentBtn = 0;
	const int WIDGET_COUNT = 4;
};
#endif // ! PRERACE_H

