#include "Menu.h"

Menu::Menu(sf::Font & font) :
	m_font(font)
	, TIME_PER_UPDATE(sf::microseconds(1500))
{
	if (!m_backgroundTex.loadFromFile(".//resources//images//UI//bg.jpg"))
	{
		std::cout << "Problem loading Texture for splash screen";
	}
	m_backgroundSprite.setTexture(m_backgroundTex);
	m_backgroundSprite.setScale(0.01f, 0.01f);
	m_backgroundSprite.setOrigin(m_backgroundTex.getSize().x / 2, m_backgroundTex.getSize().y / 2);
	m_backgroundSprite.setPosition(450, 300);

	m_timeStop = false;
	m_transitionStop = false;

	for (int i = 0; i < 4; i++)
	{
		m_buttons[i] = new Button(&m_strings[i], &sf::Vector2f(450, 150 + (i * 100)), &m_font);
	}

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

	if (m_time.asSeconds() <= 3.6)
	{
		m_backgroundSprite.setRotation(m_backgroundSprite.getRotation() - 2);
		m_backgroundSprite.scale(1.00185, 1.00185);
		m_time += TIME_PER_UPDATE;
	}
	else
	{
		m_transitionStop = true;
	}
	
}

void Menu::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(235, 233, 247));
	window.draw(m_backgroundSprite);

	for (int i = 0; i < 4; i++)
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
		m_buttons[3]->loseFocus();

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = button::Garage;	// Switches to the garage button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = button::Exit;	// Switches to the exit button
		}
		break;
	case button::Garage: // The garage button 

						  // Sets the garage button to be highlighted and the other buttons to be not
		m_buttons[0]->loseFocus();
		m_buttons[1]->getFocus();
		m_buttons[2]->loseFocus();
		m_buttons[3]->loseFocus();

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = button::Settings;	// Switches to the exit button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = button::Play;	// Switches to the play button
		}
		break;
	case button::Settings:	// The settings button

						// Sets the swttings button to be highlighted and the other buttons to be not
		m_buttons[0]->loseFocus();
		m_buttons[1]->loseFocus();
		m_buttons[2]->getFocus();
		m_buttons[3]->loseFocus();

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = button::Exit;	// Switches to the exit button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = button::Garage;	// Switches to the garage button
		}
		break;
	case button::Exit:	// The exit button

						// Sets the exit button to be highlighted and the other buttons to be not
		m_buttons[0]->loseFocus();
		m_buttons[1]->loseFocus();
		m_buttons[2]->loseFocus();
		m_buttons[3]->getFocus();

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = button::Play;	// Switches to the play button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = button::Settings;	// Switches to the options button
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
	case button::Garage:	// The garage button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			
		}
		break;
	case button::Settings:	// The settings button 
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
