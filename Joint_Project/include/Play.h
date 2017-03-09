#ifndef PLAY_H
#define PLAY_H

#include "GameState.h"
#include "Xbox360Controller.h"
#include <iostream>
#include "Car.h"

class Play
{
public:
	Play(GameState *gameState);
	~Play();

	void update(Xbox360Controller & controller, double dt);
	void render(sf::RenderWindow & window);

private:
	GameState *m_state;

	sf::Texture m_backgroundTex;
	sf::Sprite m_backgroundSprite;

	Xbox360Controller * m_controller;
	Car * car;
};
#endif // !PLAY_H
