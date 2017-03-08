#ifndef OPTIONS_H
#define OPTIONS_H

#include <SFML\Graphics.hpp>
#include "GameState.h"
#include "Widget.h"

enum class optionsButton	// Enum for the buttons
{
	Option1,
	Option2,
	Option3
};

class Options
{
public:

	Options(sf::Font font, GameState *gameState);

	~Options();

	void update(GamePadState m_state, Xbox360Controller & m_controller);
	void render(sf::RenderWindow & window);


private:
	GameState *m_state;

	void checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller);	// Function to check which button is selected
	void selectedButton(GamePadState m_state, Xbox360Controller m_controller);	// Function to check if the selected button is clicked

	optionsButton m_buttonSelected = optionsButton::Option1; // The button enum which starts on the play button
	std::string m_string = "Option1";

	sf::Font m_font;

	Button *m_button;
	Slider *m_slider;

	Widget *widgets[2];

	int m_sliderValue;
	int m_currentBtn = 0;
	const int BUTTON_COUNT = 2;
};
#endif // !OPTIONS_H
