#include "Menu.h"

Menu::Menu(sf::Font & font) :
	m_font(font)
{

	

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
	for (int i = 0; i < 3; i++)
	{
		m_buttons[i]->render(window);
	}
}

GameState Menu::changeGameState()
{
	if (m_changeState == GameState::PLAY_STATE)
	{
		return m_changeState;
	}
	else if (m_changeState == GameState::OPTIONS_STATE)
	{
		return m_changeState;
	}
}

// Function to check which button is selected
void Menu::checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller)
{
	switch (m_buttonSelected)	// Switch statement for every button
	{

	case button::Play:	// The play button

						// Sets the play button to be highlighted and the other buttons to be not
		m_buttons[0]->getFocus();
		m_buttons[1]->loseFocus();
		m_buttons[2]->loseFocus();

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = button::Options;	// Switches to the options button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = button::Exit;	// Switches to the exit button
		}
		break;
	case button::Options: // The options button 

						  // Sets the options button to be highlighted and the other buttons to be not
		m_buttons[0]->loseFocus();
		m_buttons[1]->getFocus();
		m_buttons[2]->loseFocus();

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = button::Exit;	// Switches to the exit button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = button::Play;	// Switches to the play button
		}
		break;
	case button::Exit:	// The exit button

						// Sets the exit button to be highlighted and the other buttons to be not
		m_buttons[0]->loseFocus();
		m_buttons[1]->loseFocus();
		m_buttons[2]->getFocus();

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = button::Play;	// Switches to the play button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = button::Options;	// Switches to the options button
		}
		break;
	default:
		break;
	}
}

// Function to check if the selected button has been pressed
void Menu::selectedButton(GamePadState m_state, Xbox360Controller m_controller)
{
	switch (m_buttonSelected) // Switch statement for the buttons
	{
	case button::Play:	// The play button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			
		}
		break;
	case button::Options:	// The options button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			
		}
		break;
	case button::Exit:	// The exit button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			exit(0);	// Exits the game
		}
		break;
	default:
		break;
	}

}
