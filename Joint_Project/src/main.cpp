/// <summary>
/// @mainpage Joint Project -> A game that features 
/// @Authors D.J. O'Leary, Peter Daly, Jack O'Kelly and John O'Grady
/// @Version 1.0
/// @brief
///
/// 
/// Date / Start time -> End time / length of time.
/// 06-03-17 / 09:00 -> 11:00 / 2hr.
/// 06-03-17 / 13:00 -> 
/// 
/// Total Time Taken: ???
/// </summary> 

#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#pragma comment(lib,"libyaml-cppmdd") 
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