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

void Options::render()
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
