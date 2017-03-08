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


private:
	GameState *m_gameState;
};
#endif // !OPTIONS_H
