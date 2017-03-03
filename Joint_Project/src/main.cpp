/// <summary>
/// @mainpage Connect Lads -> A game that features a UI elements and has connect 4 like gameplay that revolves around the usage of buttons.
/// @Authors D.J. O'Leary and Peter Daly
/// @Version 1.0
/// @brief Connect 4 like game.
///
/// 
/// Date/ Start time -> End time / length of time.
/// 23/01/17 / 17:45 -> 19:00 / 1hr 15mins.
/// 
/// Total Time Taken: ???
/// </summary> 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 

#include <iostream>
#include "SFML\Graphics.hpp"
#include "Game.h"

int main()
{
	sf::Font font;

	if (!font.loadFromFile(".\\resources\\fonts\\arial.ttf"))	//Checks to make sure font is correct
	{
		std::cout << "Problem loading font file!" << std::endl;
	}

	Game game(font);
	game.run();

	return 0;
}