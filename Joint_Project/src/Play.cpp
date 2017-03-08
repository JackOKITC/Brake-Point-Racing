#include "Play.h"

Play::Play()
{
}

Play::~Play()
{
}

void Play::update()
{
}

void Play::render()
{
}

GameState Play::changeGameState()
{
	if (m_changeState == GameState::MENU_STATE)
	{
		return m_changeState;
	}
}
