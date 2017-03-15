#ifndef SPLASH_H
#define SPLASH_H

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
	// Initialising the TIME_PER_UPDATE variable for the splash transition
	const sf::Time TIME_PER_UPDATE = sf::microseconds(1000);

public:

	Splash(GameState *gameState, sf::Font font);
	~Splash();

	void update(Xbox360Controller * controller, sf::Time dt);
	void render(sf::RenderWindow & window);

private:
	GameState *m_state;
	
	bool m_transitionToNext = false;
	bool m_startPressed = false;
	bool m_highlight = true;
	
	int alpha;
	int b;

	int charSize;
	
	sf::Time currentTime;

	sf::Font m_font;

	// Text variables
	sf::Text m_text;
	sf::Text m_startText;
	sf::Text m_licenseText;

	// Background variables
	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

	Xbox360Controller * m_controller;

};
#endif // !SPLASH_H
