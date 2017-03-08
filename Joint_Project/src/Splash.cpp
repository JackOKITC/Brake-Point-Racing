#include "Splash.h"

Splash::Splash(GameState *gameState, sf::Font font)
	: m_font(font)
{
	// Loading in the background texture
	if (!m_backgroundTex.loadFromFile(".//resources//images//UI//bg.jpg"))
	{
		std::cout << "Problem loading Texture for splash screen";
	}

	m_backgroundSprite.setTexture(m_backgroundTex);
	m_backgroundSprite.setScale(0.4f, 0.575f); // Setting the scale of the background sprite
	m_backgroundSprite.setOrigin(m_backgroundTex.getSize().x / 2, m_backgroundTex.getSize().y / 2); // Setting the background sprite's origin
	m_backgroundSprite.setPosition(450, 300); // Setting the background sprite's position
	m_backgroundSprite.setRotation(90); // rotating the background sprite 90 degrees to make it horizontal

	// The Title Screen text
	m_text.setFont(m_font);
	m_text.setColor(sf::Color(246, 169, 39));
	m_text.setPosition(166,100);
	m_text.setStyle(sf::Text::Bold);
	m_text.setScale(1.5f, 1.5f);

	// The "Press Start" text
	m_startText.setFont(m_font);
	m_startText.setColor(sf::Color::White);
	m_startText.setPosition(325, 450);
	m_startText.setScale(1, 1);

	// The License text
	m_licenseText.setFont(m_font);
	m_licenseText.setColor(sf::Color::White);
	m_licenseText.setPosition(670, 150);
	m_licenseText.setScale(0.5f, 0.5f);

	/// <summary>
	/// These set the strings for all text files
	/// </summary>
	/// <param name="font"></param>
	m_text.setString("BRAKE POINT RACING");

	m_startText.setString("PRESS START");
	
	m_licenseText.setString("By Team J");

	m_state = gameState;
}

Splash::~Splash()
{
}

void Splash::update(Xbox360Controller * controller, sf::Time dt)
{
	m_controller = controller;

	// Begins transition if "Start" is pressed
	if (m_controller->m_currentState.Start)
	{
		m_transitionToNext = true;
	}

	if (m_transitionToNext)
	{
		sf::Color color = m_backgroundSprite.getColor();

		m_backgroundSprite.setRotation(m_backgroundSprite.getRotation() + 2); //Rotates the sprite
		m_backgroundSprite.scale(.999, .999); // Scales the sprite down


		currentTime += TIME_PER_UPDATE;

		// Changes to the menu screen after 3 seconds of transitioning
		if (currentTime.asSeconds() > 3)
		{
			*m_state = GameState::MENU_STATE;
			m_transitionToNext = false;
		}
	}

}

void Splash::render(sf::RenderWindow & window)
{
	window.draw(m_backgroundSprite);
	
	// Drawing the text objects only if the screen is not transitioning
	if (!m_transitionToNext)
	{
		window.draw(m_text);
		window.draw(m_startText);
		window.draw(m_licenseText);
	}	
}