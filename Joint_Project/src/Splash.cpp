#include "Splash.h"

Splash::Splash(GameState *gameState, sf::Font font)
	: m_font(font)
{
	m_backgroundTex = ResourceManager::instance().m_holder["SplashBG"];
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
	m_startText.setPosition(325, 450);
	m_startText.setScale(1, 1);

	// The License text
	m_licenseText.setFont(m_font);
	m_licenseText.setColor(sf::Color::White);
	m_licenseText.setPosition(670, 150);
	m_licenseText.setScale(0.5f, 0.5f);

	alpha = 255;	// an alpha variable to allow the alpha value to be incremented/decremented in the loop
	b = 255;	// a 'b' varabile from RGB to allow the B value to be incremented/decremented in the loop

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
		m_startPressed = true;							
	}
	else if (!m_startPressed)
	{
		m_startText.setColor(sf::Color(255, 255, b));

		// highlights the text yellow and scales it slightly up.
		if (m_highlight)
		{		
			currentTime += TIME_PER_UPDATE;
			m_startText.scale(1.0002, 1.0002);
			m_startText.move(-0.02, 0);	// this is so the text doesn't only scale out to the right
			
			// decrement b if it is not 20
			if (b != 20)
			{
				b--;
			}
			
			// changes highlight to false and resets the clock
			if (currentTime.asSeconds() >= 0.5)
			{
				m_highlight = false;
				currentTime = sf::Time::Zero;
			}
		}

		// "unhighlights" the text and changes the text to white
		if (!m_highlight)
		{
			currentTime += TIME_PER_UPDATE;
			m_startText.scale(0.9998, 0.9998);
			m_startText.move(0.02, 0);	// again so the text doesn't scale too far out to the left
			
			if (b != 255)
			{
				b++;
			}

			// changes highlight to false and resets the clock, so it can keep looping the colour change and scaling
			if (currentTime.asSeconds() >= 0.5)
			{
				m_highlight = true;
				currentTime = sf::Time::Zero;
			}
		}

	}

	if (m_startPressed)
	{

		m_licenseText.move(1, 0);
		m_text.move(-2, 0);
		m_startText.move(0, 1);

		currentTime += TIME_PER_UPDATE;

		if (currentTime.asSeconds() >= 0.75)
		{
			currentTime = sf::Time::Zero;
			m_transitionToNext = true;
		}
	}

	if (m_transitionToNext)
	{	
		currentTime += TIME_PER_UPDATE;
		
		if (currentTime.asSeconds() > 0 && alpha != 0)
		{
			m_backgroundSprite.setColor(sf::Color(255, 255, 255, alpha));
			alpha--;
		}
		else
		{
			*m_state = GameState::MENU_STATE;
			m_transitionToNext = false;
		}
	}
}

void Splash::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);
	window.draw(m_backgroundSprite);
	
	// Drawing the text objects only if the screen is not transitioning
	if (!m_transitionToNext)
	{
		window.draw(m_text);
		window.draw(m_startText);
		window.draw(m_licenseText);
	}	
}