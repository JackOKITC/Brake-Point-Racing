#ifndef SPLASH_H
#define SPLASH_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include "Xbox360Controller.h"

class Splash
{
public:
	Splash();
	~Splash();

	void update(Xbox360Controller * yeah);
	void render(sf::RenderWindow & window);

	bool changeGameState();

private:
	bool m_changeState;

	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

	Xbox360Controller *m_controller;
};
#endif // !SPLASH_H
