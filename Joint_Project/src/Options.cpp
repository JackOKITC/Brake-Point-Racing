#include "Options.h"


Options::Options(sf::Font font, GameState *gameState) :
	m_font(font)
{
	m_sliderValue = 5;
	m_button = new Button(&m_string, &sf::Vector2f(450, 200), &m_font);
	m_slider = new Slider(&sf::Vector2f(380, 300), m_sliderValue);
}

Options::~Options()
{
}

void Options::update(GamePadState m_state, Xbox360Controller & m_controller)
{
	m_slider->update();
	checkButtonSelected(m_state, m_controller);
	selectedButton(m_state, m_controller);
}

void Options::render(sf::RenderWindow & window)
{
	window.clear(sf::Color::White);
	m_button->render(window);
	m_slider->render(window);
}


// Function to check which button is selected
void Options::checkButtonSelected(GamePadState m_state, Xbox360Controller m_controller)
{
	switch (m_buttonSelected)	// Switch statement for every button
	{

	case optionsButton::Option1:	// The play button

						// Sets the play button to be highlighted and the other buttons to be not
		m_button->getFocus();
		m_slider->loseFocus();

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = optionsButton::Option2;	// Switches to the options button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = optionsButton::Option3;	// Switches to the exit button
		}
		break;
	case optionsButton::Option2: // The options button 

						  // Sets the options button to be highlighted and the other buttons to be not
		m_button->loseFocus();
		m_slider->getFocus();

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = optionsButton::Option3;	// Switches to the exit button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = optionsButton::Option1;	// Switches to the play button
		}

		if ((m_state.dpadLeft && !m_controller.m_previousState.dpadLeft) || (m_state.LeftThumbStick.x < -50 && m_controller.m_previousState.LeftThumbStick.x > -50))	// Decrements the slider if the player pushes the d-pad or thumbstick left.
		{
			m_sliderValue = m_slider->decrementSlider();
		}


		if ((m_state.dpadRight && !m_controller.m_previousState.dpadRight) || (m_state.LeftThumbStick.x > 50 && m_controller.m_previousState.LeftThumbStick.x < 50))	// Increments the slider if the player pushes the d - pad or thumbstick left.
		{
			m_sliderValue = m_slider->incrementSlider();
		}
		break;
	case optionsButton::Option3:	// The exit button

						// Sets the exit button to be highlighted and the other buttons to be not
		m_button->loseFocus();
		m_slider->loseFocus();
		

		// Checks if the down button has been pressed
		if ((m_state.dpadDown && !m_controller.m_previousState.dpadDown) || (m_state.LeftThumbStick.y > 50 && m_controller.m_previousState.LeftThumbStick.y < 50))
		{
			m_buttonSelected = optionsButton::Option1;	// Switches to the play button
		}

		// Checks if the up button has been pressed
		if ((m_state.dpadUp && !m_controller.m_previousState.dpadUp) || (m_state.LeftThumbStick.y < -50 && m_controller.m_previousState.LeftThumbStick.y > -50))
		{
			m_buttonSelected = optionsButton::Option2;	// Switches to the options button
		}
		break;
	default:
		break;
	}
}

// Function to check if the selected button has been pressed
void Options::selectedButton(GamePadState m_state, Xbox360Controller m_controller)
{
	switch (m_buttonSelected) // Switch statement for the buttons
	{
	case optionsButton::Option1:	// The play button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{

		}
		break;
	case optionsButton::Option2:	// The options button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{

		}
		break;
	case optionsButton::Option3:	// The exit button 
		if (m_state.A && !m_controller.m_previousState.A)	// If the A button has been pressed
		{
			
		}
		break;
	default:
		break;
	}

}

