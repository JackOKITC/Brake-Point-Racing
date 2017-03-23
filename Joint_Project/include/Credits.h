#ifndef CREDITS_H
#define CREDITS_H

/// <summary>
/// Author: Peter Daly & Jack O'Kelly
/// Version: 1.0
/// Created: 23/03/2017
/// </summary>

#include "Widget.h"
#include "Xbox360Controller.h"
#include <Sfe\Movie.hpp>
#include <Sfe\StreamSelection.hpp>
#include <Sfe\Visibility.hpp>
#include "GameState.h"
#include "ResourceManager.h"

class Credits
{
public:
	Credits(sf::Font & font, GameState *gameState);
	~Credits();

	void render(sf::RenderWindow & window);
	void update(Xbox360Controller & controller, sf::Time dt);
private:
	sfe::Movie m_movie;	// the movie variable which stores our .mov
	sf::Font m_font;
	GameState * m_gameState;
	Label * m_label;
	Xbox360Controller * m_controller;
	std::string m_string;
};

#endif //!CREDITS_H