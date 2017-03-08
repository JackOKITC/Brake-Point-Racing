#ifndef SPLASH_H
#define SPLASH_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Xbox360Controller.h"
#include "GameState.h"
#include <sstream>

class Splash
{
	const sf::Time TIME_PER_UPDATE = sf::microseconds(1000);

public:
	Splash(sf::Font font);
	~Splash();

	void update(Xbox360Controller * controller, sf::Time dt);
	void render(sf::RenderWindow & window);

	bool changeGameState();

private:

	bool m_changeState;
	bool m_transitionToNext = false;
	sf::Time currentTime;

	sf::Font m_font;
	sf::Text m_text;
	sf::Text m_outline;
	std::stringstream m_ss;

	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

	Xbox360Controller * m_controller;
};
#endif // !SPLASH_H
