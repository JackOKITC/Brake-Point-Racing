#include "Options.h"

Options::Options()
{
}

Options::~Options()
{
}

void Options::update()
{
}

void Options::render(sf::RenderWindow & window)
{
}

bool Options::changeGameState()
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
