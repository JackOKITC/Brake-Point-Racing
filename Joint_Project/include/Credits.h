#ifndef CREDITS_H
#define CREDITS_H

/// <summary>
/// Author: Peter Daly, Jack O'Kelly
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
	/// <summary>
	/// Constructor that takes 2 arguments, them being:
	/// font which stores the font that will be used to draw all text to the screen,
	/// gameState is a pointer to the object in game.cpp.
	/// </summary>
	/// <param name="font"></param>
	/// <param name="gameState"></param>
	Credits(sf::Font & font, GameState *gameState);
	~Credits();	// De-constructor for the credits screen.

	/// <summary>
	/// Takes 2 arguments, them being:
	/// controller is a reference to the object in game.cpp,
	/// dt is the time between updates.
	/// 
	/// This is also where any other method that needs to be called frequently is called.
	/// </summary>
	/// <param name="controller"></param>
	/// <param name="dt"></param>
	void update(Xbox360Controller & controller, sf::Time dt);
	void render(sf::RenderWindow & window);
	
private:
	sfe::Movie m_movie;	// The movie variable which stores our .mov
	sf::Font m_font;	// Stores the font that is used to draw all text to the game window.
	GameState * m_gameState;	// Pointer to the GameState object in game.cpp.
	Label * m_label;	// Pointer to a label.
	Xbox360Controller * m_controller;	// Pointer to the controller object.
	std::string m_string;	// Stores text to be displayed.
};

#endif //!CREDITS_H