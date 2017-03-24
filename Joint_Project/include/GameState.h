#ifndef GAME_STATE_H
#define GAME_STATE_H

/// <summary>
/// Author: D.J. O'Leary
/// Version: 1.0
/// Created: 08/03/2017
/// </summary>

enum class GameState
{
	SPLASH_STATE,	// Enum that represents Splash.cpp
	MENU_STATE,		// Enum that represents Menu.cpp
	PLAY_STATE,		// Enum that represents Play.cpp
	UPGRADE_STATE,	// Enum that represents Garage.cpp
	OPTIONS_STATE,	// Enum that represents Options.cpp
	CREDITS_STATE,	// Enum that represents Credits.cpp
	PRERACE_STATE,	// Enum that represents PreRace.cpp
	END_STATE		// Enum that represents EndScreen.cpp
};
#endif // !GAME_STATE_H