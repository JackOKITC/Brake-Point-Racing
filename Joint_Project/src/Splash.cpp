#include "Splash.h"

Splash::Splash()
{
	if (!m_backgroundTex.loadFromFile(".//resources//images//trees//2.png"))
	{
		std::cout << "Problem loading Texture for splash screen";
	}
	m_backgroundSprite.setTexture(m_backgroundTex);
	m_changeState = false;
}

Splash::~Splash()
{
}

void Splash::update(Xbox360Controller * yeah)
{
	m_controller = yeah;
	if (m_controller->m_currentState.Start)
	{
		m_changeState = true;
		changeGameState();
	}


}

void Splash::render(sf::RenderWindow & window)
{
	window.draw(m_backgroundSprite);
}

bool Splash::changeGameState()
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
