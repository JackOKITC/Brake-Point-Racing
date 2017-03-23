#include "PreRace.h"

PreRace::PreRace(sf::Font font, GameState *gameState, Player *player) :
	m_font(font),
	m_gameState(gameState)
{
	m_player = player;

	m_rightButton[0] = new Button(&m_rightString, &sf::Vector2f(750, 200), &m_font);
	m_leftButton[0] = new Button(&m_leftString, &sf::Vector2f(150, 200), &m_font);
	m_rightButton[1] = new Button(&m_rightString, &sf::Vector2f(750, 350), &m_font);
	m_leftButton[1] = new Button(&m_leftString, &sf::Vector2f(150, 350), &m_font);
	m_backButton = new Button(&m_backString, &sf::Vector2f(450, 550), &m_font);
	m_raceButton = new Button(&m_raceString, &sf::Vector2f(450, 450), &m_font);

	m_grassLabel = new Label(&m_grassString, &m_font, &sf::Vector2f(450, 200), 20, sf::Color(255, 205, 0));
	m_icyLabel = new Label(&m_icyString, &m_font, &sf::Vector2f(450, 200), 20, sf::Color(255, 205, 0));
	m_carLabel = new Label(&m_carTypes[0], &m_font, &sf::Vector2f(450, 350), 20, sf::Color(255, 205, 0));

	widgets[0] = m_rightButton[0];
	widgets[1] = m_leftButton[0];
	widgets[2] = m_rightButton[1];
	widgets[3] = m_leftButton[1];
	widgets[4] = m_backButton;
	widgets[5] = m_raceButton;
	widgets[6] = m_carLabel;
	widgets[7] = m_grassLabel;
	widgets[8] = m_icyLabel;

	widgets[0]->loseFocus();
	widgets[1]->loseFocus();
	widgets[2]->loseFocus();
	widgets[3]->loseFocus();
	widgets[4]->loseFocus();
	widgets[5]->getFocus();

	m_currentCar = 0;
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
		widgets[7]->render(window);
	}
	if (m_whichLabel)
	{
		widgets[8]->render(window);
	}
}

// Function to check which button is selected
void PreRace::checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller)
{
	switch (m_buttonSelected)
	{
	case raceSelection::MapNext:
		m_rightButton[0]->getFocus();
		m_leftButton[0]->loseFocus();
		m_rightButton[1]->loseFocus();
		m_leftButton[1]->loseFocus();
		m_backButton->loseFocus();
		m_raceButton->loseFocus();
		if ((m_state.dpadLeft && !m_controller.m_previousState.dpadLeft) || (m_state.LeftThumbStick.x < -50 && m_controller.m_previousState.LeftThumbStick.x > -50))
		{
			m_buttonSelected = raceSelection::MapPrev;
		}
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = raceSelection::CarNext;
		}
		break;
	case raceSelection::MapPrev:
		m_rightButton[0]->loseFocus();
		m_leftButton[0]->getFocus();
		m_rightButton[1]->loseFocus();
		m_leftButton[1]->loseFocus();
		m_backButton->loseFocus();
		m_raceButton->loseFocus();
		if ((m_state.dpadRight && !m_controller.m_previousState.dpadRight) || (m_state.LeftThumbStick.x > 50 && m_controller.m_previousState.LeftThumbStick.x < 50))
		{
			m_buttonSelected = raceSelection::MapNext;
		}

		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = raceSelection::CarPrev;
		}

		break;
	case raceSelection::CarPrev:
		m_rightButton[0]->loseFocus();
		m_leftButton[0]->loseFocus();
		m_rightButton[1]->loseFocus();
		m_leftButton[1]->getFocus();
		m_backButton->loseFocus();
		m_raceButton->loseFocus();

		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = raceSelection::MapNext;
		}

		if ((m_state.dpadRight && !m_controller.m_previousState.dpadRight) || (m_state.LeftThumbStick.x > 50 && m_controller.m_previousState.LeftThumbStick.x < 50))
		{
			m_buttonSelected = raceSelection::CarNext;
		}

		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = raceSelection::Race;
		}
		break;
	case raceSelection::CarNext:
		m_rightButton[0]->loseFocus();
		m_leftButton[0]->loseFocus();
		m_rightButton[1]->getFocus();
		m_leftButton[1]->loseFocus();
		m_backButton->loseFocus();
		m_raceButton->loseFocus();

		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = raceSelection::MapNext;
		}

		if ((m_state.dpadLeft && !m_controller.m_previousState.dpadLeft) || (m_state.LeftThumbStick.x < -50 && m_controller.m_previousState.LeftThumbStick.x > -50))
		{
			m_buttonSelected = raceSelection::CarPrev;
		}

		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = raceSelection::Race;
		}
		break;
	case raceSelection::Race:
		m_rightButton[0]->loseFocus();
		m_leftButton[0]->loseFocus();
		m_rightButton[1]->loseFocus();
		m_leftButton[1]->loseFocus();
		m_backButton->loseFocus();
		m_raceButton->getFocus();

		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = raceSelection::MapPrev;
		}

		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = raceSelection::Back;
		}
		break;

	case raceSelection::Back:
		m_rightButton[0]->loseFocus();
		m_leftButton[0]->loseFocus();
		m_rightButton[1]->loseFocus();
		m_leftButton[1]->loseFocus();
		m_backButton->getFocus();
		m_raceButton->loseFocus();
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = raceSelection::Race;
		}

		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = raceSelection::MapPrev;
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
	case raceSelection::MapPrev:	// The mute button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			if (m_whichLabel)
				m_whichLabel = false;
			else
				m_whichLabel = true;
		}
		break;

	case raceSelection::MapNext:	// The mute button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			if (m_whichLabel)
				m_whichLabel = false;
			else
				m_whichLabel = true;
		}
		break;
	case raceSelection::CarPrev:	// The back button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			if (m_currentCar >= 1)
			{
				m_currentCar--;
				m_carLabel->updateText(m_carTypes[m_currentCar]);
				m_player->m_currentCar = m_currentCar;
			}
		}
		break;
	case raceSelection::CarNext:	// The back button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			if (m_currentCar != 2)
			{
				m_currentCar++;
				m_carLabel->updateText(m_carTypes[m_currentCar]);
				m_player->m_currentCar = m_currentCar;
			}
		}
		break;
	case raceSelection::Race:	// The back button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			*m_gameState = GameState::PLAY_STATE;

		}
		break;
	case raceSelection::Back:	// The back button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			*m_gameState = GameState::MENU_STATE;

		}
		break;
	default:
		break;
	}
}