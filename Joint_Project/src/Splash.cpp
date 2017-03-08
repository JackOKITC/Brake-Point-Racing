#include "Splash.h"

Splash::Splash()
{
	if (!m_backgroundTex.loadFromFile(".//resources//images//UI//bg.jpg"))
	{
		std::cout << "Problem loading Texture for splash screen";
	}
	m_backgroundSprite.setTexture(m_backgroundTex);
	m_backgroundSprite.setScale(0.4f, 0.4f);
	m_backgroundSprite.setOrigin(m_backgroundTex.getSize().x / 2, m_backgroundTex.getSize().y / 2);
	m_backgroundSprite.setPosition(450, 300);
	m_changeState = false;
}

Splash::~Splash()
{
}

void Splash::update(Xbox360Controller * controller, sf::Time dt)
{
	m_controller = controller;


	if (m_controller->m_currentState.Start)
	{
		m_transitionToNext = true;
	}

	if (m_transitionToNext)
	{
		sf::Color color = m_backgroundSprite.getColor();
		m_backgroundSprite.setRotation(m_backgroundSprite.getRotation() + 2);
		m_backgroundSprite.scale(.999, .999);

		

		currentTime += TIME_PER_UPDATE;

		if (currentTime.asSeconds() > 3)
		{
			m_changeState = true;
			changeGameState();
			m_transitionToNext = false;
		}
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
