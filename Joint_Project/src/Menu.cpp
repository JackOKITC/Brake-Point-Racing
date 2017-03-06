#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::update()
{
}

void Menu::render()
{
}

bool Menu::changeGameState()
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
