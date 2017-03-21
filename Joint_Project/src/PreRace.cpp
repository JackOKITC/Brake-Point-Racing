#include "PreRace.h"

PreRace::PreRace(sf::Font font, GameState *gameState) :
	m_font(font),
	m_gameState(gameState)
{
	m_rightButton = new Button(&m_rightString, &sf::Vector2f(750, 200), &m_font);
	m_leftButton = new Button(&m_leftString, &sf::Vector2f(150, 200), &m_font);
	m_backButton = new Button(&m_backString, &sf::Vector2f(450, 500), &m_font);
	m_raceButton = new Button(&m_raceString, &sf::Vector2f(450, 350), &m_font);
	m_grassLabel = new Label(&m_grassString, &m_font, &sf::Vector2f(450, 200), 32, sf::Color(255, 205, 0));
	m_icyLabel = new Label(&m_icyString, &m_font, &sf::Vector2f(450, 200), 32, sf::Color(255, 205, 0));

	widgets[0] = m_rightButton;
	widgets[1] = m_leftButton;
	widgets[2] = m_backButton;
	widgets[3] = m_raceButton;
	widgets[4] = m_grassLabel;
	widgets[5] = m_icyLabel;

	widgets[0]->loseFocus();
	widgets[1]->loseFocus();
	widgets[2]->loseFocus();
	widgets[3]->getFocus();

	m_whichLabel = false;
}

PreRace::~PreRace() {}

void PreRace::update(GamePadState m_state, Xbox360Controller & m_controller)
{
	checkButtonSelected(m_state, m_controller);
	selectedButton(m_state, m_controller);
}

void PreRace::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(30, 50, 90));
	for (int i = 0; i < WIDGET_COUNT; i++)
	{
		widgets[i]->render(window);
	}
	if (!m_whichLabel)
	{
		widgets[4]->render(window);
	}
	if (m_whichLabel)
	{
		widgets[5]->render(window);
	}
}

// Function to check which button is selected
void PreRace::checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller)
{
	switch (m_buttonSelected)
	{
	case raceSelection::Option1:
		m_rightButton->getFocus();
		m_leftButton->loseFocus();
		m_backButton->loseFocus();
		m_raceButton->loseFocus();
		if ((m_state.dpadLeft && !m_controller.m_previousState.dpadLeft) || (m_state.LeftThumbStick.x < -50 && m_controller.m_previousState.LeftThumbStick.x > -50))
		{
			m_buttonSelected = raceSelection::Option2;
		}
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = raceSelection::Option4;
		}
		break;
	case raceSelection::Option2:
		m_rightButton->loseFocus();
		m_leftButton->getFocus();
		m_backButton->loseFocus();
		m_raceButton->loseFocus();
		if ((m_state.dpadRight && !m_controller.m_previousState.dpadRight) || (m_state.LeftThumbStick.x > 50 && m_controller.m_previousState.LeftThumbStick.x < 50))
		{
			m_buttonSelected = raceSelection::Option1;
		}

		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = raceSelection::Option4;
		}

		break;
	case raceSelection::Option3:
		m_rightButton->loseFocus();
		m_leftButton->loseFocus();
		m_backButton->getFocus();
		m_raceButton->loseFocus();

		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = raceSelection::Option4;
		}
		break;
	case raceSelection::Option4:
		m_rightButton->loseFocus();
		m_leftButton->loseFocus();
		m_backButton->loseFocus();
		m_raceButton->getFocus();

		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = raceSelection::Option1;
		}

		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = raceSelection::Option3;
		}
		break;
	default:
		break;
	}


}

// Function to check if the selected button has been pressed
void PreRace::selectedButton(GamePadState m_state, Xbox360Controller m_controller)
{
	switch (m_buttonSelected) // Switch statement for the buttons
	{
	case raceSelection::Option1:	// The mute button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			if (m_whichLabel)
				m_whichLabel = false;
			else
				m_whichLabel = true;
		}
		break;

	case raceSelection::Option2:	// The mute button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			if (m_whichLabel)
				m_whichLabel = false;
			else
				m_whichLabel = true;
		}
		break;
	case raceSelection::Option3:	// The back button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			*m_gameState = GameState::MENU_STATE;
		}
		break;
	case raceSelection::Option4:	// The back button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			*m_gameState = GameState::PLAY_STATE;

		}
		break;
	default:
		break;
	}
}