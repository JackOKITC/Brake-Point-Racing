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

GameState Options::changeGameState()
{
	if (m_changeState == GameState::MENU_STATE)
	{
		return m_changeState;
	}
}
