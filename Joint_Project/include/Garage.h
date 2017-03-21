#ifndef GARAGE_H
#define GARAGE_H
#include <SFML\Graphics.hpp>
#include <iostream>
#include "Xbox360Controller.h"
#include "ResourceManager.h"
#include "GameState.h"
#include "Widget.h"

enum class upgradebutton	// Enum for the buttons
{
	Engine,
	Turbo,
	Handling,
	Tires,
	Back
};

class Garage
{
	const sf::Time TIME_PER_UPDATE = sf::microseconds(1000);

public:
	Garage(sf::Font font, GameState *gameState);
	~Garage();

	void update(Xbox360Controller & controller, sf::Time dt);
	void render(sf::RenderWindow & window);

	void checkSelection(GamePadState m_state, Xbox360Controller m_controller);	// Function to check which button is selected
	void checkButton(GamePadState m_state, Xbox360Controller m_controller);	// Function to check if the selected button is clicked

private:

	GameState *m_gameState;
	bool m_transitionToNext = false;

	sf::Time currentTime;
	sf::Color m_dim = sf::Color(125, 125, 125, 255);

	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;
	sf::Font m_font;

	int m_currentCar;
	int m_currentStat;

	Xbox360Controller * m_controller;

	Bar *m_upgradeBars[3];
	Slider *m_statValues[3];
	Label *m_statLabel[3];
	std::string m_strings[3] = { "Brakes", "Handling", "Acceleration" };

	sf::Texture m_upgradeText[3];
	sf::Sprite m_uprgradeSpr[3];

	sf::Texture m_carOptions[3];
	sf::Sprite m_cars[3];
};
#endif // !GARAGE
