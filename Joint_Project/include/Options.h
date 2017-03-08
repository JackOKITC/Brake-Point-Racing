#ifndef OPTIONS_H
#define OPTIONS_H

#include <SFML\Graphics.hpp>
#include "GameState.h"

class Options
{
public:
	Options();
	~Options();

	void update();
	void render(sf::RenderWindow & window);

	GameState changeGameState();

private:
	GameState m_changeState;
};
#endif // !OPTIONS_H
