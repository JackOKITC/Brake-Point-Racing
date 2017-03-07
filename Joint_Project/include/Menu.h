#ifndef MENU_H
#define MENU_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Widget.h"
#include "Xbox360Controller.h"

enum button	// Enum for the buttons
{
	Play,
	Options,
	Exit
};

class Menu
{
public:
	Menu(sf::Font & font);
	~Menu();

	void update(GamePadState m_state, Xbox360Controller & m_controller);
	void render(sf::RenderWindow & window);

	bool changeGameState();

	void checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller);	// Function to check which button is selected
	void selectedButton(GamePadState m_state, Xbox360Controller m_controller);	// Function to check if the selected button is clicked


private:
	bool m_changeState;

	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

	sf::Font m_font;
	button m_buttonSelected = button::Play; // The button enum which starts on the play button
	std::string m_strings[3] = { "Memes", "Dreams", "Mimes" };

	Button *m_buttons[3];
};
#endif // !MENU_H
