#ifndef PRERACE_H
#define PRERACE_H

#include <SFML\Graphics.hpp>
#include "GameState.h"
#include "Widget.h"
#include "ResourceManager.h"

class PreRace
{
public: 
	PreRace();
	~PreRace();

	void update();
	void render(sf::RenderWindow & window);
private: 

};
#endif // !PRERACE_H

