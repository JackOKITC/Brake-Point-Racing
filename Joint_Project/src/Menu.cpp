#include "Menu.h"

Menu::Menu(sf::Font & font, GameState *gameState) :
	m_font(font)
	, TIME_PER_UPDATE(sf::microseconds(1450))
{
	m_gameState = gameState;

#pragma region Convex Lines

	m_raceLine.setPointCount(4);
	m_raceLine.setPoint(0, sf::Vector2f(144.5, 140));
	m_raceLine.setPoint(1, sf::Vector2f(243, 105));
	m_raceLine.setPoint(2, sf::Vector2f(247.6, 115));
	m_raceLine.setPoint(3, sf::Vector2f(153, 160));
	m_raceLine.setFillColor(sf::Color(m_unselect));
	
	m_garLine.setPointCount(4);
	m_garLine.setPoint(0, sf::Vector2f(175.5, 240));
	m_garLine.setPoint(1, sf::Vector2f(278.5, 225));
	m_garLine.setPoint(2, sf::Vector2f(280.75, 235));
	m_garLine.setPoint(3, sf::Vector2f(179, 260));
	m_garLine.setFillColor(sf::Color(m_unselect));

	m_optLine.setPointCount(4);
	m_optLine.setPoint(0, sf::Vector2f(179, 340));
	m_optLine.setPoint(1, sf::Vector2f(282.5, 350));
	m_optLine.setPoint(2, sf::Vector2f(280.5, 360));
	m_optLine.setPoint(3, sf::Vector2f(176, 360));
	m_optLine.setFillColor(sf::Color(m_unselect));
	
	m_exitLine.setPointCount(4);
	m_exitLine.setPoint(0, sf::Vector2f(155.5, 438));
	m_exitLine.setPoint(1, sf::Vector2f(252, 475));
	m_exitLine.setPoint(2, sf::Vector2f(248, 485));
	m_exitLine.setPoint(3, sf::Vector2f(147, 458));
	m_exitLine.setFillColor(sf::Color(m_unselect));

#pragma endregion

	m_backgroundTex = ResourceManager::instance().m_holder["MenuBG"];

	m_backgroundSprite.setTexture(m_backgroundTex);
	m_backgroundSprite.setPosition(-1400, -200);

	m_timeStop = false;
	m_transitionStop = false;

	for (int i = 0; i < LABEL_COUNT; i++)
	{
		if (i < 1 || i > 2)
		{
			m_labels[i] = new Label(&m_strings[i], &m_font, &sf::Vector2f(300, 100 + (i * 130)));
		}
		else
		{
			m_labels[i] = new Label(&m_strings[i], &m_font, &sf::Vector2f(355, 100 + (i * 130)));
		}
		
		m_labels[i]->loseFocus();
	}

	m_currentLab = 0;
	m_labels[m_currentLab]->getFocus();
}

Menu::~Menu()
{
}

void Menu::update(GamePadState m_state, Xbox360Controller & m_controller, sf::Time deltaTime)
{
	if (m_transitionStop)
	{
		checkButtonSelected(m_state, m_controller);
		selectedButton(m_state, m_controller);
	}

	if (!m_timeStop)
	{
		deltaTime.Zero;
		m_timeStop = true;
	}

	if (m_time.asSeconds() <= 2.0)
	{
		if (m_backgroundSprite.getPosition().x < -700)
		{
			m_backgroundSprite.move(0.6, 0);
		}
		
		m_time += TIME_PER_UPDATE;
	}
	else
	{
		m_transitionStop = true;
	}
}

void Menu::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(30, 50, 90));
	window.draw(m_backgroundSprite);
	
	
	
	if (m_transitionStop)
	{
		window.draw(m_raceLine);
		window.draw(m_garLine);
		window.draw(m_optLine);
		window.draw(m_exitLine);
		for (int i = 0; i < LABEL_COUNT; i++)
		{
			m_labels[i]->render(window);

		}
	}
}


// Function to check which button is selected
void Menu::checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller)
{
	switch (m_currentLab)
	{
	case 0:
		m_raceLine.setFillColor(sf::Color(m_select));
		m_garLine.setFillColor(sf::Color(m_unselect));
		m_optLine.setFillColor(sf::Color(m_unselect));
		m_exitLine.setFillColor(sf::Color(m_unselect));
		
		break;
	case 1:
		m_raceLine.setFillColor(sf::Color(m_unselect));
		m_garLine.setFillColor(sf::Color(m_select));
		m_optLine.setFillColor(sf::Color(m_unselect));
		m_exitLine.setFillColor(sf::Color(m_unselect));
		break;
	case 2:
		m_raceLine.setFillColor(sf::Color(m_unselect));
		m_garLine.setFillColor(sf::Color(m_unselect));
		m_optLine.setFillColor(sf::Color(m_select));
		m_exitLine.setFillColor(sf::Color(m_unselect));
		break;
	case 3:
		m_raceLine.setFillColor(sf::Color(m_unselect));
		m_garLine.setFillColor(sf::Color(m_unselect));
		m_optLine.setFillColor(sf::Color(m_unselect));
		m_exitLine.setFillColor(sf::Color(m_select));
		break;
	}
	// if Down toggled
	if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
	{
		m_labels[m_currentLab]->loseFocus(); // currently selected button loses focus, unhighlighted
		m_currentLab = m_currentLab + 1; // currentBtn selected incremented
		if (m_currentLab > LABEL_COUNT - 1)
		{
			m_currentLab = m_currentLab - 1; // safe guard to stop out of bound behaviour
		}

		m_labels[m_currentLab]->getFocus(); // newly seleted button highlighted
		m_buttonSelected = (button)m_currentLab; // enum for buttons set to current int value of current button
	}

	// if Up toggled, same behaviour as above except the counter is decremented
	if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
	{
		m_labels[m_currentLab]->loseFocus();
		m_currentLab = m_currentLab - 1;
		if (m_currentLab < 0)
		{
			m_currentLab = 0;
		}

		m_labels[m_currentLab]->getFocus();
		m_buttonSelected = (button)m_currentLab;
	}
}

// Function to check if the selected button has been pressed
void Menu::selectedButton(GamePadState m_gamePadState, Xbox360Controller m_controller)
{
	switch (m_buttonSelected) // Switch statement for the buttons
	{
	case button::Play:	// The play button 
		if (m_gamePadState.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			*m_gameState = GameState::PLAY_STATE;
		}
		break;
	case button::Garage:
		if (m_gamePadState.A && !m_controller.m_previousState.A)
		{
			*m_gameState = GameState::UPGRADE_STATE;
		}
		  break;
	case button::Options:	// The options button 
		if (m_gamePadState.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			*m_gameState = GameState::OPTIONS_STATE;
		}
		break;
	case button::Exit:	// The exit button 
		if (m_gamePadState.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			exit(0);	// Exits the game
		}
		break;
	default:
		break;
	}
}