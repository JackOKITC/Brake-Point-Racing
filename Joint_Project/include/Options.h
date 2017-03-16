#ifndef OPTIONS_H
#define OPTIONS_H

#include <SFML\Graphics.hpp>
#include "GameState.h"
#include "Widget.h"
#include "ResourceManager.h"
#include "SFML\Audio.hpp"
#include "SFML\Audio\SoundSource.hpp"

enum class optionsSelection	// Enum for the buttons
{
	Option1,
	Option2,
	Option3,
	Option4
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

	optionsSelection m_buttonSelected = optionsSelection::Option1; // The button enum which starts on the first option
	
	std::string m_helpString = "Help";
	std::string m_exitString = "Back";
	std::string m_screenString = "Fullscreen:";

	sf::Font m_font;

	GameState *m_gameState;

	Button *m_helpButton;
	Button *m_exitButton;
	Slider *m_volSlider;
	RadioButton *m_screenRadio;

	sf::SoundSource *volume;

	float m_volume;

	Widget *widgets[4];

	sf::Texture m_radioTex;

	int m_sliderValue;
	int m_currentBtn = 0;
	const int BUTTON_COUNT = 4;
};
#endif // !OPTIONS_H
