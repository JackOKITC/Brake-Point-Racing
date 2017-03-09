#include "Menu.h"

Menu::Menu(sf::Font & font, GameState *gameState) :
	m_font(font)
{
	m_gameState = gameState;
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		m_buttons[i] = new Button(&m_strings[i], &sf::Vector2f(450, 200 + (i * 100)), &m_font);
		m_buttons[i]->loseFocus();
	}

	m_currentBtn = 0;
	m_buttons[m_currentBtn]->getFocus();
}

Menu::~Menu()
{
}

void Menu::update(GamePadState m_state, Xbox360Controller & m_controller)
{
	checkButtonSelected(m_state, m_controller);
	selectedButton(m_state,m_controller);
}

void Menu::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::Black);
	for (int i = 0; i < BUTTON_COUNT; i++)
	{
		m_buttons[i]->render(window);
	}
}




// Function to check which button is selected
void Menu::checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller)
{
	// if Down toggled
	if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
	{
		m_buttons[m_currentBtn]->loseFocus(); // currently selected button loses focus, unhighlighted
		m_currentBtn = m_currentBtn + 1; // currentBtn selected incremented
		if (m_currentBtn > BUTTON_COUNT - 1)
		{
			m_currentBtn = m_currentBtn - 1; // safe guard to stop out of bound behaviour
		}

		m_buttons[m_currentBtn]->getFocus(); // newly seleted button highlighted
		m_buttonSelected = (button)m_currentBtn; // enum for buttons set to current int value of current button
	}

	// if Up toggled, same behaviour as above except the counter is decremented
	if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
	{
		m_buttons[m_currentBtn]->loseFocus();
		m_currentBtn = m_currentBtn - 1;
		if (m_currentBtn < 0)
		{
			m_currentBtn = 0;
		}

		m_buttons[m_currentBtn]->getFocus();
		m_buttonSelected = (button)m_currentBtn;
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
