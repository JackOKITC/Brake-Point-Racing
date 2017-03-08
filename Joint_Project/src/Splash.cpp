#include "Splash.h"

Splash::Splash(sf::Font font)
	: m_font(font)
	, m_ss("Brake Point Racing")
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

	m_text.setFont(m_font);
	m_text.setColor(sf::Color(39, 149, 196));
	m_text.setPosition(166,100);
	m_text.setStyle(sf::Text::Bold);
	m_text.setScale(1.5f, 1.5f);

	m_outline.setFont(m_font);
	m_outline.setColor(sf::Color(0,0,0));
	m_outline.setPosition(165, 99);
	m_outline.setStyle(sf::Text::Bold);
	m_outline.setScale(1.5f, 1.5f);

	m_text.setString("BRAKE POINT RACING");
	m_outline.setString("BRAKE POINT RACING");
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
	window.draw(m_outline);
	window.draw(m_text);
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
