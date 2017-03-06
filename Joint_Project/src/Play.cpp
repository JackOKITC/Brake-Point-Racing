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

bool Play::changeGameState()
{
	if (m_changeState)
	{
		return true;
	}
	else
	{
		return false;
	}
}
