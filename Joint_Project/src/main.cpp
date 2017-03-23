/// <summary>
/// @mainpage Joint Project -> A 2d Racing Game featuring upgrades, maps, and bus selection
/// @Authors D.J. O'Leary, Peter Daly, Jack O'Kelly and John O'Grady
/// @Version 1.0
/// @brief We were tasked with making a 2d racing game in 3 weeks using what assets we were given.
/// We needed to include multiple maps, multiple upgradeable vehicles, and AI that would race against the player.
/// Break Point Racing is a challenging game that is fun to play, and allows each player to have their own game,
/// As they get to choose which vehicle they race with (as each vehicle specialises in different stats; Brakes, Handling, and Acceleration),
/// What upgrades they choose with their winnings, and what map they want to race the AI in.
/// 
/// 
/// Total Time Taken: 560hrs between 4 people.

/// </summary> 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#pragma comment(lib,"libyaml-cppmdd") 
#pragma comment(lib, "sfeMovie-d.lib")
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#pragma comment(lib, "sfeMovie.lib")
#endif 			

#include <iostream>
#include "SFML\Graphics.hpp"
#include "Game.h"

int main()
{
	sf::Font font;
	sf::Font titleFont;

	if (!font.loadFromFile(".\\resources\\fonts\\joystix.ttf"))	// Checks to make sure font is correct
	{
		std::cout << "Problem loading font file!" << std::endl;
	}
	if (!titleFont.loadFromFile(".\\resources\\fonts\\Orena.ttf"))	// Checks to make sure font is correct
	{
		std::cout << "Problem loading font file!" << std::endl;
	}

	Game game(font, titleFont);
	game.run();

	return 0;
}